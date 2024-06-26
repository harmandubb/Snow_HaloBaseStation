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

#include <nrfx_pwm.h>
#include <nrfx.h>
#include <stdlib.h>

//led parameters to be provided for the pwm output to control led
#define PWM_PERIOD PWM_NSEC(1250) //ns
#define PWM_TOP_VALUE (20)
#define PWM_NUM_LED (13)
#define PWM_RESET_PERIODS (70)
#define PWM_PULSE_ARRAY_SIZE (PWM_NUM_LED*4*8)
#define PWM_ARRAY_SIZE PWM_PULSE_ARRAY_SIZE+PWM_RESET_PERIODS //need the last value for the reset
#define PWM_0 (PWM_TOP_VALUE - 5) //clock ticks at 16, MHz
#define PWM_1 (PWM_TOP_VALUE - 10) //clock ticks at 16 MHz
#define RESET_CODE_DURATION (10) //number of periods to hold low 

//Pin allocation
#define PIN_BOARD_LED (2)

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

// Function prototypes
uint16_t* init_GPIO(const struct device *gpio_dev, int button_pin, int wrist_led_pin, gpio_callback_handler_t button_change_cb);
int init_interface_button(const struct device* ble_device, int button_pin, gpio_callback_handler_t button_change_cb);
uint16_t* init_board_led(int board_led_pin);
uint16_t* init_PWM_array();
void wrist_led_cb(bool led_state);
void update_board_led(struct k_work *item);
void button_timer_expire_cb(struct k_timer *timer);
void status_led_operation(LED_Operation led_operation);
void button_input_interrrupt_handler(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins);
void update_board_led_pressure(uint16_t* led_board_map, bool pressure_left, bool pressure_right);


#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* LED_CONTROL_H */
