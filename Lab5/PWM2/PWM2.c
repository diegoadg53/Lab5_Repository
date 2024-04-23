/*
 * PWM2.c
 *
 * Created: 4/17/2024 4:04:45 PM
 *  Author: diego
 */ 

#include "PWM2.h"

void init_PWM2_Fast(void){
	DDRB |= (1 << DDB3);
	
	TCCR2A = 0;
	TCCR2B = 0;
	TCCR2A |= (1<<COM2A1);
	
	TCCR2A |= (1<<WGM21)|(1<<WGM20);
	//TCCR2B |= (1<<WGM22);
	
	//PRESCALER DE 256
	TCCR2B |= (1<<CS22)|(1<<CS21);
	
	//TCNT2 = 177;
	
}

void updateDutyCycle2A(uint8_t duty){
	/*uint8_t temp = duty;
	OCR1AL = temp;
	duty >>= 8;
	temp = duty;
	OCR1AH = temp;*/
	OCR2A = duty;
}