#include "bsp_sw.h"
#include <stm32f10x.h>

enum sw {HK=1,LK=2};
enum sw_value {ON=1,OFF=0};

void sw_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		          
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		          
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void sync_sw(int32_t sw ,int32_t sw_value)
{
	switch(sw)
	{
		case (HK):
		{
			if(sw_value==ON)
			{
				GPIO_SetBits(GPIOA,GPIO_Pin_12);
			}
			else if(sw_value==OFF)
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_12);
			}
			break;
		}
		case (LK):
		{
			if(sw_value==ON)
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_5);
			}
			else if(sw_value==OFF)
			{
				GPIO_ResetBits(GPIOB,GPIO_Pin_5);
			}
			break;
		}
		default: break;
	}
}
