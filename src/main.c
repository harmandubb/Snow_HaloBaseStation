#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>
#include <stdlib.h>

#include "led_control.h"
#include "adc_control.h"
#include "bluetooth_control.h"
#include "button_control.h"

#include <math.h>

#define NUM_SENSORS (2)
#define ADC_BUFFER_SIZE (NUM_SENSORS*2)

// GPIO0 - adc read pins
#define PIN_ADC_READ_0 (2)
#define PIN_ADC_READ_1 (3)
#define PIN_ADC_READ_2 (28)
#define PIN_ADC_READ_3 (29)
#define PIN_ADC_READ_4 (4)
#define PIN_ADC_READ_5 (5)

// GPIO1
#define PIN_L_R_SELECT_BUTTON (15)
//PIN_WRIST_PAIRING_BUTTON in button_control.h file


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
        static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

        struct adc_sequence_options opts = {
                .interval_us = 0,
                .callback = my_adc_sequence_callback,
                .user_data = NULL, 
                .extra_samplings = 0,
                
        };
        uint16_t adc_buf[ADC_BUFFER_SIZE] = {0};
        
	struct adc_sequence sequence = {
		.buffer = &adc_buf,
		.buffer_size = sizeof(adc_buf),
		//Optional
		//.calibrate = true, //turn on calibration after the bare minimum code is active
                .options = &opts,
                .channels = (1 << NUM_SENSORS) - 1,
	};

        err = adc_channel_setup_dt(&adc_channel);
        if (err < 0) {
                LOG_ERR("Could not setup channel #%d (%d)", 0, err);
                return NULL;
        }

        err = adc_sequence_init_dt(&adc_channel, &sequence);
        if (err < 0) {
                LOG_ERR("Could not initalize sequnce");
                return NULL;
        }
        err = adc_read(adc_channel.dev, &sequence);
        if (err < 0) {
                LOG_ERR("Could not read (%d)", err);
                return NULL; 
        }

        while(!adcReady);
        LOG_INF("ADC INITALIZATION DONE\n");
        adcReady = false; 

        //----------------------PAIRING BUTTON INIT--------------------------//
        err = init_pairing_button(gpio1_dev,PIN_WRIST_PAIRING_BUTTON,wrist_pairing_button_cb);
        if (err) {
                LOG_ERR("ERROR Intializing L_R pairing button: %d", err);
        }

        //-----------------------BLUETOOTH SCAN----------------------//
        // err = bt_enable(bt_ready_cb);
	// if (err) {
	// 	LOG_ERR("Bluetooth init failed (err %d)", err);
	// 	return 0;
	// }

        // struct bt_conn_cb cb = {
        //         .connected = connected,
        //         .disconnected = disconnected,
        //         .security_changed = on_security_changed,
        // };

        // bt_conn_cb_register(&cb);

        // while(!btReady);

        // err = settings_load();
        // if (err) {
        //         LOG_ERR("Settings load failed (err %d)", err);
        // }

	// const struct bt_scan_init_param bt_scan_init_opts = {
	// 		.scan_param = NULL, //default config 
	// 		.connect_if_match = true,
	// 		.conn_param = NULL, //default config
	// };
	
	// bt_scan_init(&bt_scan_init_opts); 
        // BT_SCAN_CB_INIT(scan_cb, scan_filter_match, scan_filter_no_match, scan_connecting_error, scan_connecting);
        // bt_scan_cb_register(&scan_cb);

        // //------------------------BOND Devices Scan Check------------//
        // int bond_connect_counter = 0 ; 
        // int bond_count = scan_bond_devices();
        // LOG_INF("Scanning successfully started");
        // LOG_INF("bond count: %d", bond_count);

        // while((bond_count > 0) && (bond_connect_counter < BOND_CONNECT_COUNT_THRESHOLD) && (!connectedFlag)){
        //         k_sleep(K_MSEC(500));
        //         bond_connect_counter++;
        // }

        // if (!connectedFlag) {
        //         //stop the bond scanning 
        //         err = bt_scan_stop();
        //         if (err < 0) {
        //                 LOG_ERR("Unable to stop bond scanning");
        //         }
        // }

        

        //--------------SCAN TESTING END---------------------//

        *led_operation_ptr = BOARD_ALIVE;

        for(;;){

        //         if (sensorDataRequested == false) {
        //                 //send the reques to the adc to read
        //                 err = request_sensor_data(gpio0_dev, &adc_channel, adc_sel_pins, NUM_ADC_SEL_PINS, checkSensorNum, NUM_SENSORS, &sequence);
        //                 if (err < 0){
        //                         LOG_ERR("Failed to request the sensor data (err %d)\n", err);
        //                 }

        //                 sensorDataRequested = true; 
        //         }

        //         if(adcReady){
        //                 //update the array of the sensor value 
        //                 adc_read_val = adc_buf[0];


        //                 if (adc_read_val > 65000){
        //                         adc_read_val = 0; 
        //                 }

        //                 LOG_INF("Sensor Checked: %d", checkSensorNum);
        //                 LOG_INF("BUFF 0: %d", adc_read_val);

        //                 //print out the sensor values that are present
        //                 sensorPressureMap[checkSensorNum] = adc_read_val; 

        //                 LOG_INF("PRESSURE VALS: 0: %d, 1: %d, 2: %d, 3: %d", sensorPressureMap[0], sensorPressureMap[1], sensorPressureMap[2], sensorPressureMap[3]);

        //                 //calculate the pressure difference 
        //                 pressureDiff = calculate_pressure_diffrential(checkSensorNum, adc_read_val, NUM_SENSORS);

        //                 LOG_INF("Pressure Diff: %d", pressureDiff);
        //                 if (abs(pressureDiff) > PRESSURE_INTEGRATOR_CEILING){
        //                         pressureDiff = (pressureDiff/(abs(pressureDiff))) * PRESSURE_INTEGRATOR_CEILING;
        //                 }

        //                 //based on the pressureDiff decide which side to turn on
        //                 turnOnLeftSide = false; 
        //                 turnOnRightSide = false; 
        //                 if (abs(pressureDiff) > PRESSURE_THRESHOLD) {
        //                         //yes something need to turn on
        //                         if(pressureDiff > 0) {
        //                                 turnOnRightSide = true;
        //                         } else {
        //                                 turnOnLeftSide = true; 
                                        
        //                         }
        //                 }

        //                 //update the led as needed 
        //                 update_board_led_pressure(led_board_map, turnOnLeftSide, turnOnRightSide);
                        
        //                 if(ledHandleReady){
        //                         updateWristLED(turnOnRightSide);        
        //                 }

        //                 checkSensorNum = (checkSensorNum + 1) % NUM_SENSORS;
        //                 adcReady = false; 
        //                 sensorDataRequested = false; 
        //         }

                //electronics status indicator
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


