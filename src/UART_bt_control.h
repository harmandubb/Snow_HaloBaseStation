#ifndef UART_BT_CONTROL_H
#define UART_BT_CONTROL_H

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <bluetooth/services/nus.h>
#include <bluetooth/services/nus_client.h>
#include <zephyr/logging/log.h>

#include "boot_bt_connect.h"

// External variables
extern bool UARTSendEnable; 
extern bool UARTFinished; 
extern struct k_fifo fifo_uart_rx_data; 


// Function declarations
void sent_uart_cb(struct bt_conn *conn);
void send_enable_uart_cb(enum bt_nus_send_status status);
int UART_gatt_discover(struct bt_conn *conn);
int nus_client_init();

#endif /* UART_BT_CONTROL_H */
