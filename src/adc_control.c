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

struct adc_sequence_options opts = {
    .interval_us = 0,
    .callback = my_adc_sequence_callback,
    .user_data = NULL, 
    .extra_samplings = 0,
};

/** @brief init adc read pin . 
 * 
 * 	Initlaized the adc accept the volage from the multiplexer cycling through the sensors. 
 * 
 *  @param adc_dt_spec *adc_channel ptr to the device node label dt spec   
 *  @param adc_buffer ptr to a buffer that is used to store the adc read outputs
 *  @param sequence ptr to s sequence structure to be used in the read function
 *  @param num_sensors number of total sensors that are present in the system
 * 
 *  @return ptr to array for holding the adc sensor memory readings 
 *  
*/

int* init_multiplexer_reader(const struct adc_dt_spec *adc_channel, struct adc_sequence *sequence, int num_sensors){
    int err = 0;

    err = adc_channel_setup_dt(adc_channel);
    if (err < 0) {
        LOG_ERR("Could not setup channel #%d (%d)", 0, err);
        return NULL;
    }

    err = adc_sequence_init_dt(adc_channel, sequence);
	if (err < 0) {
		LOG_ERR("Could not initalize sequnce");
		return NULL;
	}
    err = adc_read(adc_channel->dev, sequence);
    if (err < 0) {
        LOG_ERR("Could not read (%d)", err);
        return NULL; 
    }
    //initialize the sensor memory array here: 
    int* sensor_pressure_data = (int*)malloc(num_sensors * sizeof(int));
    if (sensor_pressure_data == NULL){
        LOG_ERR("Could not allocate memory for the sensor pressure data\n");
        return NULL; 
    }

    err = adc_sequence_init_dt(adc_channel, sequence); 
    if (err < 0) {
        LOG_ERR("Error (%d) occured when initalizing adc sequence \n", err);
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
//  *                      -100 --> not enough pins provided 
//  *                      -200 --> more than expected pins are provided 
//  *                       other error codes --> need to look at the error coedes for gpio_pinconfiguration 
// */

int init_multiplexer_sel(const struct device* gpio_dev, int sel_pins[], int num_pins){
    if(num_pins <= 0){
        LOG_ERR("Not enough pins provided to control the adc multiplexer\n");
        return -100; 
    } else if (num_pins > NUM_MULTIPLEXER_PINS_ALLOWED) {
        LOG_ERR("More pins (%d) than multiplexer interface provided\n", num_pins);
        return -200; 
    }

    gpio_flags_t flags = GPIO_OUTPUT_INACTIVE;
    int err; 

    for(int i = 0; i < num_pins; i++){
        err = gpio_pin_configure(gpio_dev, sel_pins[i], flags);
        if (err < 0) {
            LOG_ERR("Error %d: failed to configure button gpio pin %d\n", err, sel_pins[i]);
            return err; 
        } 
    }

    return 0; 
}


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

    //request the adc to start recording the data     
    err = adc_read(spec->dev, sequence);
    if (err < 0){
        LOG_ERR("Error (%d) has occured when trying to read from adc\n", err);
    }

    return 0; 
};

/** @brief determine the pressure diffrential between the two sides of the board
 * 
 * 
 *  @param sensor_checked the sensor that is currently being checked
 *  @param sensor_val the sensor value that is associated with the sensor that is being checked
 *  
 *  @return pressure diffrential value. If less than 0 then the left side has more pressure, if greater than the right side has more pressure
 *          
*/

int calculate_pressure_diffrential(int sensor_checked, int sensor_val, int num_sensors){
    static int pressure_diff = 0;
    static int pressure_l = 0; 
    static int pressure_r = 0; 

    if (sensor_checked < num_sensors/2){
        pressure_l = sensor_val; 
    } else {
        pressure_r = sensor_val; 
    }

    pressure_diff = pressure_r - pressure_l;

    return pressure_diff; 
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
    //since only one sample is done there is no need to check the sampling index to see where we are
    // LOG_INF("The ADC Sample Index is: %d", sampling_index);
    //set the adc done flag 
    adcReady = true; 

    return ADC_ACTION_FINISH;
};

/**
 * @brief create a simple funciton that intialized the ADC and requests one read
 * 
 * @param adc_channel: the adc spec in the device tree describing the adc channel in use
 * 
 * @return error code if present otherwise 0
 */

int simple_adc_init_and_call(const struct adc_dt_spec adc_channel){
    int err = 0; 

    if (!adc_is_ready_dt(&adc_channel)) {
        LOG_ERR("ADC controller devivce %s not ready", adc_channel.dev->name);
        return -100;
    }

    err = adc_channel_setup_dt(&adc_channel);
    if (err < 0) {
        LOG_ERR("Could not setup channel #%d (%d)", 0, err);
        return err;
    }

    struct adc_sequence_options opts = {
                .interval_us = 0,
                .callback = my_adc_sequence_callback,
                .user_data = NULL, 
                .extra_samplings = 0,
        };

    int16_t buf;
	struct adc_sequence sequence = {
		.buffer = &buf,
		/* buffer size in bytes, not number of samples */
		.buffer_size = sizeof(buf),
		//Optional
		//.calibrate = true,
        .options = &opts,
	};

    err = adc_sequence_init_dt(&adc_channel, &sequence);
	if (err < 0) {
		LOG_ERR("Could not initalize sequnce");
		return err;
	}
    
    err = adc_read(adc_channel.dev, &sequence);
    if (err < 0) {
        LOG_ERR("Could not read (%d)", err);
        return err; 
    }

    return 0;
  
};

