/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

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

#include <nrfx.h>
#include <stdlib.h>

#include "bluetooth_control.h"

#define PIN_WRIST_PAIRING_BUTTON (14)
#define PIN_BOOT_PAIRING_BUTTON (15)

//variables
extern struct k_mutex button_hold_mutex;

//functions
int init_pairing_button(const struct device* gpio_dev, int button_pin, gpio_callback_handler_t button_interrrupt_handler);
void button_timer_expire_cb(struct k_timer *timer);
void wrist_pairing_button_cb(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins);



#ifdef __cplusplus
}
#endif


/**
 * @}
 */

#endif /* BUTTON_CONTROL_H */
