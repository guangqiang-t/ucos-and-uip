#ifndef BSP_USART_H_
#define BSP_USART_H_

//#include "stdio.h"
#include "stdint.h"

extern void USART1_Config(void);
extern void print_byte(uint8_t ch);
extern void print_str(const uint8_t *p);
extern void print_n_byte(const uint8_t *p,uint16_t len);
extern void print_int(int32_t num);
extern void print_float(float f);
extern void print_arg(const uint8_t *p,int32_t val);

#endif
