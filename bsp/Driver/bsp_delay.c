#include "bsp_delay.h"

void delay_us(unsigned int time)
{
	SysTick->LOAD=CPU_F*time;
	SysTick->CTRL=0x00000005;
	while(!(SysTick->CTRL&0x00010000));
	SysTick->CTRL=0x00000004;
}

void delay_ms(unsigned int time)
{
	int i;
	for(i=995;i>0;i--)
	{
		delay_us(time);
	}
}
