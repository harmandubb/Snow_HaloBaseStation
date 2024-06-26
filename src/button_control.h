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


#ifdef __cplusplus
}
#endif

int init_bt_scan();
void scan_connecting_error(struct bt_scan_device_info *device_info);
void transmit_led_info(bool led_status);
void scan_filter_match(struct bt_scan_device_info *device_info, struct bt_scan_filter_match *filter_match, bool connectable);
void scan_filter_no_match(struct bt_scan_device_info *device_info, bool connectable);
void scan_connecting(struct bt_scan_device_info *device_info, struct bt_conn *conn);
void scan_connecting_error(struct bt_scan_device_info *device_info);


/**
 * @}
 */

#endif /* BUTTON_CONTROL_H */
