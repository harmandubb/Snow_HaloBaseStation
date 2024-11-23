#ifndef IPHONE_BT_CONNECT_H
#define IPHONE_BT_CONNECT_H

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/settings/settings.h>
#include <bluetooth/services/nus.h>
#include <bluetooth/services/nus_client.h>
#include <zephyr/bluetooth/gatt.h>


#include <bluetooth/scan.h>
#include <bluetooth/gatt_dm.h>

#include "led_control.h"

#define DEVICE_BOARD_HALO_L "BOARD_HALO_L"
#define DEVICE_BOARD_HALO_R "BOARD_HALO_R"
#define UART_BUF_SIZE (100)

//Defining advertising parametert with no accept list 
#define BT_LE_ADV_CONN_NO_ACCEPT_LIST  BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONNECTABLE|BT_LE_ADV_OPT_ONE_TIME, \
				       BT_GAP_ADV_FAST_INT_MIN_2, \
				       BT_GAP_ADV_FAST_INT_MAX_2, NULL)

//defining advertising parameters with accept list
#define BT_LE_ADV_CONN_ACCEPT_LIST BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONNECTABLE|BT_LE_ADV_OPT_FILTER_CONN|BT_LE_ADV_OPT_ONE_TIME, \
				       BT_GAP_ADV_FAST_INT_MIN_2, \
				       BT_GAP_ADV_FAST_INT_MAX_2, NULL)

//external variables
extern struct k_work advertise_phone_work; 

//function defines: 

#endif /* IPHONE_BT_CONNECT_H */