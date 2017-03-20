#ifndef _bsp_pwm_H_
#define _bsp_pwm_H_

#include <stdint.h>
#include "stm32f10x.h"

enum pwm_ctrl {motor=1,led_w=2,led_r=3,led_g=4,led_b=5};
//extern enum pwm_ctrl;
// extern enum sw_value;

void pwm_config(uint16_t freq);//config the timer with freq:Hz
void sync_pwm(int32_t pwm_ctrl,uint8_t pwm);


#endif //_bsp_pwm_H_
