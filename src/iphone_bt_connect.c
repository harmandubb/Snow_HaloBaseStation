#include "iphone_bt_connect.h"

LOG_MODULE_REGISTER(iphone_bt_connect, LOG_LEVEL_INF);

static const struct bt_data 
iphone_ad[] = {
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL|BT_LE_AD_NO_BREDR)), 
        BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_BOARD_HALO_R, sizeof(DEVICE_BOARD_HALO_R)),
		
};

static const struct bt_data iphone_sd[] = {
        BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_NUS_VAL),
};

// TODO: launch the advertising ment work for the iphone connect

/** @brief work for advertising to phone for data output
 * 
 * 	@param: work parameter for defining work
 * 
 */
void advertise_to_phone(struct k_work *work){
	int err_code = bt_le_adv_stop();
	if (err_code) {
		LOG_ERR("Cannot stop advertising err= %d \n", err_code);
		return;
	}

	err_code = bt_le_adv_start(BT_LE_ADV_CONN_NO_ACCEPT_LIST, iphone_ad, ARRAY_SIZE(iphone_ad), iphone_sd, ARRAY_SIZE(iphone_sd));
	if (err_code) {
		LOG_ERR("Cannot start open advertising for phone connection(err: %d)\n", err_code);
	} else	{
		LOG_INF("Advertising for Phone Connection Started");
	}
};

K_WORK_DEFINE(advertise_phone_work, advertise_to_phone);

