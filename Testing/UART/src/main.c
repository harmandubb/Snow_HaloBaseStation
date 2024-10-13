#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gnss.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/uart.h>

LOG_MODULE_REGISTER(gps_app, LOG_LEVEL_INF);

#define GPS_NODE DT_NODELABEL(gps0)

#if DT_NODE_EXISTS(GPS_NODE)
#define GPS_DEVICE_READY 1
#else
#define GPS_DEVICE_READY 0
#endif

int main(void)
{
    printk("Checking GPS node...\n");
    
    #if GPS_DEVICE_READY
    printk("GPS node exists\n");
    const struct device *gnss_dev = DEVICE_DT_GET(GPS_NODE);

    if (!device_is_ready(gnss_dev)) {
        printk("GNSS device not ready\n");
        return -ENODEV;
    }

    printk("GNSS device is ready\n");
    #else
    printk("GPS node does not exist in the device tree\n");
    #endif

    while (1) {
        k_msleep(1000);
        printk("System working in the loop\n");
    }

    return 0;
}

// #include <zephyr/kernel.h>
// #include <zephyr/device.h>
// #include <zephyr/drivers/gnss.h>
// #include <zephyr/devicetree.h>
// #include <zephyr/drivers/gpio.h>
// #include <zephyr/sys/printk.h>
// #include <zephyr/logging/log.h>
// #include <zephyr/drivers/uart.h>

// LOG_MODULE_REGISTER(gps_app, LOG_LEVEL_INF);

// #define GPS_NODE DT_NODELABEL(gps0)

// int main(void)
// {
// 	int err = 0;

// 	static const struct device *gnss_dev = DEVICE_DT_GET(GPS_NODE);
// 	// Check if the GNSS device is ready
//     if (!device_is_ready(gnss_dev)) {
//         LOG_ERR("GNSS device not ready");
//         return -ENODEV;
//     }
	
	
// 	while (1) {
// 		k_msleep(1000);
// 		printk("System working in the loop\n");
// 	}
// }
