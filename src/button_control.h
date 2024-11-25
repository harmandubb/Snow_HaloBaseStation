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
#include "iphone_bt_connect.h"


#define PIN_PHONE_PAIRING_BUTTON (13)
#define PIN_BOOT_PAIRING_BUTTON (14)
#define PIN_BOOT_DEFINE_SWITCH (15)

//variables
extern bool isRightBoot;

//functions
int init_pairing_button(const struct device* gpio_dev, int button_pin, struct gpio_callback* button_interupt_cb, gpio_callback_handler_t button_interrrupt_handler);
int init_select_switch(const struct device* gpio_dev, int switch_pin);
void phone_pairing_button_cb(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins);
void boot_pairing_button_cb(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins);



#ifdef __cplusplus
}
#endif


/**
 * @}
 */

#endif /* BUTTON_CONTROL_H */
