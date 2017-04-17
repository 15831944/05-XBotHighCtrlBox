

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "MySysDefine.h"
#include "STM32_IRQ_INIT.H"
#include "STM32_SysTick.h"
#include "STM32_UsartInit.h"
#include "STM32_UsartDriver.h"
#include "STM32_TimInit.h"
#include "STM32_ADC.h"
#include "KeyRead.h"
#include "JoyStickAdcRead.h"
#include "STM32_GpioInit.h"
//#include "CbCtrl.h"


	    


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{

	SystemInit(); 		//ϵͳʱ�ӳ�ʼ��
	
	//CbCtrlInit();
	
		 
	/* System Clocks Configuration */
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(STM32_NVIC_PriorityGroup);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	

	LedDisp_Init();		//��ʾLED��ʼ��
	KeyRead_Init();		//������ʼ��
	SysTick_Init();		//1msϵͳʱ�ӳ�ʼ��
	Adc1Dma_Init();		//adc ��ʼ��
	JoyStickAdcReadInit();	//ҡ�˳�ʼ��,����ڷ���λ״̬�ᱣ��
	STM32_GpioInit();

	STM32_Tim2Init();	//����TIM2,��Ϊϵͳ��������1ms
	STM32_Tim3Init();	//����TIM2,��Ϊϵͳ��������10ms
	STM32_Tim4Init();	//����TIM2,��Ϊϵͳ��������100ms

	STM32_InitUsart1(19200);
	STM32_InitUsart2(19200);
	STM32_InitUsart3(19200);
	STM32_InitUsart4(19200);

	LED1_ON;
	LED2_OFF;
//	POWCTRL_ON;

	SysTick_Delay(100);
	STM32_ENABLE_TIM2;
	STM32_ENABLE_TIM3
	STM32_ENABLE_TIM4;
	while (1)     
	{
//		while (!USART_TXBuffer_PutByte(&USART_data_2,0X55));
	
	}
}




#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
