/*
 * Lab5.c
 *
 * Created: 4/17/2024 11:13:12 AM
 * Author : diego
 */ 

#define F_CPU 4000000
#include <avr/io.h>
#include "PWM1/PWM1.h"
#include "PWM2/PWM2.h"
#include "PWMM/PWMM.h"
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

uint8_t valor_pot1 = 0;
uint16_t dutyCycle1 = 0;
uint8_t valor_pot2 = 0;
uint8_t dutyCycle2 = 0;
uint8_t valor_pot3 = 0;
uint8_t alternador_pots = 0;

void setup(void);

uint16_t mapADCtoServo1(uint8_t valor_ADC1){
	return (uint16_t)(((float)valor_ADC1/255)*(149.88-37.47)+37.47);
}

uint8_t mapADCtoServo2(uint8_t valor_ADC2){
	return (uint8_t)(((float)valor_ADC2/255)*(31-8)+8);
}

int main(void)
{
	CLKPR = (1<<CLKPCE);
	CLKPR = (1<<CLKPS1); // CLK a 4 MHz
	setup();
    while (1) 
    {
		dutyCycle1 = mapADCtoServo1(valor_pot1);
		updateDutyCycle1A(dutyCycle1);
		
		dutyCycle2 = mapADCtoServo2(valor_pot2);
		updateDutyCycle2A(dutyCycle2);
		
		intensity_changer(valor_pot3);
    }
}

void init_ADC(void){
	ADMUX = 0;
	// Vref = AVCC = 5V
	ADMUX |= (1<<REFS0);
	// Justificado a la izquierda
	ADMUX |= (1<<ADLAR);
	// Selección del canal A7
	//ADMUX |= 0x07;
	ADCSRA = 0;
	// Habilitar ADC
	ADCSRA |= (1<<ADEN);
	// Habilitar auto-trigger
	//ADCSRA |= (1<<ADATE);
	// Máscara de la interrupción del ADC
	ADCSRA |= (1<<ADIE);
	// Prescaler del ADC a 128
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
	ADCSRB = 0;
	
	DIDR0 |= (1<<ADC1D);
	
	// Iniciar primera conversión
	ADCSRA |= (1<<ADSC);
	
}

void setup(void){
	cli();
	DDRC = 0;
 	init_PWM1_Fast();
	init_PWM2_Fast();
	init_PWMM();
	init_ADC();
	sei();
}

ISR(ADC_vect){
	ADCSRA &= ~(1<<ADEN);
	if (alternador_pots==0)
	{
		
		ADMUX = ((ADMUX & ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0))) | ((1<<MUX2)|(1<<MUX1)|(1<<MUX0)));
		valor_pot1 = ADCH;
		alternador_pots += 1;
	} 
	else if (alternador_pots == 1)
	{
		
		ADMUX = ((ADMUX & ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0))) | (1<<MUX0));
		valor_pot2 = ADCH;
		alternador_pots += 1;
	} else {
		ADMUX = (ADMUX & ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0)));
		valor_pot3 = ADCH;
		alternador_pots = 0;
	}
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADSC);
	ADCSRA |= (1<<ADIF);
}

ISR(TIMER0_OVF_vect){
	TCNT0 = 61;
}
