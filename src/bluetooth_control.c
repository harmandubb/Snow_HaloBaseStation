#include "bluetooth_control.h"

LOG_MODULE_REGISTER(button_control, LOG_LEVEL_INF);

struct bt_conn *default_conn; //would need to make this into an array if more than one connection is needed to be made 

//flags 
bool ledHandleReady = false;
uint16_t led_handle = 0; 
struct bt_conn *wrist_conn = NULL;
              

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
	

/** @brief Transmit LED on or off information 
 * 
 * 	bluetooth should be set up prior to ensure that there is a perpheral that can complete the request
 *  
 *  @param led_status bool: if the led should be on 
 * //TODO: figure out how to be able to send the led info to a peripheral. 
 *  
*/

void transmit_led_info(bool led_status){};

/** @brief Scan event handler function to handle with filter passed devices
 * 
 *	The following are the situations that can be set to check in the @ref bt_scan_filter match struct: 
	1. name //will the filter work like a contain function or a hard name? 
	2. short_name x
	3. addr x
	4. uuid //using the lbs service uuid
	5. appearance x
	6. manufacturer_data x
 *  
 *  @param device_info ptr to structure that holds device data to make a connection
 *  @param bt_scan_filter_match ptr to a struct that holds the information of filter matches for a device. Would change based on the filter opetions used
 * 	@param connectable  inform the central that the device is connectable. 
 *  
*/
void scan_filter_match(struct bt_scan_device_info *device_info, struct bt_scan_filter_match *filter_match, bool connectable)
{
    // Handle filter match event
	//assume anything with a uuid and a name that are filtered will work.
	int err; 
	
	if (filter_match->short_name.match){
		LOG_INF("NAME: ");
		for (int i = 0; i < filter_match->short_name.len; i++){
			LOG_INF("%c", filter_match->short_name.name[i]);
		}
		LOG_INF("\n");
	}

	if(filter_match->uuid.match){
		LOG_INF("UUID: ");
		for (int i = 0; i < filter_match->uuid.count; i++){
			LOG_INF("%d", filter_match->uuid.uuid[i]->type); // Logging as hexadecimal
			if (filter_match->uuid.uuid[i]->type == BT_UUID_TYPE_128) {
				LOG_INF("128 bit uuid found");
				struct bt_uuid_128 *u128 = (struct bt_uuid_128 *)filter_match->uuid.uuid;
				LOG_INF("%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
						// u128->val[0], u128->val[1], u128->val[2], u128->val[3], 
						// u128->val[4], u128->val[5], 
						// u128->val[6], u128->val[7], 
						// u128->val[8], u128->val[9], 
						// u128->val[10], u128->val[11], u128->val[12], u128->val[13], u128->val[14], u128->val[15]
						
						u128->val[15], u128->val[14], u128->val[13], u128->val[12], 
						u128->val[11], u128->val[10], 
						u128->val[9], u128->val[8], 
						u128->val[7], u128->val[6], 
						u128->val[5], u128->val[4], u128->val[3], u128->val[2], u128->val[1], u128->val[0]
						);
				LOG_INF("END OF UUID 128 bit");
			}
		}
	}

	if(filter_match->name.match){
		LOG_INF("NAME: ");
		for (int i = 0; i < filter_match->name.len; i++){
			LOG_INF("%c", filter_match->name.name[i]);
		}

		LOG_INF("\n");
	}

	

	//two options: perform a manual connect operation or allow the auto connect to work? 
	if (connectable) {
		struct bt_conn *conn; 
		err = bt_conn_le_create(device_info->recv_info->addr,
								BT_CONN_LE_CREATE_CONN, 
								device_info->conn_param, 
								&conn);

		if (!err){
			if (!err) {
				default_conn = bt_conn_ref(conn);
				bt_conn_unref(conn);
			}
		}
	}



	
};

/** @brief Scan event handler function to handle with non filter passed devices
 * 		   The device information is simpley outputed for debugging purposes. 
 *  
 *  @param device_info ptr to structure that holds device data to make a connection
 * 	@param connectable  inform the central that the device is connectable. 
 *  
*/

void scan_filter_no_match(struct bt_scan_device_info *device_info, bool connectable)
{
    // Handle filter no match event
	// LOG_ERR("DEVICE WITH ALL FILTERS NOT FOUND\n");
};

/** @brief Event handler runnign when a connection is made. Output the status of the connection. 
 * 			- what device is connected to
 * 			- status of the connection 
 * 		    
 *  
 *  @param device_info ptr to structure that holds device data to make a connection
 * 	@param conn ptr to connection info
 *  
*/

void scan_connecting(struct bt_scan_device_info *device_info, struct bt_conn *conn)
{
    LOG_INF("Connected\n");
};

