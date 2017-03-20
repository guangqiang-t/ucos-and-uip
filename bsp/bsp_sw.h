#ifndef _bsp_sw_H_
#define _bsp_sw_H_

#include <stdint.h>
#include "stm32f10x.h"

//extern enum sw;
//extern enum sw_value;

void sw_config(void);
void sync_sw(int32_t sw ,int32_t sw_value);

#endif //_bsp_sw_H_
