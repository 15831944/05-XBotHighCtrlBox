
/*******************************************************Copyright*********************************************************
**                                            ����������ʢ�����˼������޹�˾
**                                                       �з���
**                                               http://www.uptech-eod.com
**
**-------------------------------------------------------�ļ���Ϣ---------------------------------------------------------
** �ļ�����:			CbIoCtrl.h
** ����޶�����:		2010-05-01
** ���汾:			1.0
** ����:				Ӧ�����ű�������
**
**------------------------------------------------------------------------------------------------------------------------
** ������:			����
** ��������:			2009-04-01
** �汾:				1.0
** ����:				Ӧ�����ű������ˣ�
**
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
*************************************************************************************************************************/


#ifndef CBIOCTRL_H_
#define CBIOCTRL_H_

#include "avr_compiler.h"
#include "ConfigTypes.h"

#include "Apps/UsartInit.h"



#include "Apps/SystemInit.h"

#include "Drivers/port_driver.h"
#include "Apps/AdcControl.h"
#include "Protocol/CbDisCtrl.h"
#include "Protocol/CbCtrlData.h"

#define		RAPTOR_CBIOCTRL_GLOBALS

#ifndef   RAPTOR_CBIOCTRL_GLOBALS
     #define RAPTOR_CBIOCTRL_EXT
#else
     #define RAPTOR_CBIOCTRL_EXT  extern
#endif


#define CBIOCTRL_TXD_EN		PORTD.OUTSET  = PIN1_bm
#define CBIOCTRL_TXD_DIS	PORTD.OUTCLR  = PIN1_bm












typedef struct S_CbCtrl
{
	uint8 CtrlState;

	void (*p_InitDev) (void);
	void (*p_DealCtrl) (void);

	uint8_t (*pRxdPacket)(USART_data_t* p_usart_data, CB_CTRL_DATA_STRUCT* p_Rp_receive);
	uint8_t (*pTxdToRpCtrl)(USART_data_t* p_usart_data, CB_CTRL_DATA_STRUCT* p_Rp_send);

	uint8_t (*pTxdToRpFire)(USART_data_t* p_usart_data, CB_CTRL_DATA_STRUCT* p_Rp_send);

	void (*pDearRcData)(USART_data_t* p_usart_data, CB_CTRL_DATA_STRUCT* p_Xbot_receive);



}CB_CTRL_STRUCT;

RAPTOR_CBIOCTRL_EXT CB_CTRL_STRUCT CbCtrl;




#endif /* CBIOCTRL_H_ */



/******************************���п��ƽӿڶ���**************************/

/*************** IO ����ӿ�**************/
/****************************************
PC0  	IN_Aim   		��׼����
PC1		IN_Aim_Lock		����Կ��
PC4		IN_Fire			�������
PC5		IN_COM_SW		���������л����

PD0		OUT_COM_CTRL	���������л�����
PD5		IN_CAM0			ͼ��ͨ����������0
PD6		IN_CAM1			ͼ��ͨ����������1
PD7		IN_CAM2			ͼ��ͨ����������2

PE0		OUT_CAM0		ͼ��ͨ��LED�������0
PE1		OUT_CAM1		ͼ��ͨ��LED�������1
PE2		OUT_CAM2		ͼ��ͨ��LED�������2
PE3		IN_HD_LIGHT		��̨�ƹ����
PE4		IN_MV_LIGHT		��ʹ�ƹ����
PE5		IN_HANDA		��צץ��
PE6		IN_HANDB		��צ�ɿ�
PE7		IN_HAND_AUTO	��צ�Զ�

PF0		IN_JOINT1_A		������ת
PF1		IN_JOINT1_B		������ת
PF2		IN_JOINT2_A		����¸�
PF3		IN_JOINT2_B		�������
PF4		IN_JOINT3_A		С������
PF5		IN_JOINT3_B		С���¸�
PF6		IN_JOINT4_A		��צ��ת
PF7		IN_JOINT4_B		��צ��ת

**********	ADC-A	ͨ�� 	**********
ADC0	ARM_SPEED		��е���˶��ٶ�
ADC1	HAND_FORCE		��צץ������
ADC2	REVERVATION		����
ADC3	Voltage			ϵͳ������ѹ
ADC4	HEADX			��̨��ת����
ADC5	HEADY			��̨��������
ADC6	HEAD_FOCUS		��̨�佹����
ADC7	MOVE_X			�˶����ҿ���


**********	ADC-B	ͨ�� 	**********
ADC0	MOVE_Y			�˶�ǰ�����
ADC1	MOVE_Z			����
ADC2	MOVE_SPEED		�˶��ٶȿ���


********************************************/






