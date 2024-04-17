/*
 * CFile1.c
 *
 * Created: 4/17/2024 11:16:27 AM
 *  Author: diego
 */ 

#include "PWM1.h"

void init_PWM1_Fast(void){
	DDRB |= (1 << DDB1);
	
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1A |= (1<<COM1A1);
	
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12)|(1<<WGM13);
	
	//PRESCALER DE 256
	TCCR1B |= (1<<CS12);
	
	
	//TOP DE 1249
	TCNT1L = 0xE1;
	TCNT1H = 0x04;
}

void updateDutyCycleA(uint16_t duty){
	OCR1AL = duty;
	OCR1AH = duty>>8;
}