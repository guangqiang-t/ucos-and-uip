#ifndef _BSP_SYSTICK_H_
#define _BSP_SYSTICK_H_

#include <stdint.h>
#include <stdbool.h>

void systick_config(void);
void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);

#endif
