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
#include <bluetooth/services/nus.h>
#include <bluetooth/services/nus_client.h>
#include <zephyr/bluetooth/gatt.h>

#include <bluetooth/scan.h>

#define TARGET_DEVICE_NAME "SNOW"

//struct definitions
struct bond_count_data {
	int count;
};

//external variables
extern bool ledHandleReady;
extern struct bt_conn *wrist_conn;
extern uint8_t read_data[100];
extern bool connectedFlag; 
extern struct k_work unpair_work; 
extern struct k_work scan_standard_work;
extern struct k_work bt_disconnect_all_work; 
extern struct k_work scan_L_boot_work;

//function defines: 
void setup_accept_list_cb(const struct bt_bond_info *info, void *user_data);
int setup_accept_list(uint8_t local_id);
void unpair(); 

void scan_filter_match(struct bt_scan_device_info *device_info, struct bt_scan_filter_match *filter_match, bool connectable);
void scan_filter_no_match(struct bt_scan_device_info *device_info, bool connectable);
void scan_connecting(struct bt_scan_device_info *device_info, struct bt_conn *conn);
void scan_connecting_error(struct bt_scan_device_info *device_info);

void connected(struct bt_conn *conn, uint8_t err);
void disconnected(struct bt_conn *conn, uint8_t reason);
void on_security_changed(struct bt_conn *conn, bt_security_t level, enum bt_security_err err);

uint8_t discover_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr, struct bt_gatt_discover_params *params);
int updateWristLED(bool led_on);
int readWristLED();
void print_uuid(const struct bt_uuid *uuid);
uint8_t gatt_read_func(struct bt_conn *conn, uint8_t err, struct bt_gatt_read_params *params, const void *data, uint16_t length);

void bond_initial_cb(const struct bt_bond_info *info, void *user_data);
void scan_standard(struct k_work *work);

void force_disconnect_cb(struct bt_conn *conn, void *data);
void bt_disconnect_all(struct k_work *work);

#endif /* BLUETOOTH_CONTROL_H */