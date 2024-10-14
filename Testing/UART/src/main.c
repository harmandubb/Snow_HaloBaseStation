#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gnss.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>



LOG_MODULE_REGISTER(gps_app, LOG_LEVEL_DBG);

#define GPS_NODE DT_NODELABEL(gps0)
#define GPS_DEVICE DEVICE_DT_GET(GPS_NODE)

#if DT_NODE_EXISTS(GPS_NODE)
#define GPS_DEVICE_READY 1
#else
#define GPS_DEVICE_READY 0
#endif

static void gnss_data_cb(const struct device *dev, const struct gnss_data *data)
{
	if (data->info.fix_status != GNSS_FIX_STATUS_NO_FIX) { 
		LOG_INF("Got a fix!");
	} else {
        LOG_INF("NO FIX");
    }
}
GNSS_DATA_CALLBACK_DEFINE(GPS_DEVICE, gnss_data_cb);

int main(void)
{
    // int err = 0;
    // printk("Checking GPS node...\n");
    
    // #if GPS_DEVICE_READY
    // printk("GPS node exists\n");
    // const struct device *gnss_dev = DEVICE_DT_GET(GPS_NODE);

    // if (!device_is_ready(gnss_dev)) {
    //     printk("GNSS device not ready\n");
    //     return -ENODEV;
    // }

    // printk("GNSS device is ready\n");

    // #else
    // printk("GPS node does not exist in the device tree\n");
    // #endif

    

    while (1) {
        k_msleep(1000);
        LOG_INF("WHILE");
    }
    LOG_ERR("EXIT");
    return 0;
}
	