#ifndef _BSP_SYSTICK_H_
#define _BSP_SYSTICK_H_

#include <stdint.h>
#include <stdbool.h>

void SysTickConfig(void);
void DelayMs(uint32_t nms);
void DelayUs(uint32_t nus);

#endif
