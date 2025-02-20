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
        double accel[3] = {0};
        double gyro[3] = {0};

        // read IMU
        if(IMU_DEVICE_READY){
            err = readIMUData(accel,gyro);
            setUartIMUData(accel, gyro, uart_phone_buf, ADC_BUFFER_SIZE*2);
        }

        // //set the gps data 
        setUartGPSData(gps_data, uart_phone_buf, (ADC_BUFFER_SIZE*2+IMU_BYTES));

        *adcFinished = false;
        *UARTTransmit = true;
    }

    if (*UARTTransmit) {
        if (*UARTSendEnable) {

            int total_uart_buf_size = ADC_BUFFER_SIZE*2+GPS_BYTES+IMU_BYTES;

            // Test print all of teh bytes as seen on the uart 

            for (int i = 0; i < total_uart_buf_size; i++) {
                LOG_INF("Index %d: 0x%02X", i, uart_phone_buf[i]);
            }

            k_sleep(K_SECONDS(1));

            err = bt_nus_send(NULL, uart_phone_buf, total_uart_buf_size);
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
void setUartIMUData(const double accel[3], const double gyro[3], 
                    uint8_t uart_phone_buf[], int start_index) {
    uint8_t output[8] = {0}; // Temporary buffer for converted data

    uint16_t IMU_spacer = 0x0001;  // 16-bit value to store
    memcpy(&uart_phone_buf, &IMU_spacer, sizeof(IMU_spacer));

    for (int i = 0; i < 3; i++) {
        // Convert accelerometer data to bytes and store in UART buffer
        convert_double_to_bytes(accel[i], output);
        for (int j = 0; j < 8; j++) {
            uart_phone_buf[start_index + 2 + (i * 8) + j] = output[j];
        }

        // Convert gyroscope data to bytes and store in UART buffer
        convert_double_to_bytes(gyro[i], output);
        for (int j = 0; j < 8; j++) {
            uart_phone_buf[start_index + 2 + (3 * 8) + (i * 8) + j] = output[j];
        }
    }
}



void convert_double_to_bytes(double sensor_val, uint8_t output[8]) {
    memcpy(output, &sensor_val, sizeof(sensor_val));
}

void setUartGPSData(struct gps_data *data, uint8_t *uart_phone_buf, int start_index){
    uint8_t *ptr = uart_phone_buf+start_index; // Pointer to the current position in the buffer

    uint16_t gps_spacer = 0x0002;  // 16-bit value to store
    memcpy(ptr, &gps_spacer, sizeof(gps_spacer));
    
    // Serialize latitude (double -> 8 bytes)
    memcpy(ptr, &data->latitude, sizeof(data->latitude));
    ptr += sizeof(data->latitude);
    
    // Serialize longitude (double -> 8 bytes)
    memcpy(ptr, &data->longitude, sizeof(data->longitude));
    ptr += sizeof(data->longitude);
    
    // Serialize speed (float -> 4 bytes)
    memcpy(ptr, &data->speed, sizeof(data->speed));
    ptr += sizeof(data->speed);
    
    // Serialize hours (1 byte)
    *ptr++ = data->time.hours;
    
    // Serialize minutes (1 byte)
    *ptr++ = data->time.minutes;
    
    // Serialize milliseconds (2 bytes)
    memcpy(ptr, &data->time.milliseconds, sizeof(data->time.milliseconds));
    ptr += sizeof(data->time.milliseconds);
    
}

                          