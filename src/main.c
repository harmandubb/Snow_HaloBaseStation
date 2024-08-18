#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>
#include <stdlib.h>

#include "led_control.h"
#include "adc_control.h"
#include "bluetooth_control.h"
#include "button_control.h"
#include "UART_bt_control.h"

#include <math.h>



// GPIO0 - adc read pins
#define PIN_ADC_READ_0 (2)
#define PIN_ADC_READ_1 (3)
#define PIN_ADC_READ_2 (28)
#define PIN_ADC_READ_3 (29)
#define PIN_ADC_READ_4 (4)
#define PIN_ADC_READ_5 (5)

// GPIO1
//PIN_BOOT_DEFINE_SWITCH in the button_control.h file
//PIN_BOOT_PAIRING_BUTTON in the button_control.h file
//PIN_WRIST_PAIRING_BUTTON in button_control.h file

#define BOND_CONNECT_COUNT_THRESHOLD (4) //number of half second period to try bonding before giving up


// FUNCTION DEFINITIONS

void pairing_button_cb(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins);
void bt_ready_cb(int err);

LOG_MODULE_REGISTER(base_station, LOG_LEVEL_INF);

//flags
bool btReady = false; 

int main(void)
{
        k_sleep(K_SECONDS(3));
        //Setup
        int err = 0; 

        //flags 
        extern bool isRightBoot; 
        bool requestFinished = true; 
        extern bool adcFinished;
        extern bool UARTFinished; 
        extern bool UARTSendEnable; 
        
        //variables
        
        
        
        //get the gpio binding
        const struct device *gpio0_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));
	if (gpio0_dev == NULL) {
		LOG_ERR("Device binding is not found\n");
		return -1; 
	}

        const struct device *gpio1_dev = DEVICE_DT_GET(DT_NODELABEL(gpio1));
	if (gpio1_dev == NULL) {
		LOG_ERR("Device binding is not found\n");
		return -1; 
	}

        //------------------------LED INIT------------------------//
        // on board status led
        err = dk_leds_init();
	if (err) {
		printk("LEDs init failed (err %d)\n", err);
		return 0;
	}



        // ---------------------------ADC INIT---------------------------//

        // //initalize the adc device tree variable 
        static const struct adc_dt_spec adc_channel_0 = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user),0);
        static const struct adc_dt_spec adc_channel_1 = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user),1);
        static const struct adc_dt_spec adc_channel_2 = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user),2);
        static const struct adc_dt_spec adc_channel_3 = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user),3);
        static const struct adc_dt_spec adc_channel_4 = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user),4);
        static const struct adc_dt_spec adc_channel_5 = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user),5);

        const struct device *adc_dev = DEVICE_DT_GET(DT_NODELABEL(adc));

        if(!adc_is_ready_dt(&adc_channel_0)){
                LOG_ERR("ADC controller device %s not ready", adc_channel_0.dev->name);
        }

        if(!adc_is_ready_dt(&adc_channel_1)){
                LOG_ERR("ADC controller device %s not ready", adc_channel_1.dev->name);
        }

        if(!adc_is_ready_dt(&adc_channel_2)){
                LOG_ERR("ADC controller device %s not ready", adc_channel_2.dev->name);
        }

        if(!adc_is_ready_dt(&adc_channel_3)){
                LOG_ERR("ADC controller device %s not ready", adc_channel_3.dev->name);
        }

        if(!adc_is_ready_dt(&adc_channel_4)){
                LOG_ERR("ADC controller device %s not ready", adc_channel_4.dev->name);
        }

        if(!adc_is_ready_dt(&adc_channel_5)){
                LOG_ERR("ADC controller device %s not ready", adc_channel_5.dev->name);
        }

        err = adc_channel_setup_dt(&adc_channel_0);
        if (err < 0) {
                LOG_ERR("Could not setup channel #%d (%d)", 0, err);
                return 0;
        }

        err = adc_channel_setup_dt(&adc_channel_1);
        if (err < 0) {
                LOG_ERR("Could not setup channel #%d (%d)", 0, err);
                return 0;
        }

        err = adc_channel_setup_dt(&adc_channel_2);
        if (err < 0) {
                LOG_ERR("Could not setup channel #%d (%d)", 0, err);
                return 0;
        }

        err = adc_channel_setup_dt(&adc_channel_3);
        if (err < 0) {
                LOG_ERR("Could not setup channel #%d (%d)", 0, err);
                return 0;
        }

        err = adc_channel_setup_dt(&adc_channel_4);
        if (err < 0) {
                LOG_ERR("Could not setup channel #%d (%d)", 0, err);
                return 0;
        }

        err = adc_channel_setup_dt(&adc_channel_5);
        if (err < 0) {
                LOG_ERR("Could not setup channel #%d (%d)", 0, err);
                return 0;
        }

        struct adc_sequence_options opts = {
                .interval_us = 0,
                .callback = my_adc_sequence_callback,
                .user_data = NULL, 
                .extra_samplings = 0,
                
        };
        uint8_t adc_buf[ADC_BUFFER_SIZE] = {0};
        
	struct adc_sequence sequence = {
		.buffer = &adc_buf,
		.buffer_size = sizeof(adc_buf),
		//Optional
		//.calibrate = true, //turn on calibration after the bare minimum code is active
                .options = &opts,
                .channels = (1 << NUM_SENSORS) - 1,
                .resolution = 12,
	};

        err = adc_read(adc_dev, &sequence);
        if (err < 0) {
                LOG_ERR("Could not read (%d)", err);
                return -1; 
        }

        //test the adc read 
        for (int i = 0; i < ADC_BUFFER_SIZE; i++){
                LOG_INF("INDEX: %d -- VALUE: %d", i, adc_buf[i]);
        }

        while(!adcFinished);
        LOG_INF("ADC INITALIZATION DONE\n"); 

        //----------------------GPIO INIT--------------------------//
        //---------------------BUTTON INIT-------------------------//
        err = init_pairing_button(gpio1_dev,PIN_WRIST_PAIRING_BUTTON, wrist_pairing_button_cb);
        if (err < 0) {
                LOG_ERR("ERROR Intializing wrist pairing button: %d", err);
        }

        err = init_pairing_button(gpio1_dev, PIN_BOOT_PAIRING_BUTTON, boot_pairing_button_cb);
        if (err < 0){
                LOG_ERR("ERROR Inializing L_R pairing button: %d", err);
        }

        //---------------------SWITCH INIT----------------------//
        err = init_select_switch(gpio1_dev, PIN_BOOT_DEFINE_SWITCH);
        if (err < 0) {
                LOG_ERR("ERR Initializing L_R define switch: %d", err);
        }

        err = gpio_pin_get(gpio1_dev,PIN_BOOT_DEFINE_SWITCH);
        LOG_INF("Switch Result: %d", err);
        if (err < 0){
                LOG_ERR("ERROR getting state L_R define switch: %d", err);
        } else if(err == 1){
                isRightBoot = true; 
                LOG_INF("Right Boot Present");
        } else {
                isRightBoot = false; 
                LOG_INF("Left Boot Present");
        }
        //-----------------BLUETOOTH -----------------------//

        
        //-----------------------BLUETOOTH SCAN----------------------//
        err = bt_enable(bt_ready_cb);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return 0;
	}

        struct bt_conn_cb cb = {
                .connected = connected,
                .disconnected = disconnected,
                .security_changed = on_security_changed,
        };

        bt_conn_cb_register(&cb);

        while(!btReady);

        err = settings_load();
        if (err) {
                LOG_ERR("Settings load failed (err %d)", err);
        }

        //enable to be a central 
        const struct bt_scan_init_param bt_scan_init_opts = {
                .scan_param = NULL, //default config 
                .connect_if_match = true,
                .conn_param = NULL, //default config
        };

        bt_scan_init(&bt_scan_init_opts); 
        BT_SCAN_CB_INIT(scan_cb, scan_filter_match, scan_filter_no_match, scan_connecting_error, scan_connecting);
        bt_scan_cb_register(&scan_cb);

        //------------------------BOND Devices Scan Check------------//
        int bond_connect_counter = 0 ; 
        int bond_count = scan_bond_devices();
        LOG_INF("Scanning successfully started");
        LOG_INF("bond count: %d", bond_count);

        while((bond_count > 0) && (bond_connect_counter < BOND_CONNECT_COUNT_THRESHOLD) && (!connectedFlag)){
                k_sleep(K_MSEC(500));
                bond_connect_counter++;
        }

        if (!connectedFlag) {
                //stop the bond scanning 
                err = bt_scan_stop();
                if (err < 0) {
                        LOG_ERR("Unable to stop bond scanning");
                }
        }

        if(isRightBoot){

        } else {
                struct bt_nus_cb uart_cb = {
                        .sent = sent_uart_cb,
                        .send_enabled = send_enable_uart_cb,

                };

                //LEFT BOOTH SET UP 
                err = bt_nus_init(&uart_cb);
                if(err < 0){
                        LOG_ERR("ERROR UART service init error: %d", err);
                }

        }

        *led_operation_ptr = BOARD_ALIVE;

        for(;;){

                LOG_INF("requestFinsihed: %d, adcFinished: %d, UARTFinished: %d, isRightBoot: %d, UARTSendEnable: %d",requestFinished, adcFinished, UARTFinished, isRightBoot, UARTSendEnable);

                if(requestFinished){
                        requestFinished = false;  
                        adcFinished = false; 
                        UARTFinished = false; 
                        err = adc_read(adc_dev, &sequence);
                        if (err < 0) {
                                LOG_ERR("Could not read (%d)", err);
                                return -1; 
                        }
                }

                if(adcFinished){
                        if(!isRightBoot && UARTSendEnable){
                                //send information through uart
                                err = bt_nus_send(NULL, adc_buf, ADC_BUFFER_SIZE);
                                if (err < 0){
                                        LOG_ERR("Error UART Send: %d", err);
                                } 
                        }

                }

                if(UARTFinished){
                        requestFinished = true; 
                }
                
                status_led_operation(*led_operation_ptr);

        }
        return 0;
}

/** @brief  callback function to show the user is a connection has been made or not and set flag to allow the code to begin bluetooth activites
 * 
 *     
 *  @param err: error present with the connection if at all. 
 *  
*/

void bt_ready_cb(int err){
        if (err < 0){
                LOG_ERR("Error with enabling the bluetooth module (err: %d)", err);
        } else {
                LOG_INF("Bluetooth initialized");
        }

        btReady = true; 

}


