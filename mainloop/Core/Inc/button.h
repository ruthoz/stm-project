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
}StateButton;

typedef struct _button
{
	StateButton state;
	int timetick;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;

}Button;

void Button_init(Button* button , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin);
void Button_interrupt(Button* button);

#endif /* INC_BUTTON_H_ */
