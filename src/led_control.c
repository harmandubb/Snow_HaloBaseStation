/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/** @file
 *  @brief LED Button Service (LBS) sample
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>

#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/conn.h>

#include "led_control.h"

LOG_MODULE_REGISTER(LED_Control, LOG_LEVEL_INF);

#define HOLD_INTERVAL_DURATION K_SECONDS(3) //secounds
#define HOLD_INTERVAL_PERIOD K_SECONDS(5) //secounds 

#define RED_LED		DK_LED1
#define GREEN_LED	DK_LED2
#define BLUE_LED	DK_LED3

#define RUN_LED_BLINK_INTERVAL 500 //msec 

//global variables
LED_Operation led_operation = BLANK; 
LED_Operation* led_operation_ptr = &led_operation;    



/** @brief outlines how the leds should operate base on an operational mode that is passed
 * 
 * 
 *  Operational modes are outlines as followed: (Enum should be used to define the operation names)
 * 
 *  1. Board_Alive - Have a solid green light to show no connections are made but the board is looking and is healthy 
 *  2. Pairing_Operation - Blinking blue to show that a connection is being looked for currently 
 *  3. Connected - Solid Blue to show that a connection is made to a base unit 
 *  4. Pairing delete - Solid Red to show that the previous bonds are being deleted (2 secounds should be the aim for this)
 *  5. Disconnected - Blinking red to show that a disconnection has occured. (5 secound stay before a connection protocol starts)
 * 
 *  @param led_operation enum to show which on board led should be showing
 * 
*/

void status_led_operation(LED_Operation led_operation) {
    static int blink_status = 0; 

	blink_status = (blink_status + 1) % 2;

	switch(led_operation){
		case BOARD_ALIVE:
			dk_set_led(BLUE_LED, false);
			dk_set_led(RED_LED, false);
			dk_set_led(GREEN_LED, true);
			break;

		case PAIRING:
			dk_set_led(BLUE_LED, blink_status);
			dk_set_led(RED_LED, false);
			dk_set_led(GREEN_LED, false);
			break; 

		case CONNECTED: 
			dk_set_led(BLUE_LED, true);
			dk_set_led(RED_LED, false);
			dk_set_led(GREEN_LED, false);
			break; 

		case DISCONNECTED: 
			dk_set_led(BLUE_LED, false);
			dk_set_led(RED_LED, blink_status);
			dk_set_led(GREEN_LED, false);
			break; 

		case PAIRING_DELETE: 
			dk_set_led(BLUE_LED, false);
			dk_set_led(RED_LED, true);
			dk_set_led(GREEN_LED, false);
			break;  

		default: 
			dk_set_led(BLUE_LED, false);
			dk_set_led(RED_LED, false);
			dk_set_led(GREEN_LED, false);
			break;

	}

	k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
}

