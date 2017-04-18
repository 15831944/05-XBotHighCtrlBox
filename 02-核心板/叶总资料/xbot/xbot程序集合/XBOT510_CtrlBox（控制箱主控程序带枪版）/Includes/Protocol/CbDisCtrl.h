

/*******************************************************Copyright*********************************************************
**                                            ����������ʢ�����˼������޹�˾
**                                                       �з���
**                                               http://www.uptech-eod.com
**
**-------------------------------------------------------�ļ���Ϣ---------------------------------------------------------
** �ļ�����:			CbDisCtrl.h
** ����޶�����:		2011-06-21
** ���汾:			1.0
** ����:				Ӧ�����ű�������
**
**------------------------------------------------------------------------------------------------------------------------
** ������:			����
** ��������:			2011-06-21
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


#ifndef CBDISCTRL_H_
#define CBDISCTRL_H_

#include "avr_compiler.h"
#include "ConfigTypes.h"

#include "Apps/UsartInit.h"



#include "Apps/SystemInit.h"

#include "Drivers/port_driver.h"
#include "Apps/AdcControl.h"
#include "Protocol/CbCtrlData.h"

#define		XBOT_CBDISCTRL_GLOBALS

#ifndef   XBOT_CBDISCTRL_GLOBALS
     #define XBOT_CBDISCTRL_EXT
#else
     #define XBOT_CBDISCTRL_EXT  extern
#endif


/*************************************************************************************************************************
**                                                    Э����ؿ�����
*************************************************************************************************************************/


#define CBDIS_TXD_START 			0xA5
#define CBDIS_RXD_START 			0xA5




#define CBDIS_TXD_LEN				13			// ͨѶ���ݷ��ͳ���
#define CBDIS_RXD_LEN				13			// ͨѶ���ݽ��ճ���


#define CBDIS_NEW_FRAME				0X01
#define CBDIS_NONE_FRAME			0X00

#define CBDIS_NC_DATA 				0xCC








/*************************************************************************************************************************
**                                                     �ṹ�嶨��
*************************************************************************************************************************/
typedef struct S_CbDisCtrlData
{
	uint8_t TxdDataBuf[CBDIS_TXD_LEN];
	uint8_t RxdDataBuf[CBDIS_RXD_LEN];

	uint8_t TxdCheckSum;
	uint8_t RxdCheckSum;
	uint8_t CheckSum;


}CBDIS_CTRL_DATA_STRUCT;							// Raptor�ӿ�������յ��Ŀ�����Ϣ





typedef struct S_CbDisCtrl
{
	void (*pSendDisCtrl)(USART_data_t * usart_data,CB_CTRL_DATA_STRUCT* pDa);
	void (*pDealRcData)(USART_data_t * p_usart_data,CBDIS_CTRL_DATA_STRUCT* pDa);



}CBDIS_CTRL_STRUCT;

XBOT_CBDISCTRL_EXT CBDIS_CTRL_STRUCT CbDisCtrl;
XBOT_CBDISCTRL_EXT CBDIS_CTRL_DATA_STRUCT CbDisCtrlData;



#endif /* CBDISCTRL_H */








