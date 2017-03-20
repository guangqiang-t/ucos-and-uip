#include "stm32f10x.h" 
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "os_app.h"
#include "uip_user_call.h"
#include "bsp.h"
#include "get_arg.h"


//#ifdef DEBUG 
//	#define LOG(x) print_str(x)
//#else
//	#define LOG(x) 
//#endif

int main (void)
{
	
	USART1_Config();
	LEDInit();
//	SysTickConfig();
	NVIC_Config();
	pwm_config(1000);
//	sync_pwm(led_w,20);
	sync_pwm(led_r,4);
	tcp_server_init();
	
	
//	print_int(200);
	print_str("init ok\r\n");
	
	OSInit();
	OSTaskCreate(start_task, (void *)0, (OS_STK *)&Start_Task_STK[Start_STK_Size-1], Start_Task_PRIO);  //创建起始任务
	OSStart();  //ucos启动
	while(1)
	{
		print_str("error\r\n");
	}
	//return 0;
}

