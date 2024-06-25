#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>
#include <stdlib.h>

#include "led_control.h"
#include "adc_control.h"
#include "bluetooth_control.h"

#include <math.h>

#define NUM_SENSORS (2)

#define NUM_ADC_SEL_PINS (1) //should be the bits needed to rep the num_sensors value

#define PIN_ADC_SEL_0 (28) //to be coordinated with the rest of the sytem
#define PIN_ADC_SEL_1 (29) 
#define PIN_ADC_SEL_2 (4) 
#define PIN_ADC_SEL_3 (5)
// adc read pin is set to be pin 3 in the overlay file 
#define PIN_BOARD_LED (2)
#define PIN_PAIRING_BUTTON (5)


#define ADC_BUFFER_SIZE (2) //based of resolution, samples taken, and number of channesl (12 bits = 2 bytes)
                                // 2 bytes * 1 sample taken * 1 channel = 2 

#define PRESSURE_THRESHOLD (10)

LOG_MODULE_REGISTER(base_station, LOG_LEVEL_INF);

int main(void)
{
        //Setup
        int err = 0; 

        LOG_INF("TESTING GIT AUTHENTICATION?");

        //flags 
        bool sensorDataRequested = false;
        adcReady = false; 
        bool turnOnRightSide = false; 
        bool turnOnLeftSide = false; 

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
        if (!adc_is_ready_dt(&adc_channel)) {
                LOG_ERR("ADC controller devivce %s not ready", adc_channel.dev->name);
                return 0;
        }

        int adcSensorReading[ADC_BUFFER_SIZE] = {0};

        //default sequence options struct to be used. 
        struct adc_sequence_options opts = {
                .interval_us = 0,
                .callback = my_adc_sequence_callback,
                .user_data = NULL, 
                .extra_samplings = 0,
        };

        //returns a dynamically allocated sensor pressure map
        int* sensorPressureMap = init_multiplexer_reader(&adc_channel, adcSensorReading, &opts,NUM_SENSORS);
        if (sensorPressureMap == NULL) {
                LOG_ERR("Initalization of sensorPressureMap failed\n");
        }

        err = init_multiplexer_sel(gpio0_dev, adc_sel_pins, NUM_ADC_SEL_PINS);
        if (err < 0){
                LOG_ERR("Failed to intializlize the multiplexer init pins (err %d)\n", err);
        }

        //----------------------------PWM INIT--------------------------------//
        //initalize the pwm pin and the array for the board led 
        uint16_t* led_board_map = init_board_led(PIN_BOARD_LED);

        //remeber to change to gpio1_dev for the buttons
        err = init_pairing_button(gpio0_dev,PIN_PAIRING_BUTTON,pairing_button_cb);



        


        for(;;){

                if (sensorDataRequested == false) {
                        //send the reques to the adc to read
                        err = request_sensor_data(gpio0_dev, &adc_channel, adc_sel_pins, NUM_ADC_SEL_PINS, checkSensorNum, NUM_SENSORS, &opts);
                        if (err < 0){
                                LOG_ERR("Failed to request the sensor data (err %d)\n", err);
                        }

                        sensorDataRequested = true; 
                }

                if(adcReady){
                        //update the array of the sensor value 
                        sensorPressureMap[checkSensorNum] = adcSensorReading[0];
                        //calculate the pressure difference 
                        pressureDiff = calculate_pressure_diffrential(checkSensorNum, adcSensorReading[0], NUM_SENSORS);

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

                        checkSensorNum = (checkSensorNum + 1) % NUM_SENSORS;
                        adcReady = false; 
                        sensorDataRequested = false; 
                }

                //electronics status indicator
                status_led_operation(*led_operation_ptr);

        }
        return 0;
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
	// TODO: write this after the bluetooth library has been written. 
        int err = 0; 
        const struct bt_scan_init_param bt_scan_init_opts = {
                .scan_param = NULL, //default config 
                .connect_if_match = true,
                .conn_param = NULL, //default config
        };
        
        bt_scan_init(&bt_scan_init_opts);  

        uint8_t filter_modes = BT_SCAN_SHORT_NAME_FILTER | BT_SCAN_UUID_FILTER;
        err = bt_scan_filter_enable(filter_modes, true); //Want all filters to be matched when looking for a new device
        if (err < 0) {
                LOG_ERR("Error establishing scan filters (err: %d)\n", err);
        }
        //double check if the definitin of the short name filter is correct
        struct bt_scan_short_name short_name_filter = {
                .name = "SNOW_HALO",
                .min_len = 9,
        };

        err = bt_scan_filter_add(BT_SCAN_FILTER_TYPE_SHORT_NAME, &short_name_filter); 
        if (err < 0) {
                LOG_ERR("Error setting the short name filter (err: %d)\n", err);
        }

        err = bt_scan_filter_add(BT_SCAN_FILTER_TYPE_UUID, BT_UUID_LBS);
        if (err < 0) {
                LOG_ERR("Error setting the uuid filter (err: %d)\n", err);
        }

        //start the scan function 
        err = bt_scan_start(BT_SCAN_TYPE_SCAN_ACTIVE);
        if (err < 0) {
                LOG_ERR("Error starting the bt scan (err: %d)\n", err);
        }





        

};