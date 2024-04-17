/*
 * PWM1.h
 *
 * Created: 4/17/2024 11:14:29 AM
 *  Author: diego
 */ 


#ifndef PWM1_H_
#define PWM1_H_

#include <stdint.h>
#include <avr/io.h>

void init_PWM1_Fast(void);
void updateDutyCycleA(uint16_t duty);


#endif /* PWM1_H_ */