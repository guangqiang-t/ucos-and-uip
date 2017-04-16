#include "bsp_usart.h"
#include "stm32f10x.h"
#include "os_app.h"
// #include "stdio.h"




/**
  * @brief UART1  init  PA9 PA10
  * @param None 
  * @retval None
  */
void usart1_config(void)
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


void print_byte(uint8_t ch)
{
	while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
	USART_SendData(USART1, (uint8_t) ch);
}

void print_str(const int8_t *p)
{
//	OS_ENTER_CRITICAL();
	while(*p != 0)
	{
		while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
		USART_SendData(USART1, (uint8_t) *p++);
	}
//	OS_EXIT_CRITICAL(); 
}

void print_n_byte(const int8_t *p,uint16_t len)
{
	while(len--)
	{
		while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
		USART_SendData(USART1, (uint8_t) *p++);
	}
}

void print_int(int32_t num)
{
	
	uint8_t flag=0;// first no-zero flag
	uint8_t i=0;
	uint8_t n[8]={"00000000"};
//	OS_ENTER_CRITICAL();

	if(num==0)// num is 0
	{
		print_byte('0');
		return;
	}
	if(num > INT32_MAX )
	{
		print_str((const int8_t *)"int overflow\r\n");
	}
	else if(num < 0)//negtive
	{
		num=-num;
	}
	
	for(i = 0;i < 7;i++)//-99999999--->99999999
	{		
		n[6-i]=num%10+'0';
		num/=10;
	}

	for(i = 0;i < 7;i++)
	{	
		if(!flag)
		{			
			if(n[i] == '0')
			{
				continue;
			}
			else
			{	
				flag=1;
				print_byte(n[i]);
			}
		}
		else
		{
			print_byte(n[i]);
		}
	}
//	OS_EXIT_CRITICAL(); 
}

 void print_float(float f)
{
	int32_t int_f = (int32_t)(f*1000);
	print_int(int_f);
	print_str((const int8_t*)".f3\r\n");
}

void print_arg(const int8_t *p,int32_t val)
{
//	OS_ENTER_CRITICAL();
	print_str(p);
	print_int(val);
	print_str((const int8_t*)"\r\n");
//	OS_EXIT_CRITICAL(); 
} 

