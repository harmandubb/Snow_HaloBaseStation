/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/** @file
 *  @brief LED Button Service (LBS) sample
 */

#include "adc_control.h"

#define NUM_MULTIPLEXER_PINS_ALLOWED (4)
#define ADC_CHANNEL_ID  DT_PROP(DT_CHILD(ADC_NODE, channel_0), reg)
#define ADC_RESOLUTION (12)
#define ADC_BUFFER_SIZE (2)

LOG_MODULE_REGISTER(ADC_Control, LOG_LEVEL_INF);

//flag definitions 
bool adcReady = false; 


/** @brief request data from sensor 
* 
* 
*  @param gpio_dev device structure that contains the device tree information for the gpio peripheral 
*  @param spec adct_dt_spec of the device tree specification for the adc
*  @param sel_pins[] array of the pins that will be used to control the multiplexer
*  @param num_pins  the number of pins that are used to control the multiplexer
*  @param num_sesnor the number value designated to the sensor that is to be checked
*  @param adc_buffer ptr to a buffer that is used to load the adc sampled values
*  
*  @return error or success code 
*          error codes:   
*                    -100 --> num_sensor to be checked is greater than the total number of sensors on the board.       
*                      other errors --> based on the pin logic value setting  
*/

int request_sensor_data(const struct device* gpio_dev, const struct adc_dt_spec *spec, int sel_pins[], int num_pins, int num_sensor, int num_total_sensors, struct adc_sequence *sequence){
    //did you change the adc num pins flag? 
    int err; 
    if (!(num_sensor < num_total_sensors)) {
        LOG_ERR("num_sensor val (%d) is greater than sensors present (%d)\n", num_sensor, num_total_sensors);
        return -100; 
    }

    static uint32_t off_pin_mask = 0;
    for (int i = 0; i < num_pins; i++){
        off_pin_mask = off_pin_mask | (1 << sel_pins[i]);
    }
    
    //turn off all of the gpio pins initilially
    gpio_port_clear_bits(gpio_dev,off_pin_mask);

     // Turn on the pins based on the num_sensor that is being used.
    for (int i = 0; i < num_pins; i++) {
        if ((num_sensor >> i) & 1) {
            err = gpio_pin_set(gpio_dev, sel_pins[i], true);
            if (err < 0) {
                LOG_ERR("Error (%d) occurred when setting the pin for the multiplexer\n", err);
                return err;
            }
        }
    }

    //offset the pin on 
    int offset = 29; //corresponds to 4 on the bits  
    err = gpio_pin_set(gpio_dev, offset, true);
    if (err < 0){
        LOG_ERR("Error (%d) occurred when setting the offset pin", err);
    }

    //request the adc to start recording the data     
    err = adc_read(spec->dev, sequence);
    if (err < 0){
        LOG_ERR("Error (%d) has occured when trying to read from adc\n", err);
    }

    return 0; 
};

/** @brief adc callback function after each sampling
 * 
 * 
 *  @param device ptr to the device bonding 
 *  @param sequence ptr to the sequence data structure 
 *  @param sampling_index what number of sample is done where this callback should be called
 *  
 *  @return the action the adc will take next of enum adc_actoin
*/

enum adc_action my_adc_sequence_callback(const struct device *dev, const struct adc_sequence *sequence, uint16_t sampling_index){
    LOG_INF("The ADC Sample Index is: %d", sampling_index);
    //set the adc done flag 
    adcReady = true; 

    return ADC_ACTION_FINISH;
};


