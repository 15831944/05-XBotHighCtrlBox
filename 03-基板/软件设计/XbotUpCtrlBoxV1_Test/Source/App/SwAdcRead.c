
/**************************************************************************
˵�����ɼ���Դ���أ���Դ�������Ը�λ���ء�������Ҫ���һ��GPIO�������濪��״̬
���ߣ�������
���ڣ�20170417
��ע�����µ�һ�ο��������µڶ��ιػ���
	���������������ػ�

**************************************************************************/

#include "SwAdcRead.h"

#define BAT_ADC_BUF_LEN	 30

#define BAT_VALUE_MAX	255
#define BAT_VALUE_MIN	1
#define BAT_ADC_RANGE	0x400
#define BAT_VALUE_RANGE	255

uint8_t SW_GetValue(void)
{
	uint8_t SWAdcValue=0;

	SWAdcValue=SWGetAdc()*33>>12;   //�����������0.65V��Ҳ����6.5=6
	return SWAdcValue;
}

void SW_DealAdcValue(void)
{
	static uint8_t SW_PreValue=0xff;   //������һ��SW��ֵ
	static uint8_t SW_PressCount=0; //SW���¼���
	static uint8_t SW_PowerOffFlag=0;
	
	uint8_t SW_ValueTemp=SW_GetValue();
	
	if(SW_PreValue>SW_ValueTemp+2 || SW_PreValue<SW_ValueTemp-2) 
  //if(SW_PreValue != SW_ValueTemp) 
	{
		SW_PreValue=SW_ValueTemp;
		if(SW_PreValue>2)      //˵��SW����
		{
			SW_PressCount++;
			if(SW_PressCount>=2)  //�ڶ��ΰ���SW
			{
				SW_PowerOffFlag=1;
				//POWCTRL_OFF;        //�رյ�Դ���ػ�
				LED2_ON;
			}
			else if(SW_PressCount>=1)  //��һ�ΰ���SW
			{
				POWCTRL_ON;         //�򿪵�Դ������
			}
		}
		
	}
	
	// �����ػ�
	if(SW_ValueTemp>2 && SW_PowerOffFlag>0)
	{
			SW_PowerOffFlag++;
		if(SW_PowerOffFlag>10)
		{
			POWCTRL_OFF;        //�رյ�Դ���ػ�
		}
	}
	else
	{
		SW_PowerOffFlag=0;
	}
	
}





