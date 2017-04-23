#include "bsp_temp.h"
#include "bsp_usart.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)

volatile uint16_t g_adc_value[4];
uint16_t g_temp=0;

static int16_t get_adc_value(void);

void internal_temp_config(void)
{
#if 1
	
	
	//DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
//  DMA_DeInit(DMA1_Channel1);
//  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
//  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) (&g_adc_value);
//  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//  DMA_InitStructure.DMA_BufferSize = 4;
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
// 
//  DMA_Cmd(DMA1_Channel1, ENABLE);

	ADC_DeInit(ADC1);
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
 
  ADC_Cmd(ADC1, ENABLE);
 
  ADC_ResetCalibration(ADC1);
  while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));
 
 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_55Cycles5);
 
  ADC_TempSensorVrefintCmd(ENABLE);
 
//  ADC_DMACmd(ADC1, ENABLE);
 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//	print_str("adc init ok\r\n");
#else
	
#endif
}

int16_t get_adc_value(void)
{
	int16_t adc_value;
  ADC_RegularChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_55Cycles5);
  ADC_SoftwareStartConvCmd(ADC1,ENABLE);
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
  adc_value=ADC_GetConversionValue(ADC1);
  return adc_value;
}

int16_t get_temp(void)
{
	uint8_t i=0;
	int16_t avr,temp=0;
	#if 0
	avr=(g_adc_value[0]+g_adc_value[1]+g_adc_value[2]+g_adc_value[3])/4;
	temp=(int16_t)(100*(19+(1700-avr)/4.5));
	return temp;
	
	#else
	for(i=0;i<4;i++)
	{
		g_adc_value[i]=get_adc_value();
	}
	avr=(g_adc_value[0]+g_adc_value[1]+g_adc_value[2]+g_adc_value[3])/4;
	temp=(int16_t)(100*(19+(1700-avr)/4.5));
	return temp;
	#endif
}

