#ifndef _bsp_74hc595_H_
#define _bsp_74hc595_H_

#include <stdint.h>
#include "stm32f10x.h"

extern void _74hc595_config(uint8_t len);
extern void _74hc595_send_n_char(const uint8_t *pata,uint8_t n);

#endif //_bsp_74hc595_H_
