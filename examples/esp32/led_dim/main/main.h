/**
 ******************************************************************************
 * @file           	main.h
 *
 * @author 			Mart van Vliet
 * @date 			08 June 2019
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
#include <esp_err.h>
#include <nvs_flash.h>

#include "driver/ledc.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

#include "wifi.h"
#include "led.h"
#include "co.h"

#define NAME_DEF				"ESP Homekit"
#define MANUFACTURER_DEF		"Mart v Vliet"
#define SERIAL_NUMBER_DEF		"029314578"
#define MODEL_DEF				"V0.1"
#define FIRMWARE_REVISION_DEF	"V0.1"

#define PASSWORD				"123-45-789"

#define INVERTED_LED

void 			on_wifi_ready(void);

#endif /* __MAIN_H__ */