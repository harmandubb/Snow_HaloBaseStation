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
		double latitude = data->nav_data.latitude /1e9;
        double longitude = data->nav_data.longitude/ 1e9;
        double speed = data->nav_data.speed; // Speed in meters per second
        struct gnss_time time = data->utc; // Convert timestamp to time structure

        LOG_INF("Location: Latitude: %.6f, Longitude: %.6f, Time: %02d:%02d:%02d UTC, Speed: %.2f mm/s",
                latitude,
                longitude,
                time.hour,
                time.minute,
                time.millisecond,
                speed);
	} else {
        LOG_INF("NO FIX");
    }
}
GNSS_DATA_CALLBACK_DEFINE(GPS_DEVICE, gnss_data_cb);

int main(void)
{
    int err = 0;
    if (!device_is_ready(GPS_DEVICE)) {
        LOG_ERR("GNSS device is not ready");
        return -1;
    }

    while (1) {
        k_msleep(500);
        LOG_INF("WHILE");
    }

    LOG_ERR("EXIT");
    return 0;
}
	