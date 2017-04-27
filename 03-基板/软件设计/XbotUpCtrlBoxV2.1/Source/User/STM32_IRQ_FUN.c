#include "stm32f10x.h"
#include "STM32_IRQ_INIT.H"
#include "STM32_TimInit.h"
#include "MySysDefine.h"
#include "CbCtrl.h"
#include "STM32_UsartInit.h"
#include "BatteryAdcRead.h"
#include "SwAdcRead.h"

///******************************************************************************/
///*            STM32F10x Peripherals Interrupt Handlers                        */
///******************************************************************************/
//


//1ms ����һ��
/******************************  TIM2_IRQHandler *************************************/
void TIM2_IRQHandler(void)
{

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	
	{
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
		STM32_DISABLE_TIM2;
		CbDealRxdCtrl();
		STM32_ENABLE_TIM2		
	}
 
}

//10ms����һ��
/******************************  TIM3_IRQHandler *************************************/
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	
	{
		TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);

		STM32_DISABLE_TIM3;
		KeyAll_OpTask();
		
		STM32_ENABLE_TIM3;
	}
 
}

//100ms����һ��
/******************************  TIM4_IRQHandler *************************************/
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	
	{
		TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);

		STM32_DISABLE_TIM4;
		CbDealTxdCtrl(&USART_OMAP_CTRL,OMAP_TXD_DATA);	
		BAT1_GetValue();
		
		SW_DealAdcValue();  //��ȡ������ SW����ֵ
		STM32_ENABLE_TIM4;
		
	}
}

