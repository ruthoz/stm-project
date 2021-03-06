#include "Button.h"
#include "Buzzer.h"
#include "Clock.h"
#include "Communication.h"
#include "Led.h"
#include "MyMain.h"
#include "CLI.h"
#include "DHT11.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;

Led ledR;
Led ledB;
Button button1;
Buzzer buzzer;
Clock clock1;
Dht11 dht;

//////////////////////////////////////////////////////////////
int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}
//////////////////////////////////////////////////////////////

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if(htim == &htim6){

    ////////////////led////////////////////////////////////
		Led_onTimerInterrupt(&ledB);
		Led_onTimerInterrupt(&ledR);

	//////////////clock///////////////////////////////////
		Clock_onTimerInterrupt(&clock1);

	/////////////buzzer//////////////////////////////////
		Buzzer_onTimerInterrupt(&buzzer);

	///////////button///////////////////////////////////
		Button_onTimerInterrupt(&button1);

	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	Button_interrupt(&button1);
}


void mainloop()
{
	HAL_TIM_Base_Start_IT(&htim6);

	Led_init(&ledB , LD2_GPIO_Port , LD2_Pin );
	Led_init(&ledR , LD3_GPIO_Port , LD3_Pin );
	Buzzer_init(&buzzer);
	Clock_init(&clock1);
	Button_init(&button1, B2_GPIO_Port ,  B2_Pin);
	Cli_init();
	DHT11_init(&dht);
	DHT11_whrithPin(&dht);

	while(1){
		if (Communication_commTask()){
			Communication_handleCommand();
		}
	}

}
