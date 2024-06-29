#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>
#include <stdlib.h>

#include "led_control.h"
#include "adc_control.h"
#include "bluetooth_control.h"
#include "button_control.h"

#include <math.h>

#define NUM_SENSORS (2)

#define NUM_ADC_SEL_PINS (1) //should be the bits needed to rep the num_sensors value

#define PIN_ADC_SEL_0 (28) //to be coordinated with the rest of the sytem
#define PIN_ADC_SEL_1 (29) 
#define PIN_ADC_SEL_2 (4) 
#define PIN_ADC_SEL_3 (5+1)
// adc read pin is set to be pin 3 in the overlay file 
#define PIN_BOARD_LED (2)
#define PIN_PAIRING_BUTTON (5)


#define ADC_BUFFER_SIZE (2) //based of resolution, samples taken, and number of channesl (12 bits = 2 bytes)
                                // 2 bytes * 1 sample taken * 1 channel = 2 

#define PRESSURE_THRESHOLD (10)

#define TARGET_DEVICE_NAME "SNOW"


// FUNCTION DEFINITIONS

void pairing_button_cb(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins);
void bt_ready_cb(int err);

LOG_MODULE_REGISTER(base_station, LOG_LEVEL_INF);

//flags
bool btReady = false; 

int main(void)
{
        k_sleep(K_SECONDS(3));
        //Setup
        int err = 0; 

        //flags 
        bool sensorDataRequested = false;
        adcReady = false; 
        bool turnOnRightSide = false; 
        bool turnOnLeftSide = false; 
        ledHandleReady = false; 
        led_handle = 0; 
        wrist_conn = NULL;

        //variables
        int checkSensorNum = 0; 
        int pressureDiff = 0; 
        LED_Operation led_operation = BLANK; 
        LED_Operation* led_operation_ptr = &led_operation;   

        //get the gpio binding
        const struct device *gpio0_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));
	if (gpio0_dev == NULL) {
		LOG_ERR("Device binding is not found\n");
		return -1; 
	}

        // dynamically allocated memory        
        uint16_t* boardLedMap = init_board_led(PIN_BOARD_LED);
        if (boardLedMap == NULL){
                LOG_ERR("Initilization of board led failed\n");
        }

        //define the array to hold the selec pins 
        int adc_sel_pins[] = {PIN_ADC_SEL_0, PIN_ADC_SEL_1, PIN_ADC_SEL_2, PIN_ADC_SEL_3};

        // ---------------------------ADC INIT---------------------------//

        // //initalize the adc device tree variable 
        static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

        struct adc_sequence_options opts = {
                .interval_us = 0,
                .callback = my_adc_sequence_callback,
                .user_data = NULL, 
                .extra_samplings = 0,
        };
        uint16_t adc_buf[ADC_BUFFER_SIZE] = {0};
        
	struct adc_sequence sequence = {
		.buffer = &adc_buf,
		/* buffer size in bytes, not number of samples */
		.buffer_size = sizeof(adc_buf),
		//Optional
		//.calibrate = true,
                .options = &opts,
	};

        int* sensorPressureMap = init_multiplexer_reader(&adc_channel, &sequence, NUM_SENSORS);
        if (sensorPressureMap == NULL) {
                LOG_ERR("Initalization of sensorPressureMap failed\n");
        }

        while(!adcReady);
        LOG_INF("ADC INITALIZATION DONE\n");
        adcReady = false; 

        err = init_multiplexer_sel(gpio0_dev, adc_sel_pins, NUM_ADC_SEL_PINS);
        if (err < 0){
                LOG_ERR("Failed to intializlize the multiplexer init pins (err %d)\n", err);
        }

        //----------------------------PWM INIT--------------------------------//
        //initalize the pwm pin and the array for the board led 
        uint16_t* led_board_map = init_board_led(PIN_BOARD_LED);

        //----------------------PAIRING BUTTON INIT--------------------------//

        //remeber to change to gpio1_dev for the buttons
        err = init_pairing_button(gpio0_dev,PIN_PAIRING_BUTTON,pairing_button_cb);

        //-----------------------BLUETOOTH SCAN TESTING----------------------//
        

        //--------------SCAN TESTING START---------------------//

        // int err = 0; 
        err = bt_enable(bt_ready_cb);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return 0;
	}

        struct bt_conn_cb cb = {
                .connected = connected,
                .disconnected = disconnected,
        };

        bt_conn_cb_register(&cb);

        while(!btReady);

	const struct bt_scan_init_param bt_scan_init_opts = {
			.scan_param = NULL, //default config 
			.connect_if_match = true,
			.conn_param = NULL, //default config
	};
	
	bt_scan_init(&bt_scan_init_opts); 
        BT_SCAN_CB_INIT(scan_cb, scan_filter_match, scan_filter_no_match, scan_connecting_error, scan_connecting);
        bt_scan_cb_register(&scan_cb);

        //--------------------UUID FILTER

        err = bt_scan_filter_add(BT_SCAN_FILTER_TYPE_UUID, BT_UUID_LBS);
	if (err) {
		LOG_ERR("UUID scanning filters cannot be set (err %d)", err);
		return err;
	}

        //------------------SHORT NAME FILTER

        // struct bt_scan_short_name short_name_filter_data = {
        //         .name = TARGET_DEVICE_NAME,
        //         .min_len = sizeof(TARGET_DEVICE_NAME),
        // };

        // err = bt_scan_filter_add(BT_SCAN_FILTER_TYPE_SHORT_NAME,&short_name_filter_data);
        // if (err) {
	// 	LOG_ERR("Short Name scanning filters cannot be set (err %d)", err);
	// 	return err;
        // }

        //------------------NAME FILTER
        err = bt_scan_filter_add(BT_SCAN_FILTER_TYPE_NAME, TARGET_DEVICE_NAME);
        if (err) {
		LOG_ERR("Name scanning filters cannot be set (err %d)", err);
		return err;
        }


        err = bt_scan_filter_enable(BT_SCAN_UUID_FILTER | BT_SCAN_NAME_FILTER, true);
        // err = bt_scan_filter_enable(BT_SCAN_NAME_FILTER, true);

        if (err) {
		LOG_ERR("Filters cannot be turned on (err %d)", err);
		return err;
	}

        LOG_INF("Scan module initialized");


        err = bt_scan_start(BT_SCAN_TYPE_SCAN_ACTIVE);
	if (err) {
		LOG_ERR("Scanning failed to start (err %d)", err);
		return 0;
	}

        LOG_INF("Scanning successfully started");

        //--------------SCAN TESTING END---------------------//

        *led_operation_ptr = BOARD_ALIVE;

        for(;;){

                if (sensorDataRequested == false) {
                        //send the reques to the adc to read
                        err = request_sensor_data(gpio0_dev, &adc_channel, adc_sel_pins, NUM_ADC_SEL_PINS, checkSensorNum, NUM_SENSORS, &sequence);
                        if (err < 0){
                                LOG_ERR("Failed to request the sensor data (err %d)\n", err);
                        }

                        sensorDataRequested = true; 
                }

                if(adcReady){
                        //update the array of the sensor value 
                        sensorPressureMap[checkSensorNum] = adc_buf[0];
                        //calculate the pressure difference 
                        pressureDiff = calculate_pressure_diffrential(checkSensorNum, adc_buf[0], NUM_SENSORS);

                        //based on the pressureDiff decide which side to turn on
                        turnOnLeftSide = false; 
                        turnOnRightSide = false; 
                        if (abs(pressureDiff) > PRESSURE_THRESHOLD) {
                                //yes something need to turn on
                                if(pressureDiff > 0) {
                                        turnOnRightSide = true;
                                } else {
                                        turnOnLeftSide = true; 
                                        
                                }
                        }

                        //update the led as needed 
                        update_board_led_pressure(led_board_map, turnOnLeftSide, turnOnRightSide);
                        if(ledHandleReady){
                                LOG_INF("Able to turn on wrist led");
                                updateWristLED(turnOnRightSide);
                        }

                        checkSensorNum = (checkSensorNum + 1) % NUM_SENSORS;
                        adcReady = false; 
                        sensorDataRequested = false; 
                }

                //electronics status indicator
                status_led_operation(*led_operation_ptr);

        }
        return 0;
}

