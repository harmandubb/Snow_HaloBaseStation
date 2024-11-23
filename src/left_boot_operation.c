#include "left_boot_operation.h"

LOG_MODULE_REGISTER(left_boot_operation, LOG_LEVEL_INF);


int left_boot_operation(bool *requestFinished, bool *adcFinished, bool *UARTFinished, bool *UARTSendEnable, int adc_buf_size, struct device *adc_dev, struct adc_sequence sequence, uint8_t adc_buf[]){ 
    int err = 0;

    if(requestFinished){
            *requestFinished = false;  
            *adcFinished = false; 
            *UARTFinished = false; 
            err = adc_read(adc_dev, &sequence);
            if (err < 0) {
                    LOG_ERR("Could not read (%d)", err);
                    return err; 
            }
    }

    if(adcFinished){
            if(*UARTSendEnable){
                    LOG_INF("UART --> 1: %d 2: %d 3: %d 4: %d", adc_buf[0],adc_buf[1],adc_buf[2],adc_buf[3]);
                    err = bt_nus_send(NULL, adc_buf, adc_buf_size);
                    if (err < 0){
                            LOG_ERR("Error UART Send: %d", err);
                    } 
            }
    }

    if(UARTFinished){
            *requestFinished = true; 
    }

    return 0;

};