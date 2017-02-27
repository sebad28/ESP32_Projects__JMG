/*
 * LedController.c
 *
 *  Created on: 08.02.2017
 *      Author: Jean-Martin George
 */


#include "LedController.h"
#include "freertos/FreeRTOS.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_task_wdt.h"
#include "nvs_flash.h"
#include "driver/uart.h"
#include "Main_Cfg.h"
#include "ArtNet.h"
#include "driver/timer.h"
#include <string.h>

#include "Drivers.h"


uint8_t ledData[NUMBER_OF_LEDS_CHANNELS];
uint8_t newDataTrigger;


esp_err_t LedController__storeLedData(uint8_t *data, uint16_t start, uint16_t length)
{
	esp_err_t retVal;

	if (!newDataTrigger)
	{
		memcpy(&ledData[start], data, length);
		retVal = ESP_OK;
	}
	else
	{
		retVal = ESP_FAIL;
	}

	return retVal;
}


esp_err_t LedController__outputLedData (void)
{
	esp_err_t retVal = ESP_FAIL;

	if (!newDataTrigger)
	{
		newDataTrigger = true;
		retVal = ESP_OK;
	}

	return retVal;
}


void LedController__init (void)
{

}


void LedController__mainFunction (void *param)
{
	uint16_t idxLed;

	while (1)
	{
		if (newDataTrigger)
		{
			gpio_set_level(TEST_LED_LEDCTRL, 1);

			for (idxLed = 0; idxLed < NUMBER_OF_LEDS; idxLed++)
			{
				APA102__setRGBForLED(LEDMatrix__getRGBColorFromComponents(ledData[(3 * idxLed) + 2], ledData[(3 * idxLed) + 1], ledData[3 * idxLed]), idxLed);
			}

			APA102__x10();

			newDataTrigger = false;

			gpio_set_level(TEST_LED_LEDCTRL, 0);
		}

		vTaskDelay(1 / portTICK_PERIOD_MS);
	}
}