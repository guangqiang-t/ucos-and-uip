#include "os_app.h"
#include "uip_user_call.h"
#include "uip.h"
#include "get_arg.h"
#include "bsp_systick.h"
#include "stdio.h" //sprintf
#include "stdlib.h"


#ifdef DEBUG 
	#define APP_LOG(x) print_str(x)
#else
	#define APP_LOG(x) 
#endif


#define RE_OK 		(0)
#define RE_ERROR1	(1)
#define RE_ERROR2	(2)
#define RE_ERROR3	(3)
#define RE_ERROR4	(4)


static void sig_process_status(uint8_t err_code);
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
//		_74hc595_config(1);
		led_on();
		delay_ms(200);
		led_off();
		delay_ms(1800);
	}
}


void eth_task(void *pdata)
{
	#if 1
	while(1)
	{
		//user_tcp_appstate *StatePointer = (user_tcp_appstate *)&uip_conn->appstate;
		uip_polling();	
		if(g_tcp_server_state&(1<<6))
		{
			print_str(tcp_sever_receive_data_buff);
			sig_process();
			//send data
			g_tcp_server_state|=(1<<5);// To Send
			g_tcp_server_state&=~(1<<6);
		}
	}
	#endif
}

void sig_process(void)
{
//	uint8_t i=0;
	#if 1
	
	if(memcmp(tcp_sever_receive_data_buff,"SYS:LED:",8)==0)
	{
		APP_LOG("cmd is LED\r\n");
		get_all_args(&tcp_sever_receive_data_buff[7],g_arg);
		put_all_args();
		print_arg("Led pwm is ",g_arg[0][0]);
		if(g_arg[0][0] >= 0&& g_arg[0][0] <= 100)
		{
			sync_pwm(led_w,g_arg[0][0]);
			memset(g_arg,0,(MAX_RAW*MAX_COLUMN));
			sig_process_status(RE_OK);
		}
		else
		{
			// Led pwm error
			sig_process_status(RE_ERROR1);
		}
	}
	
	else if(memcmp(tcp_sever_receive_data_buff,"SYS:MOTOR:",10)==0)
	{
		APP_LOG("cmd is MOTOR\r\n");
		get_all_args(&tcp_sever_receive_data_buff[9],g_arg);
//		put_all_args();
		print_arg("Motor pwm is ",g_arg[0][0]);
		if(g_arg[0][0] >= 0&& g_arg[0][0] <= 100)
		{
			sync_pwm(motor,g_arg[0][0]); 
			memset(g_arg,0,(MAX_RAW*MAX_COLUMN));
			sig_process_status(RE_OK);
		}
		else
		{
			//Motor pwm error
			sig_process_status(RE_ERROR1);
		}
	}
	
		else if(memcmp(tcp_sever_receive_data_buff,"SYS:COLOR:",10)==0)
	{
		APP_LOG("cmd is COLOR\r\n");
		get_all_args(&tcp_sever_receive_data_buff[9],g_arg);
//		put_all_args();
		print_arg("r pwm is ",g_arg[0][0]);print_arg("g pwm is ",g_arg[0][1]);print_arg("b pwm is ",g_arg[0][2]);
		if(g_arg[0][0] >= 0 && g_arg[0][0] <= 255 && g_arg[0][1] >= 0 && g_arg[0][1] <= 255 && g_arg[0][2] >= 0 && g_arg[0][2] <= 255)
		{
			sync_pwm(led_r,g_arg[0][0]/3); 
			sync_pwm(led_g,g_arg[0][1]/3);
			sync_pwm(led_b,g_arg[0][2]/3);
			
			
			memset(g_arg,0,(MAX_RAW*MAX_COLUMN));
			sig_process_status(RE_OK);
		}
		else
		{
			//Motor pwm error
			sig_process_status(RE_ERROR1);
		}
	}
	
	
	else if(memcmp(tcp_sever_receive_data_buff,"SYS:RELAY_HK:",12)==0)
	{
		APP_LOG("cmd is HK\r\n");
		get_all_args(&tcp_sever_receive_data_buff[1],g_arg);
//		put_all_args();
		print_arg("HK is ",g_arg[0][0]);
		if(g_arg[0][0]==1)
		{
			sync_sw(HK,NO); 
			memset(g_arg,0,(MAX_RAW*MAX_COLUMN));
			sig_process_status(RE_OK);
		}
		else if(g_arg[0][0]==0)
		{
			sync_sw(HK,NC);
			sig_process_status(RE_OK);
		}
		else
		{
//			HK value ERROR
			sig_process_status(RE_ERROR1);
		}
	}
	
	
		else if(memcmp(tcp_sever_receive_data_buff,"SYS:RELAY_LK:",12)==0)
	{
		APP_LOG("cmd is LK\r\n");
		get_all_args(&tcp_sever_receive_data_buff[11],g_arg);
//		put_all_args();
		print_arg("LK is ",g_arg[0][0]);
		if(g_arg[0][0]==1)
		{
			sync_sw(LK,NO); 
			memset(g_arg,0,(MAX_RAW*MAX_COLUMN));
			sig_process_status(RE_OK);
		}
		else if(g_arg[0][0]==0)
		{
			sync_sw(LK,NC);
			sig_process_status(RE_OK);
		}
		else
		{
//			HK value ERROR
			sig_process_status(RE_ERROR1);
		}
	}
	
	
	memset(tcp_sever_receive_data_buff,0,UIP_CONF_BUFFER_SIZE);
	#endif
}

void sig_process_status(uint8_t err_code)
{
	strcpy((char *)tcp_sever_send_data_buff,(char *)tcp_sever_receive_data_buff);
	switch(err_code)
	{
		case RE_OK:
		{
			strcat((char *)tcp_sever_send_data_buff,":OK");
			break;
		}
		case RE_ERROR1:
		{
			strcat((char *)tcp_sever_send_data_buff,":ERROR1!");
			break;
		}
		default :
		{
			strcat((char *)tcp_sever_send_data_buff,"ERROR2!");
			break;
		}
	}
	memset(tcp_sever_receive_data_buff,UIP_CONF_BUFFER_SIZE,0);
//	memset(tcp_sever_send_data_buff,UIP_CONF_BUFFER_SIZE,0);
	
}



