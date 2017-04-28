#ifndef __KEY_READ_H
#define __KEY_READ_H	
#include "stm32f10x.h"

#define KEYNUM	40
#define	KEY_MAX_TIMER	10

//******************* Aϵ�п���*************************
#define __KEY_A1_PIN		GPIO_Pin_9			//����A1
#define __KEY_A2_PIN		GPIO_Pin_8			//����A2
#define __KEY_A3_PIN		GPIO_Pin_7 	    	//����A3
#define __KEY_A4_PIN		GPIO_Pin_6		  	//����A4
#define __KEY_A5_PIN		GPIO_Pin_5		   	//����A5
#define __KEY_A6_PIN 		GPIO_Pin_7		  	//����A6
#define __KEY_A7_PIN 		GPIO_Pin_4		  	//����A7
#define __KEY_A8_PIN 		GPIO_Pin_3		  	//����A8

//******************* Bϵ�п���*************************
#define __KEY_B1_PIN		GPIO_Pin_10			//����B1
#define __KEY_B2_PIN		GPIO_Pin_11			//����B2
#define __KEY_B3_PIN		GPIO_Pin_12 		//����B3
#define __KEY_B4_PIN		GPIO_Pin_13		  	//����B4
#define __KEY_B5_PIN		GPIO_Pin_14		   	//����B5
#define __KEY_B6_PIN 		GPIO_Pin_15		  	//����B6
#define __KEY_B7_PIN 		GPIO_Pin_10		  	//����B7
#define __KEY_B8_PIN 		GPIO_Pin_11		  	//����B8

//******************* Eϵ�п���*************************
#define __KEY_EU_PIN		GPIO_Pin_1			//����A1
#define __KEY_ED_PIN		GPIO_Pin_14			//����A2
#define __KEY_EL_PIN		GPIO_Pin_13 	    	//����A3
#define __KEY_ER_PIN		GPIO_Pin_0		  	//����A4
#define __KEY_EM_PIN		GPIO_Pin_15		   	//����A5

//******************* Fϵ�п���*************************
#define __KEY_FU_PIN		GPIO_Pin_4			//����A1
#define __KEY_FD_PIN		GPIO_Pin_4			//����A2
#define __KEY_FL_PIN		GPIO_Pin_7 	    	//����A3
#define __KEY_FR_PIN		GPIO_Pin_5		  	//����A4
#define __KEY_FM_PIN		GPIO_Pin_6		   	//����A5

//******************* Hϵ�п���*************************
#define __KEY_H1_PIN		GPIO_Pin_5			//����A1
#define __KEY_H2_PIN		GPIO_Pin_0			//����A2
#define __KEY_H3_PIN		GPIO_Pin_1 		    //����A3
#define __KEY_H4_PIN		GPIO_Pin_7		  	//����A4
#define __KEY_H5_PIN		GPIO_Pin_8		   	//����A5

//******************* IJϵ�п���*************************
#define __KEY_I1_PIN 		GPIO_Pin_3		  	//����A6
#define __KEY_I2_PIN 		GPIO_Pin_4		  	//����A7
#define __KEY_J1_PIN 		GPIO_Pin_5		  	//����A8
#define __KEY_J2_PIN		GPIO_Pin_6			//����A1

//******************* Mϵ�п���*************************
#define __KEY_M2_PIN		GPIO_Pin_0			//����M2
#define __KEY_M3_PIN		GPIO_Pin_1 		    //����M3
#define __KEY_M4_PIN		GPIO_Pin_2		  	//����M4

//******************* Gϵ�п���*************************
#define __KEY_G1_PIN		GPIO_Pin_6		   	//����G1
#define __KEY_G2_PIN 		GPIO_Pin_7		  	//����G2



//*****************************************�˿ں�����**********************************//

//******************* Aϵ�п���*************************
#define __KEY_A1_PORT		GPIOB			//����A1
#define __KEY_A2_PORT		GPIOB			//����A2
#define __KEY_A3_PORT		GPIOB 			//����A3
#define __KEY_A4_PORT		GPIOB		  	//����A4
#define __KEY_A5_PORT		GPIOB		   	//����A5
#define __KEY_A6_PORT 		GPIOD		  	//����A6
#define __KEY_A7_PORT 		GPIOD		  	//����A7
#define __KEY_A8_PORT 		GPIOD		  	//����A8

