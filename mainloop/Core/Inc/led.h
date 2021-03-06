/*
 * led.h
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"

typedef enum LEDstate_
{
	STATE_OFF,
	STATE_ON,
	STATE_BLINKING,
}LedState;

typedef struct _led
{
	LedState state;
	int counter;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int period;

}Led;

void Led_init(Led* led , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
void Led_on(Led* led);
void Led_off(Led* led);
void Led_blink(Led* led, int period);
void Led_onTimerInterrupt(Led* led);
void Led_onPeriodicTask(Led* led);


#endif /* INC_LED_H_ */
