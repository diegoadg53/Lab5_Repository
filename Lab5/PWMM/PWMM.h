/*
 * IncFile1.h
 *
 * Created: 4/22/2024 6:50:13 PM
 *  Author: diego
 */ 


#ifndef PWMM_H_
#define PWMM_H_

#include <stdint.h>
#include <avr/io.h>

void init_PWMM(void);

void intensity_changer(uint8_t intensidad);


#endif /* INCFILE1_H_ */