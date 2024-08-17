#include "UART_bt_control.h"

bool UARTConnectionReady = false; 


/** @brief Callback function for the UART transmitt has been completed that provides info that the transmission has worked
 *  
 *  @param[in] conn Pointer to connection object, or NULL if sent to all
 *                 connected peers. 
 */

void sent_uart_cb(struct bt_conn *conn){
    LOG_INF("UART data successfully sent");
};

/** @brief Callback function to see if the central has accepted notifications to received trasnmissions that allows the rest of the system to start working
 *  
 *  @param[in] status Send notification status.
 */

void send_enable_uart_cb(enum bt_nus_send_status status){
    if(status == BT_NUS_SEND_STATUS_ENABLED){
        LOG_INF("The UART connection is successful");
        UARTConnectionReady = true; 
    } else {
        LOG_ERR("The UART connection failed");
    }
};


