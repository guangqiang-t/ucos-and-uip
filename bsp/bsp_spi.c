#include "bsp_spi.h"
#include "stm32f10x.h"

void spi1_config(void)
{
		//开启SPI接口 并执行初始化
		//PA5- SPISCK;  PA6- SPIMISO; PA7- SPIMOSI;
		GPIO_InitTypeDef GPIO_InitStructure;
		SPI_InitTypeDef SPI_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		//初始化SPI IO 使用PA5 PA6 PA7
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 |  GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		          
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		          
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		
	
		//开启SPI时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
		SPI_Cmd(SPI2, DISABLE);
		//SPI模式设置
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(SPI1, &SPI_InitStructure);
		
		//Enable SS   At PA4
		SPI_SSOutputCmd(SPI1,ENABLE);
		//使能SPI
		SPI_Cmd(SPI1, ENABLE);
	
}
uint8_t spi_rw(uint8_t wchar)
{
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); 
		SPI_I2S_SendData(SPI1, wchar); 
		//等待接收完毕
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		//返回一个字节
		return (uint8_t)SPI_I2S_ReceiveData(SPI1);
}
