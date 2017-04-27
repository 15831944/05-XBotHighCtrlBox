#include <stm32f10x_gpio.h>

#include"STM32_LedDisp.h"
#include "STM32_GpioInit.h"



void LedDisp_Init(void)
{


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	/********* LED1��ʼ�� ***********/
	#ifdef __LED1_PIN
		STM32_GpioOneInit(__LED1_PIN,GPIO_Speed_2MHz,GPIO_Mode_Out_PP,__LED1_PORT);	
	#endif
	
	/********* LED2��ʼ�� ***********/
	#ifdef __LED2_PIN	
		STM32_GpioOneInit(__LED2_PIN,GPIO_Speed_2MHz,GPIO_Mode_Out_PP,__LED2_PORT);
	#endif
	
	/********* LED3��ʼ�� ***********/
	#ifdef __LED3_PIN	
		STM32_GpioOneInit(__LED3_PIN,GPIO_Speed_2MHz,GPIO_Mode_Out_PP,__LED3_PORT);
	#endif
	
	/********* LED4��ʼ�� ***********/
	#ifdef __LED4_PIN
		STM32_GpioOneInit(__LED4_PIN,GPIO_Speed_2MHz,GPIO_Mode_Out_PP,__LED4_PORT);	
	#endif
	
	/********* LED5��ʼ�� ***********/
	#ifdef __LED5_PIN
		STM32_GpioOneInit(__LED5_PIN,GPIO_Speed_2MHz,GPIO_Mode_Out_PP,__LED5_PORT);		
	#endif


}




