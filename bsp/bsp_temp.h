#ifndef _bsp_temp_H_
#define _bsp_temp_H_

#include "stdint.h"
#include "stm32f10x.h"


extern volatile uint16_t g_adc_value[4];
extern uint16_t g_temp;

extern void internal_temp_config(void);
extern int16_t get_temp(void);

#endif //_bsp_temp_H_

