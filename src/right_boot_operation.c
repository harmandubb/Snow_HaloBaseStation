#include "right_boot_operation.h"

LOG_MODULE_REGISTER(right_boot_operation, LOG_LEVEL_INF);

void right_boot_operation(bool *requestFinished, bool *UARTTransmit, bool *UARTSendEnable, 
                          bool *adcFinished, const struct device *adc_dev, 
                          struct adc_sequence *sequence, uint8_t adc_buf[], 
                          uint8_t uart_rx_data[], struct k_mutex *uart_data_mutex, 
                          uint16_t UART_Comp_Array[]) {
    int err = 0;

    if (*requestFinished) {
        *requestFinished = false;
        *adcFinished = false;
        *UARTTransmit = false;

        err = adc_read(adc_dev, &sequence);
        if (err < 0) {
            LOG_ERR("Could not read ADC data (%d)", err);
        }
    }

    if (*adcFinished) {
        printk("UART --> 1: %d 2: %d 3: %d 4: %d", adc_buf[0], adc_buf[1], adc_buf[2], adc_buf[3]);
        uint8_t uart_phone_buf[ADC_BUFFER_SIZE*2] = {0};
        for (int i = 0; i < ADC_BUFFER_SIZE; i++) {
            

            if (k_mutex_lock(&uart_data_mutex, K_FOREVER) == 0) {
                uint8_t rec_data = uart_rx_data[i+ADC_BUFFER_SIZE];
                k_mutex_unlock(&uart_data_mutex);
        }

        *adcFinished = false;
        *UARTTransmit = true;
    }

    if (*UARTTransmit) {
        if (*UARTSendEnable) {
            uint8_t msb_val = 0;
            uint8_t lsb_val = 0;
            

            for (int i = 0; i < ADC_BUFFER_SIZE / 2; i++) {
                UART_split_resolution(UART_Comp_Array[i], &msb_val, &lsb_val);
                uart_phone_buf[i * 2] = msb_val;
                uart_phone_buf[i * 2 + 1] = lsb_val;
            }

            err = bt_nus_send(NULL, uart_phone_buf, ADC_BUFFER_SIZE);
            if (err < 0) {
                LOG_ERR("Failed to transmit over Bluetooth (%d)", err);
            }
        }

        *requestFinished = true;
    }
}

int 


