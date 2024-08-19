#include "bluetooth_control.h"
#include "led_control.h"

LOG_MODULE_REGISTER(bluetooth_control, LOG_LEVEL_INF);

static const struct bt_data 
ad[] = {
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL|BT_LE_AD_NO_BREDR)), 
        BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_BOARD_HALO_L, sizeof(DEVICE_BOARD_HALO_L)),
		// BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_NUS_VAL),
		
};

static const struct bt_data sd[] = {
        BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_NUS_VAL),
};

struct bt_conn *default_conn; //would need to make this into an array if more than one connection is needed to be made 

//flags 
bool ledHandleReady = false;
uint16_t led_handle = 0; 
struct bt_conn *wrist_conn = NULL;
uint8_t read_data[100]; 
bool connectedFlag = false; 
extern struct bt_conn *Lboot_conn; 
extern bool isRightBoot; 
              

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
		LOG_ERR("Conection error has occured (err %d)", err);
	}

	LOG_INF("Bluetooth Connection Sucessfull");

	*led_operation_ptr = CONNECTED;
	connectedFlag = true; 


	if(conn == NULL){
		LOG_ERR("The Conneciton ptr is not set properly");
	}

	int result = 0; 

	LOG_INF("isRightBoot: %d", isRightBoot);

	if(isRightBoot){
		LOG_INF("Discovering UART Service");
		result = UART_gatt_discover(conn); //need to compare the connection parameters 
		if (result < 0){
			LOG_ERR("ERROR when UArt discovery");
		}

		static struct bt_gatt_discover_params discover_params = {
			.uuid = NULL,
			.func = discover_cb, //discover attribute callback  //shuldn't beed the issue, but not being called at all? 
			.start_handle = BT_ATT_FIRST_ATTRIBUTE_HANDLE, 
			.end_handle = BT_ATT_LAST_ATTRIBUTE_HANDLE,
			.type = BT_GATT_DISCOVER_PRIMARY,
		};

		wrist_conn = conn; 

		result = bt_gatt_discover(conn, &discover_params);
		if (result < 0) {
			LOG_ERR("Error occured when discovering the bluetooth services (err: %d)", result);
		}
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
	
	*led_operation_ptr = DISCONNECTED;
};

/** @brief annoyce how the bluetooth security has changed
 * 
 * 	@param bt_conn: conn is the connection parameters needed for the bluetooth connection
 *  @param bt_security_t: level is the security level that is set
 *  @param bt_security_err: err if present
 */
 
void on_security_changed(struct bt_conn *conn, bt_security_t level, enum bt_security_err err)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	if (!err) {
		LOG_INF("Security changed: %s level %u\n", addr, level);
	} else {
		LOG_INF("Security failed: %s level %u err %d\n", addr, level,
			err);
	}
}

/** @brief callback funciton to address cycling through characteristics of the incoming connection
 * 
 * 	Want to find the led characteristic of the led service then get the required information 
 * 
 *  @param bt_conn *conn: ptr to the connection parameters needed for a bluetooth conneciton 
 *  @param bt_gatt_attr *attr: the gatt attribute that is found currently 
 *  @param bt_gatt_discover_params *params: Discovery parameters that are given
 *  
 */

uint8_t discover_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr, struct bt_gatt_discover_params *params) {	
	static struct bt_gatt_discover_params discover_params;
	k_sleep(K_SECONDS(1));
	if (attr == NULL) {
        LOG_INF("LED Discovery complete");
        return BT_GATT_ITER_STOP;
    }


    if (params->type == BT_GATT_DISCOVER_PRIMARY) {
        struct bt_gatt_service_val *service_val = (struct bt_gatt_service_val *)attr->user_data;
        print_uuid(service_val->uuid);

        if (bt_uuid_cmp(service_val->uuid, BT_UUID_LBS) == 0) {
			
            LOG_INF("Found LBS service");
            // Here you can start discovering characteristics of the LBS service
			discover_params.uuid = NULL;
			discover_params.start_handle = attr->handle + 1; 
			discover_params.end_handle = service_val->end_handle;
			discover_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;
			discover_params.func = discover_cb;

			LOG_INF("BEFORE the LBS discover function");
			k_sleep(K_SECONDS(1));
			int err = bt_gatt_discover(conn, &discover_params);
			LOG_INF("After the LBS discover function");
			k_sleep(K_SECONDS(1));

			if (err < 0){
				LOG_ERR("Characteristic discovery failed (err: %d)", err);
				return BT_GATT_ITER_STOP;
			}
            return BT_GATT_ITER_STOP;
        }
    } else if (params->type == BT_GATT_DISCOVER_CHARACTERISTIC){
		struct bt_gatt_chrc *chrc = (struct bt_gatt_chrc *)attr->user_data;
		LOG_INF("Found characteristic with UUID: ");
        print_uuid(chrc->uuid);

		if (bt_uuid_cmp(chrc->uuid, BT_UUID_LBS_LED) == 0) {
            LOG_INF("Found LED characteristic");
            led_handle = chrc->value_handle;
            LOG_INF("LED characteristic handle: %u", led_handle);
            ledHandleReady = true;
            return BT_GATT_ITER_STOP;
        }
	}

    return BT_GATT_ITER_CONTINUE;
}

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
	LOG_INF("Transmitted led bit to the wrist moduleL %d", led_on);
	if (err < 0){
		LOG_ERR("Error updating wrist LED (err: %d)", err);
		return err; 
	} 
	return 0; 
};

