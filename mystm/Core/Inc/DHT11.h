
#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "main.h"
#include <stdint.h>

typedef enum StateDht11_
{
	OUTPUT,
	INPUTT,
}StateDht11;

typedef struct _Dht11
{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	double temperature;
	double humidity;
	int checkSum;
}Dht11;

void DHT11_init(Dht11* dht);
void DHT11_setOutput(Dht11* dht);
void DHT11_setInput(Dht11* dht);
void DHT11_whrithPin(Dht11* dht);
void DHT11_getStatus(Dht11* dht);
void DHT11_waitForSignal(Dht11* dht);
int DHT11_readNextBit(Dht11* dht);
void DHT11_printBuff(Dht11* dht);

#endif /* INC_DHT11_H_ */
