#include "UART_bt_control.h"

LOG_MODULE_REGISTER(UART_bt_control, LOG_LEVEL_INF);

bool UARTSendEnable = false;
bool UARTFinished = false; 

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
