#include "right_boot_operation.h"

LOG_MODULE_REGISTER(right_boot_operation, LOG_LEVEL_INF);

void right_boot_operation(bool *requestFinished, bool *UARTTransmit, bool *UARTSendEnable, 
                          bool *adcFinished, const struct device *adc_dev, 
                          struct adc_sequence *sequence, uint8_t adc_buf[], 
                          uint8_t uart_rx_data[], struct k_mutex *uart_data_mutex,
                          uint8_t uart_phone_buf[]) {
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
                          