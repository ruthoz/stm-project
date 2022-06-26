#include "button.h"
#include "main.h"
#include "led.h"

extern LED ledR;
extern LED ledB;

uint32_t DelayTick = 0;


void buttonInit(BUTTON* button , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
	button->state = BUTTON_STATE_NONE;
	button->timeTickOn = 0 ;
	button->timeTickPrevOff = 0 ;
	button->timeTickOff = 0 ;
	button->GPIOx = GPIOx;
	button->GPIO_Pin = GPIO_Pin;
}


void buttonInterrupt(BUTTON* button)
{
	if(HAL_GPIO_ReadPin(button->GPIOx, button->GPIO_Pin) == 1){
		button->timeTickPrevOff = button->timeTickOff;
		button->timeTickOff = HAL_GetTick();
	}

	else if(HAL_GPIO_ReadPin(button->GPIOx, button->GPIO_Pin) == 0){
		button->timeTickOn = HAL_GetTick();
	}

	DelayTick = button->timeTickOff - button->timeTickOn;


	if(DelayTick > 500){
	   button->state = BUTTON_LONG_PRESS;
	}
	else{
	   if((button->timeTickOn - button->timeTickPrevOff ) < 200 ){
		   button->state = BUTTON_DOBULE_PRESS;
	   }
	   else{
		   button->state = BUTTON_STATE_PRESS;
	   }
	}

}


