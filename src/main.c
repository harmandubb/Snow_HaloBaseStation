#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <stdlib.h>

#include "led_control.h"

#define NUM_SENSORS (2)



LOG_MODULE_REGISTER(base_station, LOG_LEVEL_INF);

int main(void)
{
        //Setup

        //flags 
        bool sensorDataRequested = false;
        bool adcReady = false;

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

        for(;;){
                //update the led of the baord 

                //go through the board logic
        }
        return 0;
}
