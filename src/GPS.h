#ifndef GPS_H
#define GPS_H

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gnss.h>
#include <zephyr/drivers/gpio.h>

#define GPS_NODE DT_NODELABEL(gps0)
#define GPS_DEVICE DEVICE_DT_GET(GPS_NODE)
#define GPS_BYTES (8*3+1+1+2)

#if DT_NODE_EXISTS(GPS_NODE)
#define GPS_DEVICE_READY 1
#else
#define GPS_DEVICE_READY 0
#endif

// External variables 
extern struct gps_data gps_data;

//struct define
struct gps_time {
    uint8_t hours;    // Hours (0-23)
    uint8_t minutes;  // Minutes (0-59)
    uint16_t milliseconds;  // Seconds (0-5999)
};

struct gps_data {
    double latitude;
    double longitude;
    float speed;
    struct gps_time time; // Nested time struct
};


// Function declarations
void gnss_data_cb(const struct device *dev, const struct gnss_data *data);



#endif /* GPS_H */
