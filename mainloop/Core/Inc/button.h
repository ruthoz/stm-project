/*
 * button.h
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

typedef enum StateButon_
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTON_LONG_PRERRS,
	BUTON_SHORT_PREES,
}StateButon;

typedef struct _button
{
	StateButon state;
	int timetick;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;

}BUTTON;

void buttonInit(BUTTON* button , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
void buttonInterrupt(BUTTON* button);

#endif /* INC_BUTTON_H_ */
