#include "bsp_usart.h"
#include "stm32f10x.h"

int fputc(int ch,FILE *f);//printf

// #include "stdio.h"
/**
  * @brief UART1  init  PA9 PA10
  * @param None 
  * @retval None
  */
void USART1_Config(void)
{
	
	 GPIO_InitTypeDef GPIO_InitStructure;

	 USART_InitTypeDef USART_InitStructure;

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

		// Configure USART1_Tx as alternate push-pull
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
		// Configure USART1_Rx as input floating
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_Init(GPIOA, &GPIO_InitStructure); 

	 USART_InitStructure.USART_BaudRate = 115200;
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;
	 USART_InitStructure.USART_Parity = USART_Parity_No ;
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 
	 USART_Init(USART1, &USART_InitStructure);
	
//	 USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	 USART_Cmd(USART1, ENABLE); 
}

int fputc(int ch, FILE *f)
{
  while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
	USART_SendData(USART1, (unsigned char) ch);
  return (ch);
}