/** @brief Event handler runnign when a connection has failed. 
 * 			Output:
 * 			- what device was attempted to connect to
 * 			- Error/reason for the connection failing
 * 		    
 *  @param device_info ptr to structure that holds device data to make a connection
 *  
*/

void scan_connecting_error(struct bt_scan_device_info *device_info)
{
    LOG_ERR("Failed to Connect\n");
};

/** @brief Macro for establishing the scan callbacks for when scanning is started
 * 		    
 *  @param _name scan_cb name of the bt_can_cb structure that is made 
 *  @param match_fun scan_filter_match function handler for when filters match 
 *  @param no_match_fun function handler for when filters do not match a device
 *  @param err_fun handler for handling error if connection failed (connect_if_match flag in the scan param must be set for connect to occur with this callback)
 *  @param connecting_fun handler for when a connection occurs (connect_if_match flag must be present)

*/

BT_SCAN_CB_INIT(scan_cb, scan_filter_match, scan_filter_no_match, scan_connecting_error, scan_connecting);

/** @brief starting the discovery of the services after a central connection is made 
 * 
 *  @param 	bt_conn * conn: struct holding the connectin parameters
 *  @param  err if error in connection has occured
 *			   
*/

void connected(struct bt_conn *conn, uint8_t err){
	if (err < 0){
		LOG_ERR("Conection erro has occured (err %d)", err);
	}

	LOG_INF("Bluetooth Connection Sucessfull");

	if(conn == NULL){
		LOG_ERR("The Conneciton ptr is not set properly");
	}

	static struct bt_uuid_128 uuid = BT_UUID_INIT_128(0);
	memcpy(&uuid, BT_UUID_LBS, sizeof(uuid));

	struct bt_gatt_discover_params discover_params = {
		.uuid = &uuid.uuid,
		.func = discover_cb, //discover attribute callback 
		.start_handle = 0x0001, 
		.end_handle = 0xffff,
		.type = BT_GATT_DISCOVER_CHARACTERISTIC,
	};

	wrist_conn = conn; 

	int result = bt_gatt_discover(conn, &discover_params);
	if (result < 0) {
		LOG_ERR("Error occured when discovering the bluetooth services (err: %d)", result);
	}
};

/** @brief starting the discovery of the services after a central connection is made 
 * 
 *  @param 	bt_conn * conn: struct holding the connectin parameters
 *  @param  reason error code for why disconnected occured   
*/

void disconnected(struct bt_conn *conn, uint8_t reason){
	LOG_ERR("Disconnection occured. (err: %d)", reason);
	wrist_conn = NULL;
	ledHandleReady = false; 
};

/** @brief callback funciton to address cycling through characteristics of the incoming connection
 * 
 * 	Want to find the led characteristic of the led service then get the required information 
 * 
 *  @param bt_conn *conn: ptr to the connection parameters needed for a bluetooth conneciton 
 *  @param bt_gatt_attr *attr: the gatt attribute that is found currently 
 *  @param bt_gatt_discover_params *params: Discovery parameters that are given
 *  
 */

uint8_t discover_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr, struct bt_gatt_discover_params *params){
	LOG_INF("IN THE DISCOVERY CALLBACK");
	// if(attr == NULL){
	// 	LOG_INF("Discovery complete");
	// 	return BT_GATT_ITER_STOP;
	// }

	// //set the struct for a characteristic 
	// struct bt_gatt_chrc *chrc = (struct bt_gatt_chrc *)attr->user_data;

	// if(bt_uuid_cmp(chrc->uuid,BT_UUID_LBS_LED) == 0) {
	// 	led_handle = chrc->value_handle;
	// 	LOG_INF("LED characteristic handle: %u", led_handle); 
	// 	ledHandleReady = true; 
	// 	return BT_GATT_ITER_STOP;  
	// } 

	// return BT_GATT_ITER_CONTINUE; 
	return BT_GATT_ITER_STOP; 
};

/** @brief send the updated led signal to the wrist module attached 
 * 	
 * 	Will need to write to teh led characteristic to update the led wrist module thorugh bluetooth control
 *  User must check if the led_handle and the bluetooth connection parameters are present. 
 * 	
 *  @param led_on: bool to tell if the led wrist strap is to be on or not 
 * 
 *  @return erro if present else 0. 
 */

int updateWristLED(bool led_on){
	uint8_t transmit_val[1] = {led_on};
	
	int err = bt_gatt_write_without_response(wrist_conn, led_handle,transmit_val,sizeof(transmit_val),false);
	if (err < 0){
		LOG_ERR("Error updating wrist LED (err: %d)", err);
		return err; 
	} 
	return 0; 
};