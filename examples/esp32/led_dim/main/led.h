/**
  ******************************************************************************
  * @file           	led.h
  *
  * @author 			Mart van Vliet
  * @date 				08 June 2019
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

/* Function prototypes -------------------------------------------------------*/
void 			led_write(bool on);
void 			led_init(void);
void 			led_identify_task(void *_args);
void 			led_identify(homekit_value_t _value);
homekit_value_t led_on_get();
void 			led_on_set(homekit_value_t value);

#endif /* __LED_H__ */
