#ifndef bsp_delay_H_
#define bsp_delay_H_

#include "stm32f10x.h"

#define CPU_F 72

void delay_us(unsigned int time);
void delay_ms(unsigned int time);

#endif
