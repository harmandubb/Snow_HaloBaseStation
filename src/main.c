#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>
#include <stdlib.h>

#include "led_control.h"
#include "adc_control.h"





LOG_MODULE_REGISTER(base_station, LOG_LEVEL_INF);

int main(void)
{
        //Setup

        //flags 
        bool sensorDataRequested = false;
        adcReady = false; 

        //variables
        int checkSensorNum = 0; 
        int pressureDiff = 0; 


        // dynamically allocated memory
        uint16_t* sensorPressureMap = (uint16_t*)malloc(NUM_SENSORS * sizeof(uint16_t));
        if (sensorPressureMap == NULL) {
                LOG_ERR("Initalization of sensorPressureMap failed\n");
        }

        uint16_t* boardLedMap = init_board_led(PIN_BOARD_LED);
        if (boardLedMap == NULL){
                LOG_ERR("Initilization of board led failed\n");
        }

        // //initalize the adc device tree variable 
        static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));
        if (!adc_is_ready_dt(&adc_channel)) {
                LOG_ERR("ADC controller devivce %s not ready", adc_channel.dev->name);
                return 0;
        }

        for(;;){
                //update the led of the baord 

                //go through the board logic
        }
        return 0;
}
