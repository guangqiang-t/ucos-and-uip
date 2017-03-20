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

// led0 task
#define LED0_Task_PRIO          	13 
#define LED0_STK_Size            	128
extern  OS_STK LED0_Task_STK[LED0_STK_Size];

//led1 task
#define LED1_Task_PRIO          	11
#define LED1_STK_Size            	128
extern OS_STK LED1_Task_STK[LED1_STK_Size];

extern int8_t EthSendBuffer[UIP_CONF_BUFFER_SIZE];

void start_task(void *pdata);
void Eth_task(void *pdata);
void LED0_task(void *pdata);
void LED1_task(void *pdata);

#endif /*os_app_H*/
