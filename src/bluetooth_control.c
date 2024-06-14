#include "bluetooth_control.h"

LOG_MODULE_REGISTER(bluetooth_control, LOG_LEVEL_INF);

static const struct bt_data 
ad[] = {
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL|BT_LE_AD_NO_BREDR)), //not the classif bluetooth operation
        BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
        BT_DATA(BT_DATA_MANUFACTURER_DATA,(unsigned char *)&adv_mfg_data, sizeof(adv_mfg_data)),
};

static const struct bt_data sd[] = {
        BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_LBS_VAL),
};                       

/** @brief for each bond present the device is added to an accept list
 * 
 * 
 *  @param info: Local identity (mostly just BT_ID_DEFAULT). 
 *  @param user_dat: passed the current count of the number of bonds that are accounted for in the accept list 
 * 
*/
void setup_accept_list_cb(const struct bt_bond_info *info, void *user_data)
{
	int *bond_cnt = user_data;
	if ((*bond_cnt) < 0) {
		return;
	}
	int err = bt_le_filter_accept_list_add(&info->addr);
	printk("Added following peer to whitelist: %x %x \n",info->addr.a.val[0],info->addr.a.val[1]);
	if (err) {
		printk("Cannot add peer to Filter Accept List (err: %d)\n", err);
		(*bond_cnt) = -EIO;
	} else {
		(*bond_cnt)++;
	}

}

/** @brief set up an accept list for bluetooth advertising  
 * 
 * 	The function iterates over all of the bond information stored in the flash memory to add the 
 *  device to the accept list 
 * 
 *  @param local_id  Local identity (mostly just BT_ID_DEFAULT). 
 *   
 *  @return return the total devices that were bonded and added to the accept list
*/

int setup_accept_list(uint8_t local_id)
{
	int err = bt_le_filter_accept_list_clear();
	if (err) {
		printk("Cannot clear Filter Accept List (err: %d)\n", err);
		return err;
	}
	int bond_cnt = 0;
	bt_foreach_bond(local_id, setup_accept_list_cb, &bond_cnt);
	return bond_cnt;
}

/** @brief set up an accept list for bluetooth advertising use or not using an accept list. 
 * 
 * 	The function is a work function that is launched to conduct the advertising based on the bonded connections present
 * 	If no bonded connection are before then advertising happens without a filter accept list.
 *  If one or more bonds are found then a accept list is used to only accept the previously paird devices. 
 * 
 *  @param work : defined using the k_work structure so the function can be submitted for multi threading work 
 *   
*/

void advertise_with_acceptlist(struct k_work *work)
{
	int err=0;
	int allowed_cnt= setup_accept_list(BT_ID_DEFAULT);
	LOG_INF("NUmber of Allowed Connections:%d\n", allowed_cnt);
	if (allowed_cnt<0){
		printk("Acceptlist setup failed (err:%d)\n", allowed_cnt);
	} else {
		if (allowed_cnt==0){
			printk("Advertising with no Filter Accept list\n"); 
			err = bt_le_adv_start(BT_LE_ADV_CONN_NO_ACCEPT_LIST, ad, ARRAY_SIZE(ad),
					sd, ARRAY_SIZE(sd));
		}
		else {
			printk("Acceptlist setup number  = %d \n",allowed_cnt);
			err = bt_le_adv_start(BT_LE_ADV_CONN_ACCEPT_LIST, ad, ARRAY_SIZE(ad),
				sd, ARRAY_SIZE(sd));	
		}
		if (err) {
		 	printk("Advertising failed to start (err %d)\n", err);
			return;
		}
		printk("Advertising successfully started\n");
	}
}

K_WORK_DEFINE(advertise_acceptlist_work, advertise_with_acceptlist);

/** @brief set up an accept list for bluetooth advertising wihtout an accept list. 
 * 
 * 	The function will stop the current advertising and advertise without an accept list to accept new devices. 
 * 	NOTE: The system needs to be not connected to any device for the new advertising to occur. 
 * 
 *  TODO: for the central I should make a function that can accept multiple connections. 
 *  TODO: for the central I need to be able to auto connect. Need to work with this code and the central code in conjunction.  
 * 
 *  @param work: defined using the k_work structure so the function can be submitted for multi threading work 
 *   
*/

void advertise_without_acceptlist(struct k_work *work)
{
	int err_code = bt_le_adv_stop();
	if (err_code) {
		LOG_ERR("Cannot stop advertising err= %d \n", err_code);
		return;
	}
	// err_code = bt_le_filter_accept_list_clear();
	// if (err_code) {
	// 	LOG_ERR("Cannot clear accept list (err: %d)\n", err_code);
	// } else	{
	// 	LOG_INF("Filter Accept List cleared succesfully");
	// }				
	err_code = bt_le_adv_start(BT_LE_ADV_CONN_NO_ACCEPT_LIST, ad, ARRAY_SIZE(ad),	sd, ARRAY_SIZE(sd));
	if (err_code) {
		LOG_ERR("Cannot start open advertising (err: %d)\n", err_code);
	} else	{
		LOG_INF("Advertising in pairing mode started");
	}
}

K_WORK_DEFINE(advertise_work, advertise_without_acceptlist);

/** @brief unpairs all bonded device from the system 
 * 
 * 
 *  @param work: defined using the k_work structure so the function can be submitted for multi threading work 
 *   
*/

void unpair(struct k_work *work){
	int err= bt_unpair(BT_ID_DEFAULT,BT_ADDR_LE_ANY);
	if (err) {
		LOG_INF("Cannot delete bond (err: %d)\n", err);
	} else	{
		LOG_INF("Bond deleted succesfully \n");
	}
}

K_WORK_DEFINE(unpair_work, unpair);
	
