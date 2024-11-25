#ifndef LEFT_BOOT_OPERATION_H
#define LEFT_BOOT_OPERATION_H

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <bluetooth/services/nus.h>

#include "adc_control.h"
#include <bluetooth/services/nus.h>


//external variables

//function defines: 
int left_boot_operation(bool *requestFinished, bool *adcFinished, bool *UARTFinished, bool *UARTSendEnable, int adc_buf_size, struct device *adc_dev, struct adc_sequence *sequence, uint8_t adc_buf[]);



#endif /* LEFT_BOOT_OPERATION_H */