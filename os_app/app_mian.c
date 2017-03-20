#include "os_app.h"
#include "uip_user_call.h"
#include "uip.h"
#include "get_arg.h"


#ifdef DEBUG 
	#define LOG(x) print_str(x)
#else
	#define LOG(x) 
#endif

OS_STK Start_Task_STK[Start_STK_Size];
OS_STK Eth_Task_STK[Eth_STK_Size];
OS_STK LED0_Task_STK[LED0_STK_Size];
OS_STK LED1_Task_STK[LED1_STK_Size];

OS_STK test_stk[256];
void test(void * pdata);

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
	SysTickConfig();
	OS_EXIT_CRITICAL(); 
	
#if OS_TASK_STAT_EN > 0
	OSStatInit();//useage
#endif
		
	OS_ENTER_CRITICAL();
	OSTaskCreate(Eth_task,  (void *)0, (OS_STK *)&Eth_Task_STK[Eth_STK_Size-1],Eth_Task_PRIO);
	OSTaskCreate(LED0_task, (void *)0, (OS_STK *)&LED0_Task_STK[LED0_STK_Size-1], LED0_Task_PRIO);
	OSTaskCreate(LED1_task, (void *)0, (OS_STK *)&LED1_Task_STK[LED1_STK_Size-1], LED1_Task_PRIO);
	OSTaskCreate(test, (void *)0, (OS_STK *)&test_stk[255], 7);
	LOG(("\r\n start task creat success \r\n"));

	OSTaskSuspend(Start_Task_PRIO);
	OS_EXIT_CRITICAL(); 
}


void Eth_task(void *pdata)
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

/******************************************************************************
* Function Name --> led0
* Description   --> none
* Input         --> *pdata: 
* Output        --> none
* Reaturn       --> none 
******************************************************************************/
void LED0_task(void * pdata)
{
	uint8_t ui8_cnt=0;
//	sig=OSSemCreate(0);
	while(1)
	{
		//g_tcp_server_state|=(1<<5);
		LEDON(3);
		DelayMs(50);
		LEDOFF(3);
		DelayMs(1000);
		ui8_cnt++;
//		if(ui8_cnt==10)
//		{
//			ui8_cnt=0;
//			OSSemPost(sig);
//			printf("post\r\n");
//		}
	}
}

/******************************************************************************
* Function Name --> led1
* Description   --> none
* Input         --> *pdata: 
* Output        --> none
* Reaturn       --> none 
******************************************************************************/
void LED1_task(void * pdata)
{
while(1)
	{
		LEDON(1);
		DelayMs(50);
		LEDOFF(1);
		DelayMs(2500);
		//OSSemPend(sig,0,&err);
//		printf("get %d msg from task0\r\n",ui8_cnt1);
	}
}


void test(void * pdata)
{
	while(1)
	{
		LEDON(2);
		DelayMs(50);
		LEDOFF(2);
		DelayMs(4200);
//		get_all_args((char *)tst,g_arg);
//		put_all_args();
	}
}

