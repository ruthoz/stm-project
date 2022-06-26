

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_

#include "main.h"
#include <stdint.h>

typedef struct _clock
{
	uint32_t tick;
	int seconds;
	int minutes;
	int hours;
	int days;

}CLOCK;

void clockInit(CLOCK* clock);
void clockOnTimerInterrupt(CLOCK* clock);



#endif /* INC_CLOCK_H_ */
