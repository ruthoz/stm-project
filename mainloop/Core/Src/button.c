#include "button.h"
#include "main.h"
#include "led.h"

extern Led ledR;
extern Led ledB;

void Button_init(Button* button , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	button->state = BUTTON_UP;
	button->timetick = 0 ;
	button->GPIOx = GPIOx;
	button->GPIO_Pin = GPIO_Pin;
}


void Button_interrupt(Button* button)
{
	if(button->state == BUTTON_DOWN)
	{
		button->state = BUTTON_UP;
		if(HAL_GetTick()- button->timetick <= 500)
		{
			Led_off(&ledB);
		}
		else
		{
			 Led_blink( &ledB, 300);
		}

	}

	else if(button->state == BUTTON_UP)
	{
		button->state = BUTTON_DOWN;
		button->timetick = HAL_GetTick();
	}

}


