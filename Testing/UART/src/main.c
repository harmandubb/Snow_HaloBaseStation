/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Controlling LEDs through UART. Press 1-3 on your keyboard to toggle LEDS 1-3 on your development
 * kit */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gnss.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/uart.h>

LOG_MODULE_REGISTER(gps_app, LOG_LEVEL_INF);

#define GPS_NODE DT_NODELABEL(gps0)

int main(void)
{
	int err = 0;

	static const struct device *gnss_dev = DEVICE_DT_GET(GPS_NODE);
	// Check if the GNSS device is ready
    if (!device_is_ready(gnss_dev)) {
        LOG_ERR("GNSS device not ready");
        return -ENODEV;
    }
	
	
	while (1) {
		k_msleep(1000);
		printk("System working in the loop\n");
	}
}
