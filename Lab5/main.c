/*
 * Lab5.c
 *
 * Created: 4/17/2024 11:13:12 AM
 * Author : diego
 */ 

#include <avr/io.h>
#include "PWM1/PWM1.h"
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>

uint8_t valor_pot = 0;
uint16_t dutyCycle = 0;

void setup(void);

uint16_t mapADCtoServo(uint8_t valor_ADC){
	return (uint16_t)(((float)valor_ADC/255)*(124.9-62.45)+62.45);
}

int main(void)
{
    /* Replace with your application code */
	setup();
    while (1) 
    {
		dutyCycle = mapADCtoServo(valor_pot);
		updateDutyCycleA(dutyCycle);
    }
}

void init_ADC(void){
	ADMUX = 0;
	// Vref = AVCC = 5V
	ADMUX |= (1<<REFS0);
	
	// Justificado a la izquierda
	ADMUX |= (1<<ADLAR);
	
	// Selección del canal A7
	ADMUX |= 0x07;
	
	ADCSRA = 0;
	
	// Habilitar ADC
	ADCSRA = (1<<ADEN);
	
	// Habilitar auto-trigger
	ADCSRA |= (1<<ADATE);
	
	// Máscara de la interrupción del ADC
	ADCSRA |= (1<<ADIE);
	
	// Prescaler del ADC a 128
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
	ADCSRB = 0;
	
	// Iniciar primera conversión
	ADCSRA |= (1<<ADSC);
	
}

void setup(void){
	cli();
	DDRC = 0;
	init_PWM1_Fast();
	init_ADC();
	sei();
}

ISR(ADC_vect){
	valor_pot = ADCH;
}
