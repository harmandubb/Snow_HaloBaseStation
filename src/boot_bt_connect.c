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
static struct bt_nus_client nus_client;

//struct defines
static K_FIFO_DEFINE(fifo_uart_rx_data);


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

static void uart_discovery_complete(struct bt_gatt_dm *dm, void *context){
	struct bt_nus_client *nus = context; 
	LOG_INF("UART Service discovery completed");

	bt_gatt_dm_data_print(dm);
	bt_nus_handles_assign(dm, nus);
	bt_gatt_dm_data_release(dm);
};

static void uart_discovery_not_found(struct bt_conn *conn, void *context){
	LOG_INF("Service not found");
};

static void uart_error_found(struct bt_conn *conn, int err, void *context){
	LOG_WRN("Error while discovering GATT database: (%d)", err);
};

struct bt_gatt_dm_cb uart_discovery_cb = {
	.completed = uart_discovery_complete,
	.service_not_found = uart_discovery_not_found, 
	.error_found = uart_error_found,
};

/** @brief UART_gatt_discover: find the UART service 
 * 
 * 	@param bt_conn the structure of the bt_connection made 
 * 	
 * @return error if present
 */

int UART_gatt_discover(struct bt_conn *conn){
	int err = 0; 

	err = bt_gatt_dm_start(conn, 
						BT_UUID_NUS_SERVICE,
						&uart_discovery_cb,
						&nus_client);

	if (err < 0){
		LOG_ERR("Could not start the discovery procedure (err %d)", err);
		return err; 
	}

	return 0;
	
};

uint8_t ble_uart_data_received(struct bt_nus_client *nus, const uint8_t *data, uint16_t len){
	LOG_INF("Received Data from UART");
	ARG_UNUSED(nus);

	int err = 0; 

	for (uint16_t i = 0; i < len; i++){
		k_fifo_put(&fifo_uart_rx_data,data[i]); //see if a type should be cast to the fifo to do some porcessing
	}

	return BT_GATT_ITER_CONTINUE; 
};

/** @brief initialize the nuse client module for receiving information 
 * 
 *  
 *  @return error is present 
 */

int nus_client_init(){
	int err = 0; 
	static struct bt_nus_client_init_param init = {
		.cb = {
			.received = ble_uart_data_received,
		}
	};

	err = bt_nus_client_init(&nus_client, &init);
	if (err < 0){
		LOG_ERR("NUS Client Initilaizaiton failed (err %d)", err);
		return err; 
	}

	LOG_INF("NUS Client module initilized");
	return err; 
}

