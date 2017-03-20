#ifndef _bsp_logic_H_
#define _bsp_logic_H_

#include <stdint.h>

extern void logic_config(void);
extern void sync_logic(const uint8_t *dat,uint8_t len);

#endif//_bsp_logic_H_
