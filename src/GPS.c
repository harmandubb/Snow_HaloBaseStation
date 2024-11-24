#include "GPS.h"

LOG_MODULE_REGISTER(gps, LOG_LEVEL_DBG);

struct gps_data gps_data = {0};

void gnss_data_cb(const struct device *dev, const struct gnss_data *data)
{
	if (data->info.fix_status != GNSS_FIX_STATUS_NO_FIX) { 
        LOG_INF("GNSS WORKING");
		double latitude = data->nav_data.latitude /1e9;
        double longitude = data->nav_data.longitude/ 1e9;
        double speed = data->nav_data.speed; // Speed in meters per second
        struct gnss_time time = data->utc; // Convert timestamp to time structure

        gps_data.time.hours = time.hour;
        gps_data.time.minutes = time.minute;
        gps_data.time.milliseconds = time.millisecond;
        gps_data.latitude = latitude;
        gps_data.longitude = longitude;
        gps_data.speed = speed;
        

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
// GNSS_DATA_CALLBACK_DEFINE(GPS_DEVICE, gnss_data_cb);