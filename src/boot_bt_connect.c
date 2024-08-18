#include "boot_bt_connect.h"


LOG_MODULE_REGISTER(boot_bt_control, LOG_LEVEL_INF);


static const struct bt_data 
ad[] = {
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL|BT_LE_AD_NO_BREDR)), 
        BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_BOARD_HALO_L, sizeof(DEVICE_BOARD_HALO_L)),
		// BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_NUS_VAL),
		
};

static const struct bt_data sd[] = {
        BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_NUS_VAL),
};


//flags   


//global variables 
struct k_work Lboot_scan_work; 
struct bt_conn *Lboot_conn; 


/** @brief Set the filters for accepting L_Boot and start the scanning
 *  
 *  @param k_work struct for threading
 *  
 */

void Lboot_scan(struct k_work *work){
    int err;
    LOG_INF("L Boot Scan Started");

    err = bt_scan_stop(); 
    if (err < 0){
        LOG_ERR("Unable to stop scanning (err: %d)", err);
    }

    bt_scan_filter_disable(); 
    bt_scan_filter_remove_all();

    err = bt_scan_filter_add(BT_SCAN_FILTER_TYPE_UUID, BT_UUID_NUS_SERVICE);
    if (err < 0){
        LOG_ERR("L Boot UUID scanning filters cannot be set (err %d)", err);
        return; 
    }

    err = bt_scan_filter_add(BT_SCAN_FILTER_TYPE_NAME, DEVICE_BOARD_HALO_L);
    if (err < 0){
        LOG_ERR("L Boot name scanning filters cannot be set (err %d)", err);
        return; 
    }

    err = bt_scan_filter_enable(BT_SCAN_UUID_FILTER, true);
    if (err < 0) {
			LOG_ERR("Filters cannot be turned on (err %d)", err);
			return;
	}

    LOG_INF("Scan module initialized");

    err = bt_scan_start(BT_SCAN_TYPE_SCAN_ACTIVE);
    if (err < 0){
        LOG_ERR("L Boot scanning failed to start (err %d)", err);
    }

}          

K_WORK_DEFINE(Lboot_scan_work, Lboot_scan);

/** @brief Scan event handler function to handler filters for scan
 
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
void boot_scan_filter_match(struct bt_scan_device_info *device_info, struct bt_scan_filter_match *filter_match, bool connectable)
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

			print_uuid(filter_match->uuid.uuid[i]);
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
				Lboot_conn = bt_conn_ref(conn);
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

void boot_scan_filter_no_match(struct bt_scan_device_info *device_info, bool connectable)
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

void boot_scan_connecting(struct bt_scan_device_info *device_info, struct bt_conn *conn)
{
    LOG_INF("Connected in the Scan Connecting callback\n");

	if(conn == NULL){
		LOG_ERR("The Conneciton ptr is not set properly");
	}
};

/** @brief Event handler runnign when a connection has failed. 
 * 			Output:
 * 			- what device was attempted to connect to
 * 			- Error/reason for the connection failing
 * 		    
 *  @param device_info ptr to structure that holds device data to make a connection
 *  
*/

void boot_scan_connecting_error(struct bt_scan_device_info *device_info)
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

BT_SCAN_CB_INIT(boot_scan_cb, boot_scan_filter_match, boot_scan_filter_no_match, boot_scan_connecting_error, boot_scan_connecting);


/** @brief callback funciton to address cycling through characteristics of the incoming connection
 * 
 * 	Want to find the led characteristic of the led service then get the required information 
 * 
 *  @param bt_conn *conn: ptr to the connection parameters needed for a bluetooth conneciton 
 *  @param bt_gatt_attr *attr: the gatt attribute that is found currently 
 *  @param bt_gatt_discover_params *params: Discovery parameters that are given
 *  
 */

// uint8_t discover_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr, struct bt_gatt_discover_params *params) {	
// 	// static struct bt_gatt_discover_params discover_params;
// 	// k_sleep(K_SECONDS(1));
// 	// if (attr == NULL) {
//     //     LOG_INF("Discovery complete");
//     //     return BT_GATT_ITER_STOP;
//     // }


//     // if (params->type == BT_GATT_DISCOVER_PRIMARY) {
//     //     struct bt_gatt_service_val *service_val = (struct bt_gatt_service_val *)attr->user_data;
//     //     print_uuid(service_val->uuid);

