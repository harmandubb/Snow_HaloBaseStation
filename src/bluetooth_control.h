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

#include <bluetooth/scan.h>



//function defines: 
void setup_accept_list_cb(const struct bt_bond_info *info, void *user_data);
int setup_accept_list(uint8_t local_id);
void unpair(struct k_work *work); 
extern struct k_work unpair_work; 

void scan_filter_match(struct bt_scan_device_info *device_info, struct bt_scan_filter_match *filter_match, bool connectable);
void scan_filter_no_match(struct bt_scan_device_info *device_info, bool connectable);
void scan_connecting(struct bt_scan_device_info *device_info, struct bt_conn *conn);
void scan_connecting_error(struct bt_scan_device_info *device_info);
int init_bt_scan();

#endif /* BLUETOOTH_CONTROL_H */