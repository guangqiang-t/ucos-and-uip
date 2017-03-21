#include "os_app.h"
#include "uip_user_call.h"
#include "uip.h"
#include "get_arg.h"
#include "bsp_systick.h"

#ifdef DEBUG 
	#define APP_LOG(x) print_str(x)
#else
	#define APP_LOG(x) 
#endif

OS_STK Start_Task_STK[Start_STK_Size];
OS_STK LED_Task_STK[LED_STK_Size];
OS_STK Eth_Task_STK[Eth_STK_Size];

OS_EVENT *sig;
INT8U err=OS_ERR_NONE;

volatile OS_CPU_SR cpu_sr=0;
//int8_t EthSendBuffer[UIP_CONF_BUFFER_SIZE];
uint32_t cnt=0;

/******************************************************************************
* Function Name --> task start 
* Description   --> none
* Input         --> *pdata:
* Output        --> none
* Reaturn       --> none 
******************************************************************************/
void start_task(void * pdata)
{

	//printf("%d",OSIdleCtrMax);
	pdata = pdata;
	
	OS_ENTER_CRITICAL();
	systick_config();
	OS_EXIT_CRITICAL(); 
	
#if OS_TASK_STAT_EN > 0
	OSStatInit();//useage
#endif
		
	OS_ENTER_CRITICAL();
	OSTaskCreate(eth_task,  (void *)0, (OS_STK *)&Eth_Task_STK[Eth_STK_Size-1],Eth_Task_PRIO);
	OSTaskCreate(status_led_task, (void *)0, (OS_STK *)&LED_Task_STK[LED_STK_Size-1], LED_Task_PRIO);
	APP_LOG(("\r\n start task creat success \r\n"));

	OSTaskSuspend(Start_Task_PRIO);
	OS_EXIT_CRITICAL(); 
}

/******************************************************************************
* Function Name --> led0
* Description   --> none
* Input         --> *pdata: 
* Output        --> none
* Reaturn       --> none 
******************************************************************************/
void status_led_task(void * pdata)
{
	while(1)
	{
		led_on();
		delay_ms(200);
		led_off();
		delay_ms(4800);
	}
}


void eth_task(void *pdata)
{
	uint8_t i=0;
	#if 1
	while(1)
	{
		//user_tcp_appstate *StatePointer = (user_tcp_appstate *)&uip_conn->appstate;
		uip_polling();	
		if(g_tcp_server_state&(1<<6))
		{
			//send data
			strcpy((char *)tcp_sever_send_data_buff,"STM32Reply");
			sprintf((char *)&tcp_sever_send_data_buff[10],"%.3d",cnt++);
			sync_pwm(led_w,i);
			i+=1;
			if(i>50)i=0;
			g_tcp_server_state|=(1<<5);// To Send
			g_tcp_server_state&=~(1<<6);
//			printf("@-%d\r\n",OSCPUUsage);
		}
	}
	#endif
}





