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

#include <nrfx.h>
#include <stdlib.h>

#define PIN_TOGGLE_OUTPUT (3)

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* BUTTON_CONTROL_H */
