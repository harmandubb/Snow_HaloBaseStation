/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef LED_CONTROL_H
#define LED_CONTROL_H

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
#include <dk_buttons_and_leds.h>

#include <dk_buttons_and_leds.h>

#include <nrfx_pwm.h>
#include <nrfx.h>
#include <stdlib.h>

//led parameters to be provided for the pwm output to control led
#define PWM_PERIOD PWM_NSEC(1250) //ns
#define PWM_TOP_VALUE (20) 
#define PWM_NUM_LED (10)
#define PWM_RESET_PERIODS (70)

#define PWM_COLOR_LED (3) //if RGB only 
// #define PWM_COLOR_LED (4) //if the white led is present


#define PWM_PULSE_ARRAY_SIZE (PWM_NUM_LED*PWM_COLOR_LED*8)
#define PWM_ARRAY_SIZE PWM_PULSE_ARRAY_SIZE+PWM_RESET_PERIODS //need the last value for the reset
// #define PWM_0 (PWM_TOP_VALUE - 5) //clock ticks at 16, MHz 0.9 us L
// #define PWM_1 (PWM_TOP_VALUE - 10) //clock ticks at 16 MHz 0.6 us L

#define PWM_0 (PWM_TOP_VALUE - 7) //0.8 us L
#define PWM_1 (PWM_TOP_VALUE - 13) //0.45 us L

#define RESET_CODE_DURATION (10) //number of periods to hold low 

typedef enum {
    BOARD_ALIVE,
    PAIRING,
    CONNECTED,
    DISCONNECTED,
    PAIRING_DELETE,
    BLANK
} LED_Operation;

typedef struct {
	struct k_work work; 
	int *PWM_pulse_array;
	int PWM_pulse_array_size; 
	const struct pwm_dt_spec *spec;
}Update_Board_Led_Data;

extern LED_Operation* led_operation_ptr;

// Function prototypes
void wrist_led_cb(bool led_state);
void status_led_operation(LED_Operation led_operation);


#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* LED_CONTROL_H */
