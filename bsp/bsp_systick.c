#include "bsp_systick.h"
#include "stm32f10x.h"
#include "includes.h"

static uint8_t  fac_us=0;	
static uint16_t fac_ms=0;	

void systick_config(void)
{

	uint32_t RELOAD=0;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//HCLK / 8=9M
	fac_us = SystemCoreClock / 8000000; //1s--9 000 000 --72M--1 000 000 us==>1us=9

//	RELOAD = SystemCoreClock / 8000000;	// cnt/s
	RELOAD = (9000000 / OS_TICKS_PER_SEC);//RELOAD max 16777216
	fac_ms = 1000 / OS_TICKS_PER_SEC;
	
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	SysTick->LOAD = RELOAD;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void delay_us(uint32_t nus)
{		
	uint32_t temp=0;
	uint32_t VAL_Prev=0;
	uint32_t VAL_Now=0; 
	uint32_t VAL_cnt=0;   
	uint32_t Reload=SysTick->LOAD;

	temp = nus*fac_us; 
	VAL_Prev = SysTick->VAL;
	
	while(1)
	{
		VAL_Now = SysTick->VAL;
		if(VAL_Now != VAL_Prev)
		{
			if(VAL_Now < VAL_Prev) 
				{
					VAL_cnt += VAL_Prev-VAL_Now;  
				}
			else                     
				{
					VAL_cnt += Reload - VAL_Now + VAL_Prev;
				}
			VAL_Prev = VAL_Now; 
			if(VAL_cnt >= temp)  break;
		}
	}
}

void delay_ms(uint32_t nms)
{
	if(OSRunning == 1) // os is running
	{
		if(nms > fac_ms) 
		{
			OSTimeDly(nms/fac_ms);
		}
		nms %= fac_ms;
	}
	delay_us((uint32_t)(nms*1000));
}

