#ifndef _bsp_sw_H_
#define _bsp_sw_H_

#include <stdint.h>
#include "stm32f10x.h"

enum sw {HK=1,LK=2};
enum sw_value {NO=1,NC=0};

void sw_config(void);
void sync_sw(int32_t sw ,int32_t sw_value);

#endif //_bsp_sw_H_
