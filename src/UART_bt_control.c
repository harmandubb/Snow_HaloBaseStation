#include "UART_bt_control.h"

LOG_MODULE_REGISTER(UART_bt_control, LOG_LEVEL_INF);

bool UARTSendEnable = false;
bool UARTFinished = false; 

K_FIFO_DEFINE(fifo_uart_rx_data);

/** @brief Callback function for when the UART transmission is completed
 *  
 *  @param[in] conn Pointer to connection object, or NULL if sent to all
 *                 connected peers. 
 */
void sent_uart_cb(struct bt_conn *conn) {
    LOG_INF("UART data successfully sent");
    UARTFinished = true; 

}

/** @brief Callback function to check if the central has accepted notifications,
 *         allowing the rest of the system to start working.
 *  
 *  @param[in] status Send notification status.
 */
void send_enable_uart_cb(enum bt_nus_send_status status) {
    if (status == BT_NUS_SEND_STATUS_ENABLED) {
        LOG_INF("The UART connection is successful");
        UARTSendEnable = true; 
    } else {
        LOG_ERR("The UART connection failed");
    }
}

//Callback for accepting the incoming uart data over ble

uint8_t ble_uart_data_received(struct bt_nus_client *nus, const uint8_t *data, uint16_t len){
	LOG_INF("Received Data from UART");
	ARG_UNUSED(nus);

	int err = 0; 

	for (uint16_t i = 0; i < len; i++){
		k_fifo_put(&fifo_uart_rx_data,data[i]); //see if a type should be cast to the fifo to do some porcessing
	}

	return BT_GATT_ITER_CONTINUE; 
};

/** @brief initialize the nuse client module for receiving information 
 * 
 *  
 *  @return error is present 
 */

int nus_client_init(){
	int err = 0; 
	static struct bt_nus_client_init_param init = {
		.cb = {
			.received = ble_uart_data_received,
		}
	};

	err = bt_nus_client_init(&nus_client, &init);
	if (err < 0){
		LOG_ERR("NUS Client Initilaizaiton failed (err %d)", err);
		return err; 
	}

	LOG_INF("NUS Client module initilized");
	return err; 
}



