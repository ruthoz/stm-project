#include "main.h"
#include "myMain.h"
#include "rtc.h"
#include "buzzer.h"
#include <string.h>
#include <stdio.h>


extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;


Buzzer buzzer;

int _write(int fd, char* ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_Base_Stop(&htim3);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
	rtcOnTimerInterrupt();
}

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{

}


/////////////////////////////////////////////////////////////////////////
// Communication task definitions and functions
/////////////////////////////////////////////////////////////////////////

#define MAX_BUFFER_LENGTH 100

uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
int cmdcount = 0;
int cmdprint = 0;
int flagSystemLoock = 0;

int Communication_commTask()
{

	uint8_t ch;

	HAL_StatusTypeDef Status = HAL_UART_Receive(&huart2, &ch, 1, 10);
	if (Status != HAL_OK)
	{
		if ((huart2.Instance->ISR & USART_ISR_ORE) != 0)
		{
			__HAL_UART_CLEAR_OREFLAG(&huart2);
		}

		// here we have a time to print the command
		while (cmdprint < cmdcount)
		{
			HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
		}

		return 0;
	}

	if (ch != '\r' && ch != '\n')
	{
		//HAL_UART_Transmit(&huart2, &ch, 1, 0xFFFF);

		if (cmdcount >= MAX_BUFFER_LENGTH)
		{
			cmdcount = 0;
			cmdprint = 0;
		}

		cmdbuffer[cmdcount++] = ch;
		return 0;
	}

	// here we have a time to print the command
	while (cmdprint < cmdcount)
	{

		     HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
			printf("The system lock \r\n");
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 0xFFFF);

	cmdbuffer[cmdcount] = 0;
	cmdcount = 0;
	cmdprint = 0;
	return 1;
}


void Communication_handleCommand()
{
	char cmd[20];
    uint32_t pass;
    static int Lock3min = 0;
    static int Lock5min = 0;


  int params = sscanf((const char*)cmdbuffer, "%s %lu", cmd, &pass);
  if (params == 0){
	  return;
  }
  lockOrOpen();
  if (flagSystemLoock == 1){
	  printf("The system is lock \r\n");
  	  return;
  }

  if (strcmp(cmd, "code") == 0){
	  if(getCode(pass)){
		  printf("password ok\r\n");
		  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
		  Lock3min = 0 ;
		  Lock5min = 0 ;
	  }
	  else{
		  HAL_TIM_Base_Start(&htim3);
		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
		  Buzzer_playNote(&buzzer);
		  if(Lock3min<2){
			 Lock3min++;
			 Lock5min++;
			 printf("wrong password \r\n");
		  }
		  else{
			 if(Lock5min > 5){
				 lockSystem5min();
				 HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, 1);
				 printf("wrong password. try again for 5 min \r\n");
		0		 Lock5min = 0;
			 }
			 else{
				 flagSystemLoock = 1 ;
				 HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, 1);
				 printf("wrong password. try again for 30 seconds \r\n");
				 Lock3min = 0 ;
			 }

		  }
	  }
  }

  else if (strcmp(cmd, "stop") == 0){
	  HAL_TIM_Base_Stop(&htim3);
	  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
  }
  else{
	  printf("Invalid command\r\n");
  }
}




void mainloop()
{
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
	Buzzer_init(&buzzer);
	setCode(1234);

	while (1) {

		if (Communication_commTask()) {
			Communication_handleCommand();
		}

	}
}
