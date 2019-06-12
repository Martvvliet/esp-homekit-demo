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

#define UART_NUM			UART_NUM_1
#define UART_TX_PIN			GPIO_NUM_4
#define UART_RX_PIN			GPIO_NUM_5
#define UART_RTS_PIN		UART_PIN_NO_CHANGE
#define UART_CTS_PIN		UART_PIN_NO_CHANGE
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