/*
 * CFile1.c
 *
 * Created: 4/22/2024 6:50:40 PM
 *  Author: diego
 */ 

#include "PWMM.h"

void init_PWMM(void){
	DDRD |= (1<<DDD2);
	
	TCCR0B |= (1 << CS02);//|(1 << CS00);
	
	TIMSK0 |= (1 << TOIE0);
	
	TCNT0 = 61;
}

void intensity_changer(uint8_t intensidad){
	uint8_t valor = (uint8_t)(((float)intensidad/255)*(255-61)+61); 
	if (TCNT0 <= valor)
	{
		PORTD |= (1 << PORTD2);
	} 
	else
	{
		PORTD &= ~(1 << PORTD2);
	}
}