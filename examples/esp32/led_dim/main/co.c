/**
 ******************************************************************************
 * @file    	co.c
 *
 * @author 		Mart van Vliet
 * @date 		09 June 2019
 * @brief
 ******************************************************************************
 **
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "co.h"

homekit_characteristic_t airQuality = HOMEKIT_CHARACTERISTIC_(AIR_QUALITY, 0);
homekit_characteristic_t co2Sensor = HOMEKIT_CHARACTERISTIC_(CARBON_DIOXIDE_LEVEL, 0);

void air_quality_identify(homekit_value_t _value) {
    printf("Air Quality identify\n");
}


void air_quality_task(void *_args) {

    int 	airQualityValue, 
			CO2Value;

    while (1) {
        airQualityValue = 2;

        airQuality.value.int_value = airQualityValue;
            // co2Sensor.value.float_value = humidity_value;

        homekit_characteristic_notify(&airQuality, HOMEKIT_UINT8(airQualityValue));
            // homekit_characteristic_notify(&co2Sensor, HOMEKIT_FLOAT(humidity_value));

        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

void air_quality_init() {
    xTaskCreate(air_quality_task, "Air Quality Sensor", 1024, NULL, 2, NULL);
}

homekit_value_t air_get(void){
    return HOMEKIT_INT(1);
}

homekit_value_t co2_get(void){
    return HOMEKIT_INT(400);
}