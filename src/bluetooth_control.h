#ifndef BLUETOOTH_CONTROL_H
#define BLUETOOTH_CONTROL_H

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/settings/settings.h>
#include <bluetooth/services/lbs.h>
#include <zephyr/bluetooth/gatt.h>

#include <bluetooth/scan.h>



//function defines: 
void setup_accept_list_cb(const struct bt_bond_info *info, void *user_data);
int setup_accept_list(uint8_t local_id);
void unpair(struct k_work *work); 
extern struct k_work unpair_work; 
extern bool ledHandleReady;
extern struct bt_conn *wrist_conn;

void scan_filter_match(struct bt_scan_device_info *device_info, struct bt_scan_filter_match *filter_match, bool connectable);
void scan_filter_no_match(struct bt_scan_device_info *device_info, bool connectable);
void scan_connecting(struct bt_scan_device_info *device_info, struct bt_conn *conn);
void scan_connecting_error(struct bt_scan_device_info *device_info);
int init_bt_scan();


void connected(struct bt_conn *conn, uint8_t err);
void disconnected(struct bt_conn *conn, uint8_t reason);
uint8_t discover_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr, struct bt_gatt_discover_params *params);
int updateWristLED(bool led_on);

#endif /* BLUETOOTH_CONTROL_H */