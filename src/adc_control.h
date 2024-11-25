/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef ADC_CONTROL_H
#define ADC_CONTROL_H

/**@file
 * @defgroup bt_lbs LED Button Service API
 * @{
 * @brief API for the LED Button Service (LBS).
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h> //need to allow memory size in the heap to use malloc
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/types.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <zephyr/drivers/adc.h>

#define ADC_RESOLUTION (12)
#define NUM_SENSORS (2)
#define ADC_BUFFER_SIZE (NUM_SENSORS*2)

extern bool adcFinished;
extern uint16_t led_handle;
extern struct bt_conn *conn; //TODO: make this an array of connections based on the connections that are allowed to allow for multiple gatt operations to take place. For now just allow one wrist device to take place. 

enum adc_action my_adc_sequence_callback(const struct device *dev, const struct adc_sequence *sequence, uint16_t sampling_index);
int simple_adc_init_and_call(const struct adc_dt_spec adc_channel);
int request_sensor_data(const struct adc_dt_spec *spec, struct adc_sequence *sequence);



#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* ADC_CONTROL_H */
