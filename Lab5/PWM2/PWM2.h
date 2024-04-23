/*
 * PWM2.h
 *
 * Created: 4/17/2024 4:03:21 PM
 *  Author: diego
 */ 


#ifndef PWM2_H_
#define PWM2_H_

#include <stdint.h>
#include <avr/io.h>

void init_PWM2_Fast(void);
void updateDutyCycle2A(uint8_t duty);

#endif /* PWM2_H_ */