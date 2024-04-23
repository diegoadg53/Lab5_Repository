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
	
	//PRESCALER DE 64
	TCCR1B |= (1<<CS11)|(1<<CS10);
	
	
	//TOP DE 1249
	ICR1H = 0x04;
	ICR1L = 0xE1;
	
}

void updateDutyCycle1A(uint16_t duty){
	/*uint8_t temp = duty;
	OCR1AL = temp;
	duty >>= 8;
	temp = duty;
	OCR1AH = temp;*/
	OCR1AH = (duty & 0xFF00) >> 8;
	OCR1AL = (duty & 0x00FF);
}