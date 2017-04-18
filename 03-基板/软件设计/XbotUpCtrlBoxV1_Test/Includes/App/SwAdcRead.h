/*********************************************************************
˵�����ɼ���Դ���أ���Դ�������Ը�λ���ء�������Ҫ���һ��GPIO�������濪��״̬
���ߣ�������
���ڣ�20170417
��ע�����µ�һ�ο��������µڶ��ιػ���Ŀǰû����ӳ������������ܻ�����󴥵����

**********************************************************************/

#ifndef __SW_ADC_READ_H
#define __SW_ADC_READ_H	
#include "stm32f10x.h"
#include "STM32_Adc.h"

#include "STM32_GpioInit.h"  
#include "STM32_LedDisp.h"

#define SW_ADC		0X06


#define  SWGetAdc()	GetAdcAverageValue(ADC1ConvertedValue,SW_ADC,STM32_ADC_CACHEL_M)


extern uint8_t SW_GetValue(void);
extern void SW_DealAdcValue(void);  //����SWAdc����ֵ

#endif
