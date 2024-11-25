#include "button_control.h"


LOG_MODULE_REGISTER(Button_Control, LOG_LEVEL_INF);

//Global variables
bool isRightBoot = false; 
extern struct k_work Lboot_scan_work; 

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
	gpio_flags_t interrupts = GPIO_INT_EDGE_BOTH; //can change to interrupt on active low 

	err = gpio_pin_configure(gpio_dev, button_pin, flags);
	if (err < 0) {
		LOG_ERR("Error %d: failed to configure button gpio pin %d\n", err, button_pin);
		return err; 
	} 

	err = gpio_pin_interrupt_configure(gpio_dev, button_pin, interrupts);
	if (err < 0){
		LOG_ERR("Error %d: failed to configure button callback on pin %d\n", err, button_pin);
		return err;
	}

	gpio_init_callback(&button_interupt_cb, button_interrrupt_handler ,BIT(button_pin));

	err = gpio_add_callback(gpio_dev, &button_interupt_cb);
	if (err < 0) {
		LOG_ERR("Error adding callback for button change: (err %d)\n", err);
		return err; 
	}

	return 0;
}

/** @brief initilizes the GPIO for an slider switch input
 * 
 * 	Initlizes the pin input for a slider switch 
 *  @param gpio_dev device structure that contains the device tree information for the gpio peripheral 
 *  @param switch_pin Pin value on the board for the button input
 *   
 *  @return status code. 0 if successfull <0 if failed 
 *
*/

int init_select_switch(const struct device* gpio_dev, int switch_pin){
	int err;
	gpio_flags_t flags = GPIO_INPUT | GPIO_ACTIVE_HIGH;

	err = gpio_pin_configure(gpio_dev, switch_pin, flags);
	if (err < 0) {
		LOG_ERR("Error %d: failed to configure switch gpio pin %d\n", err, switch_pin);
		return err; 
	} 

	return 0;
}



/** @brief  callback function for the wristing paring button
 * 
 *  Allow the bluetooth system to look for the wrist module (must be a right boot board)
 *  Act like a central to connect to the wrist module
 *  
 *  @param port: device binding device structure 
 *  @param gpio_callback: structure that is used to register callback function in the config stage
 *  @param pins: bitwise repersentation of what pin callback has occured. 
 *  
 *  implement concurrency control to ensure that the updates occur correctly
*/

void phone_pairing_button_cb(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
{
	LOG_INF("IN the Phone pairng callback");
	//check what the boot mode is 
	if (isRightBoot){
		LOG_INF("Advertising right boot for phone connection");
		// use the scanning options
		k_work_submit(&advertise_phone_work);
	} 
};


/** @brief  callback function for the pairing of the boot button
 *
 * 	check what boot module you are and then start the bluetooth system as needed
 *  - L: act like a peripheral --> advertise the L name and UART service
 *  - R: act like a central --> scan using fillters for UUID with the UART service 
 *  
 *  @param port: device binding device structure 
 *  @param gpio_callback: structure that is used to register callback function in the config stage
 *  @param pins: bitwise repersentation of what pin callback has occured. 
 *  
 *  implement concurrency control to ensure that the updates occur correctly
*/

void boot_pairing_button_cb(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins){
	// check if the correct interrupt has gone off
	// I think the documentation states that only the pins set with the call back will call it. 
	// If the call back is unique then only one pin can activate it. 

	LOG_INF("IN the BOOT pairing callback");
	//check what the boot mode is 
	if (isRightBoot){
		LOG_INF("SCANNING FOR L boot");
		// use the scanning options
		k_work_submit(&Lboot_scan_work);
	} else {
		//left boot operation is being focused on 
		LOG_INF("ADVERTISING L BOOT");
		k_work_submit(&advertise_L_boot_work);

	}
	
};