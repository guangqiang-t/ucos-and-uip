#include "stm32f10x.h" 
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "os_app.h"
#include "uip_user_call.h"
#include "bsp.h"
#include "get_arg.h"

#ifdef DEBUG 
	#define MAIN_LOG(x) print_str(x)
#else
	#define MAIN_LOG(x) 
#endif

int main (void)
{
	uint8_t aa[8]={1,2,3,4,5,6,7,255};
	uint8_t *p=aa;

	usart1_config();
	led_init();
	NVIC_Config();
	logic_config();

	sw_config();
	pwm_config(100);
	sync_pwm(led_w,0);
	sync_pwm(motor,0);
	sync_pwm(led_g,0);
	sync_pwm(led_r,0);
	sync_pwm(led_b,0);
	
	_74hc595_send_n_char(p,3);
	tcp_server_init();

	MAIN_LOG("system init ok\r\n");
	
	OSInit();
	OSTaskCreate(start_task, (void *)0, (OS_STK *)&Start_Task_STK[Start_STK_Size-1], Start_Task_PRIO);  //创建起始任务
	OSStart();  //ucos启动
	while(1)
	{
		print_str("uC/OS is error!!!\r\n");
	}
	//return 0;
}

