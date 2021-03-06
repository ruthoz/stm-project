#include "DHT11.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim16;

GPIO_InitTypeDef GPIO_InitStruct = {0};
uint8_t buffDht11 [5] = {0};
uint8_t oneBit = 0;


void DHT11_init(Dht11* dht)
{
	dht->GPIO_Pin = D4_Pin;
	dht->GPIOx = D4_GPIO_Port;
	dht->temperature = 0;
	dht->humidity = 0;
	dht->checkSum = 0;
}

void DHT11_setOutput(Dht11* dht)
{
	GPIO_InitStruct.Pin = dht->GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht->GPIOx, &GPIO_InitStruct);
}

void DHT11_setInput(Dht11* dht)
{
	GPIO_InitStruct.Pin = dht->GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht->GPIOx, &GPIO_InitStruct);
}

void DHT11_whrithPin(Dht11* dht)
{
	HAL_TIM_Base_Start(&htim16);
	DHT11_setOutput(dht);
	__HAL_TIM_SET_COUNTER(&htim16 , 0);
	HAL_GPIO_WritePin(dht->GPIOx, dht->GPIO_Pin, 0);
	while (__HAL_TIM_GET_COUNTER(&htim16) < 18500){

	}
	HAL_GPIO_WritePin(dht->GPIOx, dht->GPIO_Pin, 1);
	__HAL_TIM_SET_COUNTER(&htim16 , 0);

	DHT11_getStatus(dht);
}

void DHT11_getStatus(Dht11* dht){
	DHT11_setInput(dht);
	while (HAL_GPIO_ReadPin(dht->GPIOx, dht->GPIO_Pin) == 1){
		if(__HAL_TIM_GET_COUNTER(&htim16) > 60){
				return;
		}
	}
	__HAL_TIM_SET_COUNTER(&htim16 , 0);
	while (HAL_GPIO_ReadPin(dht->GPIOx, dht->GPIO_Pin) == 0){
		if(__HAL_TIM_GET_COUNTER(&htim16) > 100){
		    return;
		}
    }
	__HAL_TIM_SET_COUNTER(&htim16 , 0);
	while (HAL_GPIO_ReadPin(dht->GPIOx, dht->GPIO_Pin) == 1){
			if(__HAL_TIM_GET_COUNTER(&htim16) > 100){
			    return;
			}
	}
    DHT11_waitForSignal(dht);
}

void DHT11_waitForSignal(Dht11* dht){
	for(int x=0; x<5; x++){
		for(int i=0; i<8; i++){
			while (HAL_GPIO_ReadPin(dht->GPIOx, dht->GPIO_Pin) == 0){

			}
			buffDht11 [x] = DHT11_readNextBit(dht);
		}
	}
	dht->humidity = buffDht11[0] + (buffDht11[1]*0.1);
	dht->temperature = buffDht11[2] + (buffDht11[3]*0.1);
	dht->checkSum = buffDht11[4];
	DHT11_printBuff(dht);
}

int DHT11_readNextBit(Dht11* dht)
{

	__HAL_TIM_SET_COUNTER(&htim16 , 0);
	while (HAL_GPIO_ReadPin(dht->GPIOx, dht->GPIO_Pin) == 1){

	}
	oneBit <<= 1;
	if (__HAL_TIM_GET_COUNTER(&htim16) > 50){
		oneBit |= 1;
	}
	return oneBit;
}

void DHT11_printBuff(Dht11* dht)
{
	printf ("--------------------------------- \n\r");
	printf ("RH = %u.%u \n\r", buffDht11[0] , buffDht11[1]);
	printf ("T = %u.%u \n\r", buffDht11[2] , buffDht11[3]);
	printf ("check sum = %d  \n\r", buffDht11[4]);
//	printf ("RH = %f \n\r", dht->humidity);
//	printf ("T = %f \n\r", dht->temperature);
//	printf ("check sum = %d  \n\r", dht->checkSum);
}

