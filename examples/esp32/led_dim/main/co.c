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


void air_quality_task (void *_args) {

    int 	airQualityValue;
	float	CO2Value = -1;

    while (1) {
		CO2Value = co2_sensor_get();
        airQualityValue = air_quality_get((int)CO2Value);

        airQuality.value.int_value = airQualityValue;
        co2Sensor.value.float_value = CO2Value;

        homekit_characteristic_notify(&airQuality, HOMEKIT_UINT8(airQualityValue));
        homekit_characteristic_notify(&co2Sensor, HOMEKIT_FLOAT(CO2Value));

        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

void air_quality_init () {
    xTaskCreate(air_quality_task, "Air Quality Sensor", 1024, NULL, 2, NULL);
}

int air_quality_get (int CO2Value){
	if (CO2Value <= 0)
		return 0; 
	else if (CO2Value <= 600)
		return 1; 
	else if (CO2Value <= 800)
		return 2; 
	else if (CO2Value <= 1000)
		return 3; 
	else if (CO2Value <= 1500)
		return 4; 
	else
		return 5; 
}

float co2_sensor_get (void){
	uint8_t command[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
	uint8_t response[9];



	/* Check if response is valid */
	if (response[0] != 0xFF) 
		return -1;
	
	if (response[1] != 0x86) 
		return -1;
	

	int ppm = (256 * response[2]) + response[3];
	int temp = response[4]-40;
	byte status = response[5];
	int minimum = (256 * response[6]) + response[7];
    return 700;
}