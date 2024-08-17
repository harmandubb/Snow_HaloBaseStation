/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/** @file
 *  @brief LED Button Service (LBS) sample
 */

#include "adc_control.h"


#define ADC_CHANNEL_ID  DT_PROP(DT_CHILD(ADC_NODE, channel_0), reg)


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

int request_sensor_data(const struct adc_dt_spec *spec, struct adc_sequence *sequence){
    int err = 0; 
    //request the adc to start recording the data     
    err = adc_read(spec->dev, sequence);
    if (err < 0){
        LOG_ERR("Error (%d) has occured when trying to read from adc\n", err);
        return err; 
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
    //set the adc done flag 
    adcReady = true; 

    LOG_INF("Sampling Index: %d", sampling_index);

    if (sampling_index < NUM_SENSORS){
        return ADC_ACTION_CONTINUE;
    } else {
        return ADC_ACTION_FINISH;
    }
};


