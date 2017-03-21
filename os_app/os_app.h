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
#define Eth_STK_Size            	(1024*2)
extern OS_STK Eth_Task_STK[Eth_STK_Size];

// status led task
#define LED_Task_PRIO          		3 
#define LED_STK_Size            	64
extern  OS_STK LED_Task_STK[LED_STK_Size];


extern int8_t EthSendBuffer[UIP_CONF_BUFFER_SIZE];

void start_task(void *pdata);
void eth_task(void *pdata);
void status_led_task(void * pdata);

#endif /*os_app_H*/
