#include "led.h"

void Led_init(Led* led , GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin)
{
 led->state = STATE_OFF;
 led->counter = 0 ;
 led->GPIOx = GPIOx;
 led->GPIO_Pin = GPIO_Pin;
}

void Led_on(Led* led)
{
	led->state = STATE_ON;
    HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, 1);
}

void Led_off(Led* led)
{
	led->state = STATE_OFF;
    HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, 0);
}
void Led_blink(Led* led, int period)
{
	led->state = STATE_BLINKING;
	led->period = period;
	led->counter = 0;
}
void Led_onTimerInterrupt(Led* led)
{
	if(led->state == STATE_BLINKING)
	{
		led->counter++;
		if((led->counter) >= (led->period) )
		{
			HAL_GPIO_TogglePin(led->GPIOx, led->GPIO_Pin);
			led->counter = 0;

		}
	}
}

void Led_onPeriodicTask(Led* led);
