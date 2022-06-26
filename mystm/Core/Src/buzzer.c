#include "buzzer.h"

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;


int note []={ 390, 340, 303, 286, 255, 227, 202};
int noteJonatan []= {255 , 303,  303,  286, 340, 340, 390, 340, 303, 286, 255, 255, 255, 255 , 303,  303,  286, 340, 340 ,390, 303, 255, 255,390};
int periodeJonatan[]={250, 250,  500,  250, 250, 500, 250, 250, 250, 250, 500, 250, 250, 250,  250,  500,  250, 250, 500, 250, 250, 250 ,500,250};


void buzzerInit(BUZZER* buzzer)
{
	buzzer->state = MUSIC_OFF;
	buzzer->sizeOfMusic = (sizeof(noteJonatan) / sizeof(noteJonatan[0]));
	buzzer->currentNote= 0;
	buzzer->counter = 0;
	buzzer->Maxcount = periodeJonatan[0];
}

void playNote(BUZZER* buzzer)
{
	__HAL_TIM_SET_COUNTER(&htim3,0);
	__HAL_TIM_SET_AUTORELOAD(&htim3, noteJonatan[buzzer->currentNote]);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (noteJonatan[buzzer->currentNote]/2));

}

void playNextNote(BUZZER* buzzer)
{
	buzzer->currentNote++;
	if(buzzer->currentNote >= buzzer->sizeOfMusic){
		buzzer->currentNote = 0;
	}
	buzzer->Maxcount = periodeJonatan [buzzer->currentNote];
	playNote(buzzer);
}

void buzzerOnTimerInterrupt(BUZZER* buzzer)
{
	if(buzzer->state == MUSIC_ON){
		buzzer->counter++;
		if(buzzer->counter >= buzzer->Maxcount){
		   playNextNote(buzzer);
		   buzzer->counter = 0;
		}
	}


}
