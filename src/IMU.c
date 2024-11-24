#include "IMU.h"

LOG_MODULE_REGISTER(imu, LOG_LEVEL_INF);

int IMUSetup(){
    if (!device_is_ready(IMU_DEVICE)) {
                LOG_ERR("IMU device is not ready");
                return -1;
        } else {
                LOG_INF("IMU DEVICE MegIS READY");
        }

    return 0; 
};

int readIMUData(struct sensor_value accel[], struct sensor_value gyro[]){
    int err = 0; 

    static struct sensor_value accel_x, accel_y, accel_z;
	static struct sensor_value gyro_x, gyro_y, gyro_z;


    // Fetch accelerometer data
    err = sensor_sample_fetch_chan(IMU_DEVICE, SENSOR_CHAN_ACCEL_XYZ);
    if (err < 0) {
        LOG_ERR("Error fetching accelerometer data: %d", err);
        return err;  // Exit or handle the error appropriately
    }

    // Get accelerometer channels
    err = sensor_channel_get(IMU_DEVICE, SENSOR_CHAN_ACCEL_X, &accel_x);
    if (err < 0) {
        LOG_ERR("Error getting accelerometer X channel: %d", err);
    }

    err = sensor_channel_get(IMU_DEVICE, SENSOR_CHAN_ACCEL_Y, &accel_y);
    if (err < 0) {
        LOG_ERR("Error getting accelerometer Y channel: %d", err);
    }

    err = sensor_channel_get(IMU_DEVICE, SENSOR_CHAN_ACCEL_Z, &accel_z);
    if (err < 0) {
        LOG_ERR("Error getting accelerometer Z channel: %d", err);
    }

    // Fetch gyroscope data
    err = sensor_sample_fetch_chan(IMU_DEVICE, SENSOR_CHAN_GYRO_XYZ);
    if (err < 0) {
        LOG_ERR("Error fetching gyroscope data: %d", err);
        return err;  // Exit or handle the error appropriately
    }

    // Get gyroscope channels
    err = sensor_channel_get(IMU_DEVICE, SENSOR_CHAN_GYRO_X, &gyro_x);
    if (err < 0) {
        LOG_ERR("Error getting gyroscope X channel: %d", err);
    }

    err = sensor_channel_get(IMU_DEVICE, SENSOR_CHAN_GYRO_Y, &gyro_y);
    if (err < 0) {
        LOG_ERR("Error getting gyroscope Y channel: %d", err);
    }

    err = sensor_channel_get(IMU_DEVICE, SENSOR_CHAN_GYRO_Z, &gyro_z);
    if (err < 0) {
        LOG_ERR("Error getting gyroscope Z channel: %d", err);
    }

    accel[0] = accel_x;
    accel[1] = accel_y;
    accel[2] = accel_z;

    gyro[0] = gyro_x;
    gyro[1] = gyro_y;
    gyro[2] = gyro_z;

    return 0;
   
}