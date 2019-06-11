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

uart_config_t uart_config = {
    .baud_rate = 9600,
    .data_bits = UART_DATA_8_BITS,
    .parity    = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
};

void air_quality_identify(homekit_value_t _value) {
    printf("Air Quality identify\n");
}


void air_quality_task (void *_args) {

    int 	airQualityValue;
	float	CO2Value = -1;

    while (1) {
		// CO2Value = co2_sensor_get();
		CO2Value = 600;

        airQualityValue = air_quality_get((int)CO2Value);

        airQuality.value.int_value = airQualityValue;
        co2Sensor.value.float_value = CO2Value;

        homekit_characteristic_notify(&airQuality, HOMEKIT_UINT8(airQualityValue));
        homekit_characteristic_notify(&co2Sensor, HOMEKIT_FLOAT(CO2Value));

        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

void air_quality_init () {

	// uart_param_config(UART_NUM_CO, &uart_config);
	
	// /* Set UART pins (using UART0 default pins ie no changes.) */
    // ESP_ERROR_CHECK(uart_set_pin(UART_NUM_CO, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    // /* Install UART driver, and get the queue. */
    // uart_driver_install(UART_NUM_CO, BUF_SIZE, BUF_SIZE, 20, NULL, 0);

    xTaskCreate(air_quality_task, "Air Quality Sensor", 5012, NULL, 2, NULL);
}

int air_quality_get (int CO2Value){
	printf("CO2 Value: %d\n", CO2Value);
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
	uint8_t response[9] = {0};
	int length = 0;

	uart_write_bytes(UART_NUM_CO, (const char*)command, strlen((const char*)command));

	ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_CO, (size_t*)&length));
	length = uart_read_bytes(UART_NUM_CO, response, length, 100);

	printf("{0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X}\n", (char)response[0], (char)response[1], (char)response[2], (char)response[3], (char)response[4], (char)response[5], (char)response[6], (char)response[7], (char)response[8]);

	/* Check if response is valid */
	if (response[0] != 0xFF) 
		return -1;
	
	if (response[1] != 0x86) 
		return -1;
	

	int ppm = (256 * response[2]) + response[3];
	int temp = response[4]-40;
	byte status = response[5];
	int minimum = (256 * response[6]) + response[7];

    return ppm;
}