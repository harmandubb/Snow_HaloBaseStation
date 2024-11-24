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
extern struct k_mutex uart_data_mutex; 
extern uint8_t uart_rx_data[];


// Function declarations
void sent_uart_cb(struct bt_conn *conn);
void send_enable_uart_cb(enum bt_nus_send_status status);
int UART_gatt_discover(struct bt_conn *conn);
int nus_client_init();
uint16_t UART_full_resolution_converter(uint8_t msb_val, uint8_t lsb_val);
void UART_split_resolution(uint16_t full_val, uint8_t *msb_val, uint8_t *lsb_val);

#endif /* UART_BT_CONTROL_H */
