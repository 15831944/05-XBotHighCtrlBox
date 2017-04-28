
/*******************************************************Copyright*********************************************************

**
**-------------------------------------------------------�ļ���Ϣ---------------------------------------------------------
** �ļ�����:			CbCtrl.c
** ����޶�����:		2012-06-02
** ���汾:			1.0
** ����:				�ɼ�����IO��Ϣ�����͸�OMAP��
**
**------------------------------------------------------------------------------------------------------------------------
** ������:				����
** ��������:			2012-06-02
** �汾:				1.0
** ����:				20120601_XBOT510�߶˿��ƺ�ͨѶЭ��
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


#ifndef __CBCTRL_H	 
#define __CBCTRL_H

#include "stm32f10x.h"
#include "MySysdefine.h"
#include "KeyRead.h"
#include"STM32_LedDisp.h"
#include "JoyStickAdcRead.h"
#include "BatteryAdcRead.h"
#include "STM32_UsartDriver.h"
#include "STM32_UsartInit.h"

#define		__CBCTRL_GLOBALS

#ifndef   __CBCTRL_GLOBALS
     #define CBCTRL__EXT
#else
     #define CBCTRL__EXT  extern
#endif



#define OMAP_TXD_DATA_LEN	15
#define OMAP_RXD_DATA_LEN	15

#define XBOT_TXD_DATA_LEN	13
#define XBOT_RXD_DATA_LEN	13

#define OMAP_RXD_START	0xA5
#define OMAP_TXD_START	0xA5
#define OMAP_NC_DATA	0x66

#define XBOT_RXD_START	0xA5
#define XBOT_TXD_START	0xA5


#define CB_COM_KEY_CTRL		0X30
#define CB_COM_XBOT_CTRL	0X10

CBCTRL__EXT uint8_t OMAP_TXD_DATA[OMAP_TXD_DATA_LEN];
CBCTRL__EXT uint8_t OMAP_RXD_DATA[OMAP_RXD_DATA_LEN];

CBCTRL__EXT uint8_t XBOT_TXD_DATA[XBOT_TXD_DATA_LEN];
CBCTRL__EXT uint8_t XBOT_RXD_DATA[XBOT_RXD_DATA_LEN];

CBCTRL__EXT void CbDealRxdCtrl(void);
CBCTRL__EXT void CbCtrlInit(void);
CBCTRL__EXT void CbDealTxdCtrl(USART_data_t* p_usart_data,uint8_t* pTXD_DATA);
CBCTRL__EXT bool CbCtrlDealRcData(USART_data_t* p_usart_data, uint8_t* pRXD_DATA);


						


#endif











