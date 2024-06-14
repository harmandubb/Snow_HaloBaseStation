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
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

#include <dk_buttons_and_leds.h>

#include <nrfx_pwm.h>
#include <nrfx.h>
#include <stdlib.h>

#define PWM_PERIOD PWM_NSEC(1250) //ns
#define PWM_TOP_VALUE (20)
#define PWM_NUM_LED (10)
#define PWM_RESET_PERIODS (70)
#define PWM_PULSE_ARRAY_SIZE (PWM_NUM_LED*4*8)
#define PWM_ARRAY_SIZE PWM_PULSE_ARRAY_SIZE+PWM_RESET_PERIODS //need the last value for the reset
#define PWM_0 (PWM_TOP_VALUE - 5) //clock ticks at 16, MHz
#define PWM_1 (PWM_TOP_VALUE - 10) //clock ticks at 16 MHz
#define RESET_CODE_DURATION (10) //number of periods to hold low 
#define PIN_TOGGLE_OUTPUT (28)
#define PIN_BUTTON_INTERFACE (3)



#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* ADC_CONTROL_H */
