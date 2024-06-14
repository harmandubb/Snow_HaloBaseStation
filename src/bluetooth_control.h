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
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/gap.h>
#include <bluetooth/services/lbs.h>

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME)-1)
#define COMPANY_ID_CODE (0x0059)

//Defining advertising parametert with no accept list 
#define BT_LE_ADV_CONN_NO_ACCEPT_LIST  BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONNECTABLE|BT_LE_ADV_OPT_ONE_TIME, \
				       BT_GAP_ADV_FAST_INT_MIN_2, \
				       BT_GAP_ADV_FAST_INT_MAX_2, NULL)

//defining advertising parameters with accept list
#define BT_LE_ADV_CONN_ACCEPT_LIST BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONNECTABLE|BT_LE_ADV_OPT_FILTER_CONN|BT_LE_ADV_OPT_ONE_TIME, \
				       BT_GAP_ADV_FAST_INT_MIN_2, \
				       BT_GAP_ADV_FAST_INT_MAX_2, NULL)

typedef struct adv_mfg_data {
	uint16_t company_code;	    /* Company Identifier Code. */
} adv_mfg_data_type;


static adv_mfg_data_type adv_mfg_data = {COMPANY_ID_CODE};



//function defines: 
void setup_accept_list_cb(const struct bt_bond_info *info, void *user_data);
int setup_accept_list(uint8_t local_id);
void advertise_with_acceptlist(struct k_work *work);
void advertise_without_acceptlist(struct k_work *work);
void unpair(struct k_work *work);

extern struct k_work advertise_acceptlist_work;
extern struct k_work advertise_work; 
extern struct k_work unpair_work; 

#endif /* BLUETOOTH_CONTROL_H */