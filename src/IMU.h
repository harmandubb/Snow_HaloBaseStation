#ifndef IMU_H
#define IMU_H

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>


#define IMU_NODE DT_NODELABEL(lsm6ds3tr_c)
#define IMU_DEVICE DEVICE_DT_GET(IMU_NODE)
#define SAMPLE_FREQUENCY (2)
#define IMU_BYTES (6*4*2+2) //plus two for the spacing of data 

#if DT_NODE_EXISTS(IMU_NODE)
#define IMU_DEVICE_READY 1
#else
#define IMU_DEVICE_READY 0
#endif

// External variables 

//struct define

// Function declarations
#if IMU_DEVICE_READY
int IMUSetup();
int readIMUData(double accel[], double gyro[]);
#endif

#endif /* IMU_H */
