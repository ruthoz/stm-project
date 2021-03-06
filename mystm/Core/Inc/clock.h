

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_

#include "main.h"
#include <stdint.h>

typedef struct clock_
{
	uint32_t tick;
	int seconds;
	int minutes;
	int hours;
	int days;

}Clock;

void Clock_init(Clock* clock);
void Clock_onTimerInterrupt(Clock* clock);

#endif /* INC_CLOCK_H_ */
