/**
 ******************************************************************************
 * @file           	led.h
 *
 * @author 			Mart van Vliet
 * @date 			08 June 2019
 * @brief
 ******************************************************************************
 **
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H__
#define __LED_H__

/* Includes ------------------------------------------------------------------*/

#include "main.h"




/* Defines -------------------------------------------------------------------*/
#define NAME_DEF				"led dimmer"

#define LED_TIMER          		LEDC_TIMER_0
#define LED_MODE          		LEDC_HIGH_SPEED_MODE
#define LED_GPIO       		    18
#define LED_CHANNEL    			LEDC_CHANNEL_0
#define LED_FADE_TIME  		    500

#ifdef INVERTED_LED
	#define INVMOD(x)  (100-x)
#else
	#define INVMOD(x)	x
#endif


/* Function prototypes -------------------------------------------------------*/
void 			led_set				(uint8_t bright);
void 			led_init			(void);
void 			led_identify_task	(void *_args);
void 			led_identify		(homekit_value_t _value);
homekit_value_t led_on_get			(void);
void 			led_on_set			(homekit_value_t value);
homekit_value_t led_bright_get		(void);
void 			led_bright_set		(homekit_value_t value);

#endif /* __LED_H__ */