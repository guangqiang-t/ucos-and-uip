#ifndef os_app_H_
#define os_app_H_

#include "includes.h" 
#include "uip-conf.h"

//start task
#define Start_Task_PRIO          	1 
#define Start_STK_Size            64
extern OS_STK Start_Task_STK[Start_STK_Size];

//Eth process
#define Eth_Task_PRIO          	  15
#define Eth_STK_Size            	(1536)
extern OS_STK Eth_Task_STK[Eth_STK_Size];

// status led task
#define LED_Task_PRIO          		3 
#define LED_STK_Size            	64
extern  OS_STK LED_Task_STK[LED_STK_Size];

#define Sig_Pro_Task_PRIO          7 
#define Sig_Pro_STK_Size          512
extern  OS_STK Sig_Pro_Task_STK[Sig_Pro_STK_Size];


extern volatile OS_CPU_SR cpu_sr;

extern OS_EVENT *sig_msg_to_process;
extern OS_EVENT *sig_msg_process_complete;

//extern int8_t EthSendBuffer[UIP_CONF_BUFFER_SIZE];

extern void start_task(void *pdata);
extern void eth_task(void *pdata);
extern void status_led_task(void * pdata);
extern void sig_process_task(void *pdata);



#endif /*os_app_H*/
