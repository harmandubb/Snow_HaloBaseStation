#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>
#include <stdlib.h>

#include "led_control.h"
#include "adc_control.h"

#define NUM_SENSORS (2)

#define NUM_ADC_SEL_PINS (1) //should be the bits needed to rep the num_sensors value

#define PIN_ADC_SEL_0 (28) //to be coordinated with the rest of the sytem
#define PIN_ADC_SEL_1 (29) 
#define PIN_ADC_SEL_2 (4) 
#define PIN_ADC_SEL_3 (5)

#define ADC_BUFFER_SIZE (2) //based of resolution, samples taken, and number of channesl (12 bits = 2 bytes)
                                // 2 bytes * 1 sample taken * 1 channel = 2 


LOG_MODULE_REGISTER(base_station, LOG_LEVEL_INF);

int main(void)
{
        k_sleep(K_SECONDS(3));
        LOG_INF("Most Updated Code: 1\n");
        //Setup
        int err = 0; 

        //flags 
        bool sensorDataRequested = false;
        adcReady = false; 

        //variables
        int checkSensorNum = 0; 
        int pressureDiff = 0; 

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

        err = request_sensor_data(gpio0_dev, &adc_channel, adc_sel_pins, NUM_ADC_SEL_PINS, checkSensorNum, NUM_SENSORS, &opts);
        if (err < 0){
                LOG_ERR("Failed to request the sensor data (err %d)\n", err);
        }

        //determine what pin the adc channel is reading from 


        for(;;){

                // Constantl read the ADC buffer for the output 
                LOG_INF("The ADC Reading is: %d, %d \n", adcSensorReading[0], adcSensorReading[1]);
                k_sleep(K_MSEC(100));
                err = request_sensor_data(gpio0_dev, &adc_channel, adc_sel_pins, NUM_ADC_SEL_PINS, checkSensorNum, NUM_SENSORS, &opts);
                if (err < 0){
                        LOG_ERR("Failed to request the sensor data (err %d)\n", err);
                }
                //update the led of the baord 

                //go through the board logic
        }
        return 0;
}
