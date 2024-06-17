/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/** @file
 *  @brief LED Button Service (LBS) sample
 */



#include "adc_control.h"

LOG_MODULE_REGISTER(ADC_Control, LOG_LEVEL_INF);

/** @brief init adc read pin . 
 * 
 * 	Initlaized the adc pin to accept the volage from the multiplexer cycling through the sensors. 
 * 
 *  @param adc_dt_spec *adc_channel ptr to an empty struct variabl
 *  
 *  //TODO: read through the adc documentation to determine if more parameters are needed  
 * 
 *  @return ptr to array for holding the adc sensor memory readings 
 *  
*/

int* init_multiplexer_reader(struct adc_dt_spec *adc_channel){
    int err;

    err = adc_channel_setup_dt(adc_channel);
    if (err < 0) {
        LOG_ERR("Could not setup channel #%d (%d)", 0, err);
        return NULL;
    }
    //initialize the sensor memory array here: 
    int* sensor_pressure_data = (int*)malloc(NUM_SENSORS * sizeof(int));
    if (sensor_pressure_data == NULL){
        LOG_ERR("Could not allocate memory for the sensor pressure data\n");
        return NULL; 
    }

    return sensor_pressure_data;
};

// /** @brief init the multiplexer control pins. 
//  * 
//  * 
//  *  @param gpio_dev device structure that contains the device tree information for the gpio peripheral 
//  *  @param sel_pins[] array holding the pin numbers that are used to control the multiplexer selection
//  *  @param num_pins the number of pins that are going to be used to initialize. cannot be more than 4 or less than 1. 
//  *  
//  *  @return status code if the intialization worked or erro code based on the issue
//  *          Status codes: 
//  *                      0 --> Success
//  *                      -1 --> not enough pins provided 
//  *                      -2 --> more than expected pins are provided 
//  *  
// */

int init_multiplexer_sel(const struct device* gpio_dev, int sel_pins[], int num_pins){
    return 0; 
}


// /** @brief request data from sensor 
//  * 
//  * 
//  *  @param gpio_dev device structure that contains the device tree information for the gpio peripheral 
//  *  @param sens_num the number value designated to the sensor that is to be checked
//  *  
//  *  @return sensor value that is scanned by the adc 
//  *          error codes:        
//  *  
// */

int request_sensor_data(const struct device* gpio_dev, int num_sensor){
    return 0; 
};

// /** @brief determine the pressure diffrential between the two sides of the board
//  * 
//  * 
//  *  @param sensor_checked the sensor that is currently being checked
//  *  @param sensor_val the sensor value that is associated with the sensor that is being checked
//  *  
//  *  @return pressure diffrential value. If less than 0 then the left side has more pressure, if greater than the right side has more pressure
//  *          
// */

int calculate_pressure_diffrential(int sensor_checked, int sensor_val){
    static int pressure_diff = 0;

    return pressure_diff; 
}; 



