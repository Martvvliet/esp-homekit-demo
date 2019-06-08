/**
  ******************************************************************************
  * @file           	main.h
  *
  * @author 			Mart van Vliet
  * @date 				08 June 2019
  * @brief          	Main program header
  ******************************************************************************
  **
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <esp_wifi.h>
#include <esp_event_loop.h>
#include <esp_log.h>
#include <nvs_flash.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include "wifi.h"


#include "led.h"


void on_wifi_ready(void);
void wifi_init(void);

#endif /* __MAIN_H__ */