int readWristLED(){
	static struct bt_gatt_read_params read_params; 
	
	read_params.func = gatt_read_func;
	read_params.handle_count = 1;
	read_params.single.handle = led_handle;
	read_params.single.offset = 0;

	LOG_INF("About to read the LED attribute");
	int err = bt_gatt_read(wrist_conn, &read_params);
	LOG_INF("AFTER to read the LED attribute");
	if (err < 0){
		LOG_ERR("Error reading the attribute (err: %d)",err);
		return err; 
	}

	return 0;
};

uint8_t gatt_read_func(struct bt_conn *conn, uint8_t err, struct bt_gatt_read_params *params, const void *data, uint16_t length)
{
    if (err< 0) {
        LOG_ERR("Read failed (err %d)\n", err);
        return BT_GATT_ITER_STOP ;
    }

	if(data == NULL){
		LOG_INF("Read is complete");

		return BT_GATT_ITER_STOP;
	} else {
		LOG_INF("Size of data: %d", length);
        memcpy(read_data, data, length);
        LOG_INF("Read data: %s\n", read_data);
        return BT_GATT_ITER_STOP;
    }

	return BT_GATT_ITER_CONTINUE;
};

/** @brief prints uuid in a clean form as shown in nrf connect app
 * 		
 * 	The funciton will determine what size the uuid is and print it as needed
 * 	
 *  @param uuid: ptr to a bt_uuid structure
 * 
 */

void print_uuid(const struct bt_uuid *uuid) {
    char uuid_str[37]; // 36 characters for UUID + null terminator
    
    switch (uuid->type) {
        case BT_UUID_TYPE_16:
        {
            struct bt_uuid_16 *u16 = (struct bt_uuid_16 *)uuid;
            LOG_INF("16-bit UUID: 0x%04x", u16->val);
            break;
        }
        case BT_UUID_TYPE_32:
        {
            struct bt_uuid_32 *u32 = (struct bt_uuid_32 *)uuid;
            LOG_INF("32-bit UUID: 0x%08x", u32->val);
            break;
        }
        case BT_UUID_TYPE_128:
        {
            struct bt_uuid_128 *u128 = (struct bt_uuid_128 *)uuid;
            bt_uuid_to_str(uuid, uuid_str, sizeof(uuid_str));
            LOG_INF("128-bit UUID: %s", uuid_str);
            LOG_INF("Raw 128-bit UUID: %02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                    u128->val[15], u128->val[14], u128->val[13], u128->val[12],
                    u128->val[11], u128->val[10],
                    u128->val[9], u128->val[8],
                    u128->val[7], u128->val[6],
                    u128->val[5], u128->val[4], u128->val[3], u128->val[2], u128->val[1], u128->val[0]);
            break;
        }
        default:
            LOG_INF("Unsupported UUID type");
            break;
    }
}

/** @brief create the appropriate scan filter based on the bonded devices. 
 * 
 * 	
 */

static int bond_filter_scan(bt_addr_le_t* bond_addr){
	int err; 

	LOG_INF("BOND FILTER SCAN STARTED");

	err = bt_scan_filter_add(BT_SCAN_FILTER_TYPE_ADDR,bond_addr);
	if (err < 0){
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
		return 0;
	}

};


/** @brief determine if bonded device is present and handle the connection as needed 
 *  If present then set the appripirate filter to scan 
 *  If not present then just start the scanning
 * 
 * 	@return the total number of bonds found in the system
 */

int scan_bond_devices(){
	static struct bond_count_data data = {
		.count = 0,
	};

	bt_foreach_bond(BT_ID_DEFAULT,bond_initial_cb,&data);

	// TODO: determine a mechanisms to allow two bonds to occur back to back 
	return data.count; 
};

/** @brief bond call back for when scanning is done on start up 
 * 	determine what identified for the bonded device that is stored and set a filter for a scan. 
 * 
 * 	@param bt_bond_info *info: pointer to the bond informaiton we get for each bonded device
 *  @param *user_data a predecided data structure for beused in the callback and outside of the bt_foreach_bond call
 * 	
 */

void bond_initial_cb(const struct bt_bond_info *info, void *user_data){
	struct bond_count_data *data = (struct bond_count_data *)user_data;

	data->count++; 

	char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(&(info->addr), addr, sizeof(addr));
	LOG_INF("Bonded Address found: %s", addr);

	int err = bond_filter_scan(&(info->addr));
	if (err < 0){
		LOG_ERR("Error set up and starting bond scan (err: %d)", err);
	}

};


/** @brief disconnect from all bluetooth devices
 * 
 * 	@param: work parameter for defining work
 */
void bt_disconnect_all(struct k_work *work){
	bt_conn_foreach(BT_CONN_TYPE_LE,force_disconnect_cb, NULL);
};

K_WORK_DEFINE(bt_disconnect_all_work, bt_disconnect_all);

