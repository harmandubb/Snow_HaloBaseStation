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

extern bool adcReady;

enum adc_action my_adc_sequence_callback(const struct device *dev, const struct adc_sequence *sequence, uint16_t sampling_index);
int request_sensor_data(const struct device* gpio_dev, const struct adc_dt_spec *spec, int sel_pins[], int num_pins, int num_sensor, int num_total_sensors, struct adc_sequence *sequence);
int calculate_pressure_diffrential(int sensor_checked, int sensor_val, int num_sensors);
int init_multiplexer_sel(const struct device* gpio_dev, int sel_pins[], int num_pins);
int* init_multiplexer_reader(struct adc_dt_spec *adc_channel, int *adc_buffer, struct adc_sequence *sequence, int num_sensors);




#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* ADC_CONTROL_H */
