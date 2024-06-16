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

//advertising defines

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

struct Advertise_Bt_Conn_Data {
	struct k_work *work; 
	bool new_connection; 
};

//global variables end 


/** @brief Initlizes an output pin to control the LED on and off states using a PWM signal 
 * 
 *  Function is resposible for initilizing a dynamically allocated array that holds the pulse values for the LED wrist module
 *  and ensuring the pin is correctly configured for the PWM output wave
 * 
 *  @param wrist_led_pin value on the board that that powers the LED color change 
 *  @param array_size size of the array needed for all of the pwm pulses for the led wrist strap
 *  @param zero_logic_pulse_val interger value of the pulse values that define a z or off value
 *  
 *  @return ptr to the dynamically allocated PWM array that holds the led pulses
 * 
*/

uint16_t* init_board_led(int board_led_pin){
	int err;
	uint16_t* pwm_pulse_array = init_PWM_array();

	nrfx_pwm_t pwm0 = NRFX_PWM_INSTANCE(0);
	nrfx_pwm_config_t pwm0_config = {
        .output_pins = {
            board_led_pin,
            NRF_PWM_PIN_NOT_CONNECTED,
            NRF_PWM_PIN_NOT_CONNECTED, 
            NRF_PWM_PIN_NOT_CONNECTED,
        },

        .pin_inverted = {
            false, 
            false, 
            false, 
            false,
        },
        .irq_priority = NRFX_PWM_DEFAULT_CONFIG_IRQ_PRIORITY,
        .base_clock = NRF_PWM_CLK_16MHz,
        .count_mode = NRF_PWM_MODE_UP,
        .top_value = PWM_TOP_VALUE,
        .load_mode = NRF_PWM_LOAD_COMMON,
        .step_mode = NRF_PWM_STEP_AUTO, //need to set the repeat value to one so this moves every time through the memory. 
        .skip_gpio_cfg = false,
        .skip_psel_cfg = false
    };

    //ensuring that a prior initialization is not present. 
    nrfx_pwm_uninit(&pwm0);

	err = nrfx_pwm_init(&pwm0,&pwm0_config,NULL,NULL);
    if (err != NRFX_SUCCESS){
        printk("Error Occured when initializing the pwm: %d\n", err);
    }

	nrf_pwm_sequence_t pw0_seq_config = {
        .values = pwm_pulse_array, //this is suppose to be a 16 bit value but lets see how a 8 bit value impacts
        .length = PWM_ARRAY_SIZE,
        .repeats = 0, //only play the duty cycle in each cell once. 
        .end_delay = RESET_CODE_DURATION,
    };

    nrfx_pwm_simple_playback(&pwm0, &pw0_seq_config, 1, NRFX_PWM_FLAG_LOOP);

	return pwm_pulse_array;
}

/** @brief Intilizes an array that holds the pulse values for controlling the wrist led strap
 * 
 * 	The function will not have an input for the led array size since it will rely on the defines
 *  to create the array size becuase the array size can change on the number of LED that are present 
 *  and the protocol type that is being used. 
 * 
 *  @param array_size size of the PWM array to be made for the PWM pulses
 *  @param zero_logic_pulse_val logic value that defines an off or zero pulse value
 * 
 *  @return ptr to the dynamically allocated PWM array that holds the led pulses
 * 
*/

uint16_t* init_PWM_array(){
    uint16_t* pwm_array = (uint16_t*)malloc(PWM_ARRAY_SIZE * sizeof(uint16_t));
    if (pwm_array == NULL){
        printk("Error: failed to initialize the PWM array\n");
        return NULL; 
    }

    for (int i = 0; i < PWM_ARRAY_SIZE; i++){
        if(i < PWM_PULSE_ARRAY_SIZE) {
            pwm_array[i] = PWM_0;
        } else {
            pwm_array[i] = PWM_TOP_VALUE;
        }
    }

    return pwm_array;
}


/** @brief produces the needed control signals to change the led lighting on the wrist 
 * 
 *  This will use the sypers library to create the needed pulses to update the led wrist band. \
 *  This functin will be running on a seperate thread in the back ground to execute
 * 
 *  @param work struct of k_work: this will be apart of a struct with the following parameters
 *
 *  		@param PWM_pulse_array ptr to the dynamically allocated array that holds the led control pulses 
 * 			@param PWM_pulse_array_size size of the pulse array in the dynamic memory
 *  		@param pwm_spec zephyr struct pwm_dt_spec which holds the device binding, pwm pin, the period of the pwm wave. 
*/

void update_wrist_led(struct k_work *item){
	// values that are in the struct --> int* PWM_pulse_array, int PWM_pulse_array_size, int PWM_pin
	Update_Wrist_Led_Data *data = CONTAINER_OF(item, Update_Wrist_Led_Data, work); 
	int err; 

	if(data->spec == NULL) {
		printk("The spec designation is NULL\n");
		return; 
	}

	err = pwm_set_dt(data->spec, PWM_PERIOD, data->PWM_pulse_array[0]);
	if (err < 0){
		printk("Unable to send initial PWM pulse");
		return; 
	}

	for(int i = 1; i < data->PWM_pulse_array_size; i++){
		//update the pwm signal for the next signal to be on deck and then wait for the period amount. 
		err = pwm_set_dt(data->spec, PWM_PERIOD, data->PWM_pulse_array[i]);
		if (err < 0) {
			printk("Setting PWM Error: %d on pin %d\n",err, data->spec->channel);
			return; 
		}

		k_sleep(K_NSEC(1250));
	}
	err = pwm_set_dt(data->spec, PWM_PERIOD, 0);
		if (err < 0) {
			printk("Unable to turn of the PWM signal\n");
			return; 
		}

	return; 

}



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

void board_led_operation(LED_Operation led_operation) {
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

