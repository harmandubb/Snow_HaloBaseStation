#include "UART_bt_control.h"

LOG_MODULE_REGISTER(UART_bt_control, LOG_LEVEL_INF);

bool UARTSendEnable = false;
bool UARTFinished = false; 
 
uint8_t uart_rx_data[UART_BUF_SIZE] = {0};
K_MUTEX_DEFINE(uart_data_mutex);

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
	// LOG_INF("Received Data from UART");
	ARG_UNUSED(nus);

	int err = 0; 

	for (uint16_t i = 0; i < len; i++){
		k_mutex_lock(&uart_data_mutex,K_FOREVER);
		uart_rx_data[i] = data[i];
		k_mutex_unlock(&uart_data_mutex);
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

/** @brief Convert broken UART transmission values to a full UART resoltuion 
 * 	 
 * 	@param msb_val most signigifaicant bit number
 *  @param lsb_val least significant bit numer
 * 
 *  @return return a full resolution value 
 */

uint16_t UART_full_resolution_converter(uint8_t msb_val, uint8_t lsb_val){
	return (msb_val << 8) | lsb_val;
};

/** @brief Split a full UART resolution value into MSB and LSB
 * 
 *  @param full_val Full 16-bit resolution value to be split
 *  @param msb_val Pointer to store the most significant byte
 *  @param lsb_val Pointer to store the least significant byte
 */
void UART_split_resolution(uint16_t full_val, uint8_t *msb_val, uint8_t *lsb_val) {
    *msb_val = (full_val >> 8) & 0xFF; // Extract the MSB (upper 8 bits)
    *lsb_val = full_val & 0xFF;       // Extract the LSB (lower 8 bits)
}


