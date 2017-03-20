#ifndef bsp_USART_H_
#define bsp_USART_H_


#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"

void usart1_config(void);

int fputc(int ch,FILE *f);//printf
void uip_log(char *m);

#endif
