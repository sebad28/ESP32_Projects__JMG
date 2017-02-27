/*
 * APA102.h
 *
 *  Created on: 22.02.2017
 *      Author: Jean-Martin George
 */

#ifndef APA102_H_
#define APA102_H_

#include <string.h>
#include "Main_Types.h"
#include "Main_Cfg.h"
#include "uC.h"


//#if (LED_TYPE == LED_TYPE_APA102)

void APA102__init (void);
void APA102__x10 (void);
void APA102__setRGBForLED (RGB_Color_t color, uint16_t led);
void APA102__setRGBForAllLEDs (RGB_Color_t color);
void APA102__resetAllLEDs (void);
void APA102__enableUpdate (uint8_t enable);
void APA102__disableUpdate (uint8_t enable);
void APA102__setGlobalBrightness (uint8_t brightness);
//#if (RGB_LED_ORDER == RGB_LED_ORDER__CONFIGURABLE)
//void APA102__toggleRGBLedOrder (void);
//#endif

#define APA102_GLOBAL_BRIGHNESS__MAX	31
#define APA102_GLOBAL_BRIGHNESS__MIN	1

#define START_FRAME_LENGTH	4

#if (((LEDS_NB / 16) > 1) && ((LEDS_NB % 16) == 0))
#define STOP_FRAME_LENGTH	(LEDS_NB / 16)
#else
#define STOP_FRAME_LENGTH	((LEDS_NB / 16) + 1)
#endif

//#endif

#endif /* APA102_H_ */