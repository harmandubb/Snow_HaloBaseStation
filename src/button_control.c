#include "button_control.h"

LOG_MODULE_REGISTER(Button_Control, LOG_LEVEL_INF);

/** @brief initilizes the GPIO for the button input responsible for the paring of the system
 * 
 * 	Initlizes the pin input for a button press and sets the approppriate button change call back for when the button state changes.
 *  @param gpio_dev device structure that contains the device tree information for the gpio peripheral 
 *  @param button_pin Pin value on the board for the button input
 *  @param button_change_cb callback to use on the button interupt for the state change
 * 
 *  @return status code. 0 if successfull <0 if failed 
 *
*/

int init_pairing_button(const struct device* gpio_dev, int button_pin, gpio_callback_handler_t button_interrrupt_handler){
	int err;
	static struct gpio_callback button_interupt_cb;
	gpio_flags_t flags = GPIO_INPUT | GPIO_ACTIVE_HIGH; // I think the configuration here was wrong before hand
	gpio_flags_t interrupts = GPIO_INT_EDGE_RISING; //can change to interrupt on active low 

	LOG_INF("Init GPIO Button: gpio_pin_configure\n");

	err = gpio_pin_configure(gpio_dev, button_pin, flags);
	if (err < 0) {
		LOG_ERR("Error %d: failed to configure button gpio pin %d\n", err, button_pin);
		return err; 
	} 

	LOG_INF("Init GPIO Button: gpio_pin_interrupt_configure\n");

	err = gpio_pin_interrupt_configure(gpio_dev, button_pin, interrupts);
	if (err < 0){
		LOG_ERR("Error %d: failed to configure button callback on pin %d\n", err, button_pin);
		return err;
	}

	LOG_INF("Init GPIO Button: gpio_init_callback\n");

	gpio_init_callback(&button_interupt_cb, button_interrrupt_handler ,BIT(button_pin));

	LOG_INF("Init GPIO Button: gpio_add_callback\n");

	err = gpio_add_callback(gpio_dev, &button_interupt_cb);
	if (err < 0) {
		LOG_ERR("Error adding callback for button change: (err %d)\n", err);
		return err; 
	}

	return 0;
}

/** @brief function to execute on the timer expires
 * 
 *  increment the button hold intervals which will be looked at when the button is released
 *  a concurrency safe coding method will be used such that an external party doesn't read or modify 
 *  the variable before the timer has updated it. 
 *  
 *  @param button_hold_interval ptr to the number of button hold intervals that have occured
 *  
 *  implement concurrency control to ensure that the updates occur correctly
*/

void button_timer_expire_cb(struct k_timer *timer);

/** @brief  callback function for the pairing button
 * 
 *  Allow the bluetooth scanning to occur to accept a new wrist module
 *  
 *  @param port: device binding device structure 
 *  @param gpio_callback: structure that is used to register callback function in the config stage
 *  @param pins: bitwise repersentation of what pin callback has occured. 
 *  
 *  implement concurrency control to ensure that the updates occur correctly
*/

void pairing_button_cb(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins){
	// Call the bluetoth advertising function to occur here. 
	// TODO: write this after the bluetooth library has been written.  
};

