#ifndef UART_BT_CONTROL_H
#define UART_BT_CONTROL_H

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <bluetooth/services/nus.h>
#include <bluetooth/services/nus_client.h>
#include <zephyr/logging/log.h>

// External variables
extern bool UARTSendEnable; 
extern bool UARTFinished; 

// Function declarations
void sent_uart_cb(struct bt_conn *conn);
void send_enable_uart_cb(enum bt_nus_send_status status);

#endif /* UART_BT_CONTROL_H */
