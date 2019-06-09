/**
 ******************************************************************************
 * @file    	led.c
 *
 * @author 		Mart van Vliet
 * @date 		08 June 2019
 * @brief
 ******************************************************************************
 **
 *
 ******************************************************************************
 */

#include "led.h"


const int led_gpio = 2;
uint8_t led_bright = 100;
bool led_on = true;

/*
 * Prepare and set configuration of timers
 * that will be used by LED Controller
 */
ledc_timer_config_t led_dim_timer = {
	.speed_mode 	= LED_MODE,      		// timer mode
	.duty_resolution= LEDC_TIMER_8_BIT, 	// resolution of PWM duty
	.freq_hz 		= 100000,				// frequency of PWM signal
	.timer_num 		= LED_TIMER				// timer index
};

/**
 * Prepare individual configuration
 * for each channel of LED Controller
 * by selecting:
 * - controller's channel number
 * - output duty cycle, set initially to 0
 * - GPIO number where LED is connected to
 * - speed mode, either high or low
 * - timer servicing selected channel
 *   Note: if different channels use one timer,
 *         then frequency and bit_num of these channels
 *         will be the same
 */
ledc_channel_config_t led_dim_channel = {
	.channel    	= LED_CHANNEL,
	.duty       	= 0,
	.gpio_num   	= LED_GPIO,
	.speed_mode 	= LED_MODE,
	.hpoint     	= 0,
	.timer_sel  	= LED_TIMER
};



void led_set(uint8_t bright) {
	uint16_t dutyCycle;

	if (led_on)
		dutyCycle = (int)(INVMOD(bright)*2.56);
	else 
		dutyCycle = (int)(INVMOD(0)*2.56);
	


	printf("Current Brightness: %d\n", bright);
	printf("Current Brightness: %f\n", (INVMOD(bright)*2.56));
	printf("Current Brightness: %d\n", dutyCycle);
	
	ledc_set_fade_with_time(led_dim_channel.speed_mode,
		led_dim_channel.channel, dutyCycle, LED_FADE_TIME);
	ledc_fade_start(led_dim_channel.speed_mode,
		led_dim_channel.channel, LEDC_FADE_WAIT_DONE);
	
}

void led_init() {

	// Set configuration of timer0 for high speed channels
    ledc_timer_config(&led_dim_timer);

	ledc_channel_config(&led_dim_channel);

	// Initialize fade service.
    ledc_fade_func_install(0);

    led_set(led_bright);
}

void led_identify_task(void *_args) {
    for (int i=0; i<3; i++) {
        led_set(100);
        vTaskDelay(600 / portTICK_PERIOD_MS);
        led_set(0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    led_set(led_bright);

    vTaskDelete(NULL);
}

void led_identify(homekit_value_t _value) {
    printf("LED identify\n");
    xTaskCreate(led_identify_task, "LED identify", 2056, NULL, 2, NULL);
}

homekit_value_t led_on_get() {
    return HOMEKIT_BOOL(led_on);
}

void led_on_set(homekit_value_t value) {
    if (value.format != homekit_format_bool) {
        printf("Invalid value format: %d\n", value.format);
        return;
    }

	
    led_on = value.bool_value;

	led_set(led_bright);
}

homekit_value_t led_bright_get() {
    return HOMEKIT_INT(led_bright);
}

void led_bright_set(homekit_value_t value) {
    if (value.format != homekit_format_int) {
        printf("Invalid value format: %d\n", value.format);
        return;
    }

    led_bright = value.int_value;
    led_set(led_bright);
}