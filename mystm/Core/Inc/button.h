/*
 * button.h
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include <stdint.h>

typedef enum StateButon_
{
	BUTTON_STATE_NONE,
	BUTTON_STATE_PRESS,
	BUTTON_LONG_PRESS,
	BUTTON_DOBULE_PRESS,
}StateButon;

typedef struct _button
{
	StateButon state;
	uint32_t timeTickOn;
	uint32_t timeTickPrevOff;
	uint32_t timeTickOff;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;

}BUTTON;

void buttonInit(BUTTON* button , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
void buttonInterrupt(BUTTON* button);

#endif /* INC_BUTTON_H_ */