//******************* Bϵ�п���*************************
#define __KEY_B1_PORT		GPIOE			//����B1
#define __KEY_B2_PORT		GPIOE			//����B2
#define __KEY_B3_PORT		GPIOE 			//����B3
#define __KEY_B4_PORT		GPIOE		  	//����B4
#define __KEY_B5_PORT		GPIOE		   	//����B5
#define __KEY_B6_PORT 		GPIOE		  	//����B6
#define __KEY_B7_PORT 		GPIOB		  	//����B7
#define __KEY_B8_PORT 		GPIOB		  	//����B8

//******************* Eϵ�п���*************************
#define __KEY_EU_PORT		GPIOD			//����A1
#define __KEY_ED_PORT		GPIOD			//����A2
#define __KEY_EL_PORT		GPIOD 			//����A3
#define __KEY_ER_PORT		GPIOD		  	//����A4
#define __KEY_EM_PORT		GPIOD		   	//����A5

//******************* Fϵ�п���*************************
#define __KEY_FU_PORT		GPIOA			//����A1
#define __KEY_FD_PORT		GPIOC			//����A2
#define __KEY_FL_PORT		GPIOA 			//����A3
#define __KEY_FR_PORT		GPIOA		  	//����A4
#define __KEY_FM_PORT		GPIOA		   	//����A5

//******************* Hϵ�п���*************************
#define __KEY_H1_PORT		GPIOC			//����A1
#define __KEY_H2_PORT		GPIOB			//����A2
#define __KEY_H3_PORT		GPIOB 			//����A3
#define __KEY_H4_PORT		GPIOE		  	//����A4
#define __KEY_H5_PORT		GPIOE		   	//����A5

//******************* IJϵ�п���*************************
#define __KEY_I1_PORT 		GPIOE		  	//����A6
#define __KEY_I2_PORT 		GPIOE		  	//����A7
#define __KEY_J1_PORT 		GPIOE		  	//����A8
#define __KEY_J2_PORT		GPIOE			//����A1

//******************* Mϵ�п���*************************
#define __KEY_M2_PORT		GPIOE			//����M2
#define __KEY_M3_PORT		GPIOE 			//����M3
#define __KEY_M4_PORT		GPIOE		  	//����M4

//******************* Gϵ�п���*************************
#define __KEY_G1_PORT		GPIOC		   	//����G1
#define __KEY_G2_PORT 		GPIOC		  	//����G2

#define KEY_PRESS_NULL	0X00
#define KEY_PRESS_DOWN	0X01
#define KEY_RRESS_UP	0X02
#define KEY_SELECT	  	0X03
#define KEY_UNSELECT	0X04


typedef struct S_KEYDATA_STRUCT
{
	uint16_t KEY_Pin;
	GPIO_TypeDef* KEY_PORT;
	uint8_t TimerTick;
	uint8_t PreState;		//��ʾǰһʱ�̰���״̬,Ĭ�������û�а�������
	uint8_t NowState;		//����һ���м�������𵽴��ε�����
	uint8_t TimerTickMax;

}KEYDATA_STRUCT;


#define	KEY_A1	0
#define	KEY_A2	1
#define	KEY_A3	2
#define	KEY_A4	3
#define	KEY_A5	4
#define	KEY_A6	5
#define	KEY_A7	6
#define	KEY_A8	7

#define	KEY_B1	8
#define	KEY_B2	9
#define	KEY_B3	10
#define	KEY_B4	11
#define	KEY_B5	12
#define	KEY_B6	13
#define	KEY_B7	14
#define	KEY_B8	15

#define	KEY_H1	16
#define	KEY_H2	17
#define	KEY_H3	18
#define	KEY_H4	19
#define	KEY_H5	20

#define	KEY_I1	21
#define	KEY_I2	22
#define	KEY_J1	23
#define	KEY_J2	24
#define	KEY_M2	25
#define	KEY_M3	26
#define	KEY_M4	27
#define	KEY_G1	28
#define	KEY_G2	29

#define	KEY_EU	30
#define	KEY_ED	31
#define	KEY_EL	32
#define	KEY_ER	33
#define	KEY_EM	34

#define	KEY_FU	35
#define	KEY_FD	36
#define	KEY_FL	37
#define	KEY_FR	38
#define	KEY_FM	39

extern KEYDATA_STRUCT KEY_DATA[KEYNUM];


extern void KeyRead_Init(void);
extern void KeyAll_OpTask(void);

	  
#endif

