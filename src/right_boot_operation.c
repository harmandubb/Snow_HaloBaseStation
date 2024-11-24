#include "right_boot_operation.h"

LOG_MODULE_REGISTER(right_boot_operation, LOG_LEVEL_INF);

void right_boot_operation(bool *requestFinished, bool *UARTTransmit, bool *UARTSendEnable, 
                          bool *adcFinished, const struct device *adc_dev, 
                          struct adc_sequence *sequence, uint8_t adc_buf[], 
                          uint8_t uart_rx_data[], struct k_mutex *uart_data_mutex,
                          uint8_t uart_phone_buf[], struct gps_data *gps_data) {
    int err = 0;

    if (*requestFinished) {
        *requestFinished = false;
        *adcFinished = false;
        *UARTTransmit = false;

        err = adc_read(adc_dev, sequence);
        if (err < 0) {
            LOG_ERR("Could not read ADC data (%d)", err);
        }
    }

    if (*adcFinished) {
        for (int i = 0; i < ADC_BUFFER_SIZE; i++) {
            //upload the local adc 
            uart_phone_buf[i] = adc_buf[i];
            //upload the left boot sensor data 
            if (k_mutex_lock(uart_data_mutex, K_FOREVER) == 0) {
                uart_phone_buf[i+ADC_BUFFER_SIZE] = uart_rx_data[i];
                k_mutex_unlock(uart_data_mutex);
            }
        }

        //set the IMU data 
        struct sensor_value accel[3] = {0};
        struct sensor_value gyro[3] = {0};

        // read IMU
        err = readIMUData(accel,gyro);
        setUartIMUData(accel, gyro, uart_phone_buf, ADC_BUFFER_SIZE*2);

        //set the gps data 





        *adcFinished = false;
        *UARTTransmit = true;
    }

    if (*UARTTransmit) {
        if (*UARTSendEnable) {

            err = bt_nus_send(NULL, uart_phone_buf, ADC_BUFFER_SIZE);
            if (err < 0) {
                LOG_ERR("Failed to transmit over Bluetooth (%d)", err);
            }
        }

        *requestFinished = true;
    }
}

/**
 * @brief Populates a UART buffer with accelerometer and gyroscope data.
 *
 * This function converts accelerometer (`accel`) and gyroscope (`gyro`) sensor data
 * into 8-byte chunks and populates a specified section of the `uart_phone_buf`.
 *
 * The function assumes the accelerometer data is stored in the first 3 indices
 * of `uart_phone_buf`, followed by gyroscope data in the next 3 indices.
 *
 * @param accel Array of 3 `struct sensor_value` containing accelerometer data.
 * @param gyro Array of 3 `struct sensor_value` containing gyroscope data.
 * @param uart_phone_buf Array of bytes to store the converted IMU data.
 * @param start_index Starting index in the `uart_phone_buf` to begin storing data.
 */
void setUartIMUData(const struct sensor_value accel[3], const struct sensor_value gyro[3], 
                    uint8_t uart_phone_buf[], int start_index) {
    uint8_t output[8] = {0}; // Temporary buffer for converted data

    for (int i = 0; i < 3; i++) {
        // Convert accelerometer data to bytes and store in UART buffer
        convert_IMI_data_to_bytes(&accel[i], output);
        for (int j = 0; j < 8; j++) {
            uart_phone_buf[start_index + (i * 8) + j] = output[j];
        }

        // Convert gyroscope data to bytes and store in UART buffer
        convert_IMI_data_to_bytes(&gyro[i], output);
        for (int j = 0; j < 8; j++) {
            uart_phone_buf[start_index + (3 * 8) + (i * 8) + j] = output[j];
        }
    }
}



void convert_IMI_data_to_bytes(struct sensor_value *sensor, uint8_t output[8]) {
    // Extract bytes from val1
    output[0] = (sensor->val1 >> 24) & 0xFF;  // Most significant byte (MSB)
    output[1] = (sensor->val1 >> 16) & 0xFF;
    output[2] = (sensor->val1 >> 8) & 0xFF;
    output[3] = sensor->val1 & 0xFF;          // Least significant byte (LSB)

    // Extract bytes from val2
    output[4] = (sensor->val2 >> 24) & 0xFF;  // Most significant byte (MSB)
    output[5] = (sensor->val2 >> 16) & 0xFF;
    output[6] = (sensor->val2 >> 8) & 0xFF;
    output[7] = sensor->val2 & 0xFF;          // Least significant byte (LSB)
}

void setUartGPSData(struct gps_data gps_data, uint8_t uart_phone_buf[], int start_index){
    
}
                          