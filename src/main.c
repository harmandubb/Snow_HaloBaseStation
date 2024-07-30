#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>
#include <stdlib.h>

#include "led_control.h"
#include "adc_control.h"
#include "bluetooth_control.h"
#include "button_control.h"

#include <math.h>

#define NUM_SENSORS (4)

#define NUM_ADC_SEL_PINS (4) //should be the bits needed to rep the num_sensors value

// GPIO0
#define PIN_BOARD_LED (2)
// adc read pin is set to be pin 3 in the overlay file 
#define PIN_ADC_SEL_3 (28)
#define PIN_ADC_SEL_2 (29) 
#define PIN_ADC_SEL_1 (4) 
#define PIN_ADC_SEL_0 (5) 

// GPIO1
#define PIN_PAIRING_BUTTON (15)
#define PIN_SPARE_BUTTON (14)


#define ADC_BUFFER_SIZE (2) //based of resolution, samples taken, and number of channesl (12 bits = 2 bytes)
                                // 2 bytes * 1 sample taken * 1 channel = 2 

#define PRESSURE_THRESHOLD (150)
#define PRESSURE_INTEGRATOR_CEILING (1000)



#define BOND_CONNECT_COUNT_THRESHOLD (6)


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
        *led_operation_ptr = BLANK;

        //variables
        int checkSensorNum = 0; 
        int pressureDiff = 0; //hold a cummuliate value of the pressures 
        int adc_read_val = 0; //use for the value conversion
        
        //get the gpio binding
        const struct device *gpio0_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));
	if (gpio0_dev == NULL) {
		LOG_ERR("Device binding is not found\n");
		return -1; 
	}

        const struct device *gpio1_dev = DEVICE_DT_GET(DT_NODELABEL(gpio1));
	if (gpio1_dev == NULL) {
		LOG_ERR("Device binding is not found\n");
		return -1; 
	}

        //------------------------LED INIT------------------------//
        err = dk_leds_init();
	if (err) {
		printk("LEDs init failed (err %d)\n", err);
		return 0;
	}

        // dynamically allocated memory        
        uint16_t* boardLedMap = init_board_led(PIN_BOARD_LED);
        if (boardLedMap == NULL){
                LOG_ERR("Initilization of board led failed\n");
        }



        // ---------------------------ADC INIT---------------------------//

        //define the array to hold the selec pins 
        int adc_sel_pins[] = {PIN_ADC_SEL_0, PIN_ADC_SEL_1, PIN_ADC_SEL_2, PIN_ADC_SEL_3};

        

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
        err = init_pairing_button(gpio1_dev,PIN_PAIRING_BUTTON,pairing_button_cb);

        //-----------------------BLUETOOTH SCAN----------------------//
        err = bt_enable(bt_ready_cb);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return 0;
	}

        struct bt_conn_cb cb = {
                .connected = connected,
                .disconnected = disconnected,
                .security_changed = on_security_changed,
        };

        bt_conn_cb_register(&cb);

        while(!btReady);

        err = settings_load();
        if (err) {
                LOG_ERR("Settings load failed (err %d)", err);
        }

	const struct bt_scan_init_param bt_scan_init_opts = {
			.scan_param = NULL, //default config 
			.connect_if_match = true,
			.conn_param = NULL, //default config
	};
	
	bt_scan_init(&bt_scan_init_opts); 
        BT_SCAN_CB_INIT(scan_cb, scan_filter_match, scan_filter_no_match, scan_connecting_error, scan_connecting);
        bt_scan_cb_register(&scan_cb);

        //------------------------BOND Devices Scan Check------------//
        int bond_connect_counter = 0 ; 
        int bond_count = scan_bond_devices();
        LOG_INF("Scanning successfully started");
        LOG_INF("bond count: %d", bond_count);

        while((bond_count > 0) && (bond_connect_counter < BOND_CONNECT_COUNT_THRESHOLD) && (!connectedFlag)){
                k_sleep(K_MSEC(500));
                bond_connect_counter++;
        }

        if (!connectedFlag) {
                //stop the bond scanning 
                err = bt_scan_stop();
                if (err < 0) {
                        LOG_ERR("Unable to stop bond scanning");
                }
        }

        

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
                        adc_read_val = adc_buf[0];


                        if (adc_read_val > 65000){
                                adc_read_val = 0; 
                        }

                        LOG_INF("Sensor Checked: %d", checkSensorNum);
                        LOG_INF("BUFF 0: %d", adc_read_val);

                        //print out the sensor values that are present
                        sensorPressureMap[checkSensorNum] = adc_read_val; 

                        LOG_INF("PRESSURE VALS: 0: %d, 1: %d, 2: %d, 3: %d", sensorPressureMap[0], sensorPressureMap[1], sensorPressureMap[2], sensorPressureMap[3]);

                        //calculate the pressure difference 
                        pressureDiff = calculate_pressure_diffrential(checkSensorNum, adc_read_val, NUM_SENSORS);

                        LOG_INF("Pressure Diff: %d", pressureDiff);
                        if (abs(pressureDiff) > PRESSURE_INTEGRATOR_CEILING){
                                pressureDiff = (pressureDiff/(abs(pressureDiff))) * PRESSURE_INTEGRATOR_CEILING;
                        }

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