/** @brief  callback function to show the user is a connection has been made or not and set flag to allow the code to begin bluetooth activites
 * 
 *     
 *  @param err: error present with the connection if at all. 
 *  
*/

void bt_ready_cb(int err){
        if (err < 0){
                LOG_ERR("Error with enabling the bluetooth module (err: %d)", err);
        } else {
                LOG_INF("Bluetooth initialized");
        }

        btReady = true; 

}


/** @brief  callback function for the pairing button
 * 
 *  Allow the bluetooth scanning to occur to accept a new wrist module
 *  TODO: Make the button keep a time state for deliteing all of the connections 
 *  
 *  @param port: device binding device structure 
 *  @param gpio_callback: structure that is used to register callback function in the config stage
 *  @param pins: bitwise repersentation of what pin callback has occured. 
 *  
 *  implement concurrency control to ensure that the updates occur correctly
*/

void pairing_button_cb(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins){
	// Call the bluetoth advertising function to occur here. 
	uint32_t pin_vals = 0; 
        int err = 0; 

        err = gpio_port_get(port,&pin_vals);
        if (err < 0){
                LOG_ERR("Error: Unable to get gpio port levels (err: %d)", err);
        }
         //if the button is not pressed down then just return right away 
        if (!(pin_vals & (1 << PIN_PAIRING_BUTTON))) {
                return;
        }

        // err = init_bt_scan();
        // if (err < 0){
        //         LOG_ERR("Unable to initalize the bluetooth scan parameters (err: %d)\n", err);
        // }
        
        //start the scan function 
        err = bt_scan_start(BT_SCAN_TYPE_SCAN_ACTIVE);
        if (err < 0) {
                LOG_ERR("Error starting the bt scan (err: %d)\n", err);
        }

};