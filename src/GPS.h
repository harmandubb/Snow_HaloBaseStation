#ifndef GPS_H
#define GPS_H

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gnss.h>
#include <zephyr/drivers/gpio.h>

#define GPS_NODE DT_NODELABEL(gps0)
#define GPS_DEVICE DEVICE_DT_GET(GPS_NODE)

#if DT_NODE_EXISTS(GPS_NODE)
#define GPS_DEVICE_READY 1
#else
#define GPS_DEVICE_READY 0
#endif

// External variables 

//struct define

// Function declarations
void gnss_data_cb(const struct device *dev, const struct gnss_data *data);



#endif /* GPS_H */
