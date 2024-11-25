#ifndef RIGHT_BOOT_OPERATION_H
#define RIGHT_BOOT_OPERATION_H

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <bluetooth/services/nus.h>

#include "adc_control.h"
#include "UART_bt_control.h"
#include "IMU.h"
#include "GPS.h"

#define PHONE_UART_BUFFER_SIZE (2*ADC_BUFFER_SIZE+IMU_BYTES+GPS_BYTES)

/**
 * @file right_boot_operation.h
 * @brief Header file for right_boot_operation function.
 *
 * Provides the function prototype and necessary includes for controlling
 * the right boot operation logic, including ADC, UART, and Bluetooth.
 */

/**
 * @brief Handles the right boot operation logic, including ADC reads, UART processing, and Bluetooth transmission.
 *
 * @param requestFinished Pointer to a boolean indicating if the request is finished.
 * @param UARTTransmit Pointer to a boolean indicating if UART transmission is ongoing.
 * @param UARTSendEnable Pointer to a boolean indicating if UART send is enabled.
 * @param adcFinished Pointer to a boolean indicating if the ADC operation is finished.
 * @param adc_dev Pointer to the ADC device structure.
 * @param sequence Pointer to the ADC sequence structure for configuration.
 * @param adc_buf Buffer to store ADC data.
 * @param uart_rx_data Buffer to store UART received data.
 * @param uart_data_mutex Pointer to the mutex for synchronizing UART data access.
 * @param UART_Comp_Array Array for storing processed UART comparison data.
 */
void right_boot_operation(bool *requestFinished, bool *UARTTransmit, bool *UARTSendEnable, 
                          bool *adcFinished, const struct device *adc_dev, 
                          struct adc_sequence *sequence, uint8_t adc_buf[], 
                          uint8_t uart_rx_data[], struct k_mutex *uart_data_mutex,
                          uint8_t uart_phone_buf[], struct gps_data *gps_data);

void convert_IMI_data_to_bytes(struct sensor_value *sensor, uint8_t output[8]);
void setUartIMUData(const struct sensor_value accel[3], const struct sensor_value gyro[3], 
                    uint8_t uart_phone_buf[], int start_index);
void setUartGPSData(struct gps_data *data, uint8_t *uart_phone_buf, int start_index);

#endif /* RIGHT_BOOT_OPERATION_H */
