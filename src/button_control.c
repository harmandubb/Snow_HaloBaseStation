#include "button_control.h"


LOG_MODULE_REGISTER(Button_Control, LOG_LEVEL_INF);

//Global variables 
int timer_hold_intervals = 0; 
K_MUTEX_DEFINE(button_hold_mutex);
K_TIMER_DEFINE(button_hold_timer,button_timer_expire_cb,NULL);

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

	err = gpio_pin_configure(gpio_dev, switch_pin, 0);
	if (err < 0) {
		LOG_ERR("Error %d: failed to configure switch gpio pin %d\n", err, switch_pin);
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

void button_timer_expire_cb(struct k_timer *timer){
	k_mutex_lock(&button_hold_mutex,K_FOREVER);
	timer_hold_intervals++;
	LOG_INF("Timer_Hold_Intervals: %d", timer_hold_intervals);
	k_mutex_unlock(&button_hold_mutex);
};

/** @brief  callback function for the pairing button for the L/R boot side
 * 
 *  Allow the bluetooth scanning to occur to accept a new L/R Connection. 
 *  Delete the previously exisitng L/R connection of the system. 
 *  
 *  @param port: device binding device structure 
 *  @param gpio_callback: structure that is used to register callback function in the config stage
 *  @param pins: bitwise repersentation of what pin callback has occured. 
 *  
*/

void boot_pairing_button_cb(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins){
	LOG_INF("In the pairing button callback");
    
    uint32_t pin_vals = 0;
    int err = gpio_port_get(port, &pin_vals);
    if (err != 0) {
        LOG_ERR("Error: Unable to get GPIO port levels (err: %d)", err);
        return;  // Consider returning early on error
    }

	if (pin_vals & BIT(PIN_BOOT_PAIRING_BUTTON)){
		LOG_INF("Adding additional device");
        k_work_submit(&scan_standard_work);
	} 


}



/** @brief  callback function for the pairing button
 * 
 *  Allow the bluetooth scanning to occur to accept a new wrist module
 *  TODO: Make the button keep a time state for deleting all of the connections 
 *  
 *  @param port: device binding device structure 
 *  @param gpio_callback: structure that is used to register callback function in the config stage
 *  @param pins: bitwise repersentation of what pin callback has occured. 
 *  
 *  implement concurrency control to ensure that the updates occur correctly
*/

void wrist_pairing_button_cb(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
{
    LOG_INF("In the pairing button callback");
    
    uint32_t pin_vals = 0;
    int err = gpio_port_get(port, &pin_vals);
    if (err != 0) {
        LOG_ERR("Error: Unable to get GPIO port levels (err: %d)", err);
        return;  // Consider returning early on error
    }

    k_mutex_lock(&button_hold_mutex, K_FOREVER);  // Use K_FOREVER instead of K_NO_WAIT

    if (pin_vals & BIT(PIN_WRIST_PAIRING_BUTTON)) {
        LOG_INF("Button Pressed: starting hold timer");
        k_timer_start(&button_hold_timer, K_MSEC(100), K_SECONDS(1));      
    } else if (!(pin_vals & BIT(PIN_WRIST_PAIRING_BUTTON)) && timer_hold_intervals > 0) {
        LOG_INF("Button Release: stopping timer");
        k_timer_stop(&button_hold_timer);
        
        switch (timer_hold_intervals) {
            case 0:
                // debounce
                break;
            case 1:
                LOG_INF("Adding additional device");
                k_work_submit(&scan_standard_work);
                break;
            default:
                LOG_INF("Unpairing devices and then adding additional device");
				k_work_submit(&bt_disconnect_all_work);
				k_work_submit(&unpair_work);
				k_work_submit(&scan_standard_work);
                break;
        }
        
        timer_hold_intervals = 0;
    }

    k_mutex_unlock(&button_hold_mutex);
}


