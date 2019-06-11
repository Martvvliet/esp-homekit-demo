/**
 ******************************************************************************
 * @file		co.h
 *
 * @author		Mart van Vliet
 * @date		09 June 2019
 * @brief
 ******************************************************************************
 **
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CO_H__
#define __CO_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Defines -------------------------------------------------------------------*/
#define NAME_CO2			"Air quality"

#define UART_NUM_CO			UART_NUM_2
#define BUF_SIZE		   (1024 * 2)

/* Extern declare ------------------------------------------------------------*/
extern homekit_characteristic_t airQuality;
extern homekit_characteristic_t co2Sensor;


/* Function prototypes -------------------------------------------------------*/
extern void 	air_quality_init	(void);
void 			air_quality_task	(void *_args);
void 			air_quality_identify(homekit_value_t _value);
int 			air_quality_get		(int CO2Value);
float 			co2_sensor_get		(void);


#endif /* __CO_H__ */