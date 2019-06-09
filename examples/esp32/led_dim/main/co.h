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
#define NAME_CO2				"Air quality"

/* Extern declare ------------------------------------------------------------*/
extern homekit_characteristic_t airQuality;
extern homekit_characteristic_t co2Sensor;


/* Function prototypes -------------------------------------------------------*/
extern void 	air_quality_init	(void);
void 			air_quality_task	(void *_args);
void 			air_quality_identify(homekit_value_t _value);
homekit_value_t air_get				(void);
homekit_value_t co2_get				(void);


#endif /* __CO_H__ */