//     //     if (bt_uuid_cmp(service_val->uuid, BT_UUID_LBS) == 0) {
			
//     //         LOG_INF("Found LBS service");
//     //         // Here you can start discovering characteristics of the LBS service
// 	// 		discover_params.uuid = NULL;
// 	// 		discover_params.start_handle = attr->handle + 1; 
// 	// 		discover_params.end_handle = service_val->end_handle;
// 	// 		discover_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;
// 	// 		discover_params.func = discover_cb;

// 	// 		LOG_INF("BEFORE the LBS discover function");
// 	// 		k_sleep(K_SECONDS(1));
// 	// 		int err = bt_gatt_discover(conn, &discover_params);
// 	// 		LOG_INF("After the LBS discover function");
// 	// 		k_sleep(K_SECONDS(1));

// 	// 		if (err < 0){
// 	// 			LOG_ERR("Characteristic discovery failed (err: %d)", err);
// 	// 			return BT_GATT_ITER_STOP;
// 	// 		}
//     //         return BT_GATT_ITER_STOP;
//     //     }
//     // } else if (params->type == BT_GATT_DISCOVER_CHARACTERISTIC){
// 	// 	struct bt_gatt_chrc *chrc = (struct bt_gatt_chrc *)attr->user_data;
// 	// 	LOG_INF("Found characteristic with UUID: ");
//     //     print_uuid(chrc->uuid);

// 	// 	if (bt_uuid_cmp(chrc->uuid, BT_UUID_LBS_LED) == 0) {
//     //         LOG_INF("Found LED characteristic");
//     //         led_handle = chrc->value_handle;
//     //         LOG_INF("LED characteristic handle: %u", led_handle);
//     //         ledHandleReady = true;
//     //         return BT_GATT_ITER_STOP;
//     //     }
// 	// }

//     // return BT_GATT_ITER_CONTINUE;
// }



// uint8_t gatt_read_func(struct bt_conn *conn, uint8_t err, struct bt_gatt_read_params *params, const void *data, uint16_t length)
// {
//     // if (err< 0) {
//     //     LOG_ERR("Read failed (err %d)\n", err);
//     //     return BT_GATT_ITER_STOP ;
//     // }

// 	// if(data == NULL){
// 	// 	LOG_INF("Read is complete");

// 	// 	return BT_GATT_ITER_STOP;
// 	// } else {
// 	// 	LOG_INF("Size of data: %d", length);
//     //     memcpy(read_data, data, length);
//     //     LOG_INF("Read data: %s\n", read_data);
//     //     return BT_GATT_ITER_STOP;
//     // }

// 	// return BT_GATT_ITER_CONTINUE;
// };

/** @brief create the appropriate scan filter based on the bonded devices. 
 * 
 * 	
 */

static int bond_filter_scan(const bt_addr_le_t* bond_addr) {
    int err;

    LOG_INF("BOND FILTER SCAN STARTED");

    err = bt_scan_filter_add(BT_SCAN_FILTER_TYPE_ADDR, bond_addr);
    if (err < 0) {
        LOG_ERR("Error adding the addr filter for bonded devices: (err %d)", err);
        return err;
    }

    err = bt_scan_filter_enable(BT_SCAN_ADDR_FILTER, false);
    if (err < 0) {
        LOG_ERR("Filters cannot be turned on (err %d)", err);
        return err;
    }

    err = bt_scan_start(BT_SCAN_TYPE_SCAN_ACTIVE);
    if (err < 0){
        LOG_ERR("Scanning failed to start (err %d)", err);
        return err;
    }

    return 0;  // Ensure a value is returned in the success case
}


/** @brief work for advertising the L_Boot configurations
 * 
 * 	@param: work parameter for defining work
 * 
 */
void advertise_L_boot(struct k_work *work){
	int err_code = bt_le_adv_stop();
	if (err_code) {
		LOG_ERR("Cannot stop advertising err= %d \n", err_code);
		return;
	}

	err_code = bt_le_adv_start(BT_LE_ADV_CONN_NO_ACCEPT_LIST, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err_code) {
		LOG_ERR("Cannot start open advertising (err: %d)\n", err_code);
	} else	{
		LOG_INF("Advertising in pairing mode started");
	}
};

K_WORK_DEFINE(advertise_L_boot_work, advertise_L_boot);

