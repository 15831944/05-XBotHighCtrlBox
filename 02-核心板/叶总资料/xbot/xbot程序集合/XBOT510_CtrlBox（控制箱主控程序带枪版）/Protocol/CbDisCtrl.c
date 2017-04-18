/*
 * CbDisCtrl.c
 *
 *  Created on: 2011-6-21
 *      Author: wulin
 */




/*******************************************************Copyright*********************************************************
**                                            ����������ʢ�����˼������޹�˾
**                                                       �з���
**                                               http://www.uptech-eod.com
**
**-------------------------------------------------------�ļ���Ϣ---------------------------------------------------------
** �ļ�����:			CbDisCtrl.c
** ����޶�����:		2011-06-21
** ���汾:			1.0
** ����:				�������������߿��Ƶ�Э�������
**
**------------------------------------------------------------------------------------------------------------------------
** ������:			����
** ��������:			2011-06-21
** �汾:				1.0
** ����:				���������ڿ������Э�飬ͬʱ�����൱�Ŀ�����Ϣ��
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

#include "Protocol/CbDisCtrl.h"

inline static int8_t CbDisGetSpeed(uint8_t Dir,uint8_t Speed)
{
	int16_t TempSpeed;
	/**************���õ����*******************/
	if(Dir==0x01)
	{
		TempSpeed = Speed;
		TempSpeed /= 2;
	}
	else if(Dir==0x02)
	{
		TempSpeed = 0-Speed;
		TempSpeed /= 2;
	}
	else
	{
		TempSpeed = 0;
	}
	return TempSpeed;

}
static void XbotCbSendDisCtrl(USART_data_t * usart_data,CB_CTRL_DATA_STRUCT* pDa)
{
	uint8_t SendData[CBDIS_TXD_LEN];
	static uint8_t SendIndex=0x00;
	static uint8_t Index=0x00;

	SendIndex++;
	SendIndex = SendIndex&0x03;

	SendData[0] = CBDIS_TXD_START;					//����֡ͷ
	SendData[1] = SendIndex;						//�������ݷ��������֡��ش����

	SendData[2] = CbDisGetSpeed(pDa->LeftMoveCtrl,pDa->LeftMoveSpeed);  	//�ش������ٶ�
	SendData[3] = CbDisGetSpeed(pDa->RightMoveCtrl,pDa->RightMoveSpeed);	//�ش������ٶ�
	if(SendIndex==0x00)
	{
		SendData[4] =pDa->Arm1Angle;
		SendData[5] =pDa->Arm5Angle;
		SendData[6] =pDa->HandWidth;
		SendData[7] =  pDa->Battery_1;;				//���1��ѹ
		SendData[8] =  pDa->Error_1;				//����
		SendData[9] =  pDa->Error_2;				//����
		SendData[10] = pDa->Wirelength;	 			//�߳�
	}
	else if(SendIndex==0x01)
	{
		SendData[4] =pDa->Arm2Angle;
		SendData[5] =pDa->Arm6Angle;
		SendData[6] = pDa->Arm0Angle;;
		SendData[7] =  pDa->Battery_2;;				//���2��ѹ
		SendData[8] =  pDa->Error_3;				//����
		SendData[9] =  pDa->Error_4;				//����
		SendData[10] = pDa->signal;	 				//�ź�ǿ��
	}
	else if(SendIndex==0x02)
	{
		SendData[4] =pDa->Arm3Angle;
		SendData[5] =pDa->Arm7Angle;
		SendData[6] =  pDa->CtrlBoxPowerVal/2;		//�������ѹ
//		SendData[6] = (uint8_t)(adc_a_control.ad1&0x00ff);					//�ش���ʵ���ٶ�
		SendData[7] =  pDa->Battery_3; 				//���3��ѹ
		SendData[8] =  pDa->Error_5;				//����
		SendData[9] =  pDa->Error_6;				//����
		SendData[10] = pDa->LeftSpeed;				//�ش���ʵ���ٶ�

//		SendData[10]	= (uint8_t)(adc_a_control.ad1>>8);					//�ش���ʵ���ٶ�
	}
	else if(SendIndex==0x03)
	{
		SendData[4] =pDa->Arm4Angle;
		SendData[5] =pDa->CamPtAngle;
		SendData[6] =pDa->RobotSelfPowerVal;		//�����ѹ
//		SendData[6]	= (uint8_t)(adc_a_control.ad1>>8);					//�ش���ʵ���ٶ�
		SendData[7] =  pDa->Battery_4;; 			//���4��ѹ
		SendData[8] =  pDa->Error_7;				//����
		SendData[9] =  pDa->Error_8;				//����
		SendData[10] = pDa->RightSpeed;					//�ش���ʵ���ٶ�
//		SendData[10] = (uint8_t)(adc_a_control.ad1&0x00ff);					//�ش���ʵ���ٶ�
	}
	SendData[11] = pDa->FireState;					//����״̬

	SendData[CBDIS_TXD_LEN-1] = 0x00;
	for(Index=0;Index<CBDIS_TXD_LEN-1;Index++)
		SendData[CBDIS_TXD_LEN-1] += SendData[Index];


	for(Index=0;Index<CBDIS_TXD_LEN;Index++)
		while (!USART_TXBuffer_PutByte(usart_data,SendData[Index]));
}

inline static void CbDisSetCtrlData(CBDIS_CTRL_DATA_STRUCT* pDa,CB_CTRL_DATA_STRUCT* pCtrlData)
{
	if((pDa->RxdDataBuf[1]&0x80) != 0x00)
		return;

	if(((pDa->RxdDataBuf[1]>>4)&0x0F) == 0x00)
	{
		pCtrlData->Arm0WorkMode 	= (pDa->RxdDataBuf[2]>>5)&0X07;			//���ȹ���ģʽ
		pCtrlData->Arm18WorkMode 	= (pDa->RxdDataBuf[2]>>2)&0X07;;		//��е�۹���ģʽ
		pCtrlData->YtWorkMode 		= (pDa->RxdDataBuf[2]>>0)&0X03;;		//��̨����ģʽ

	}

	if(pDa->RxdDataBuf[3] == 0x8A)
		pCtrlData->TestMode = TEST_NO_LIMIT;
	else if(pDa->RxdDataBuf[3] == 0x8B)
		pCtrlData->TestMode = TEST_SET_ZERO;
	else if(pDa->RxdDataBuf[3] == 0xA8)
		pCtrlData->TestMode = TEST_FIRE;
	else if(pDa->RxdDataBuf[3] == 0xB8)
		pCtrlData->TestMode = TEST_GUN;
	pCtrlData->KeyVal=pDa->RxdDataBuf[4];									//СҺ�����İ���ֵ
	CbCtrlData.ReceiveFormDisCounter++;
}

static void XbotCbDealRxDisCtrl(USART_data_t * p_usart_data,CBDIS_CTRL_DATA_STRUCT* pDa)
{
	uint8_t TempData,TempCount;

	static uint8_t DataIndex = 0;

	while (USART_RXBufferData_Available(p_usart_data))
	{
		TempData = USART_RXBuffer_GetByte(p_usart_data);

		if (DataIndex == 0X00)
		{
			if(CBDIS_RXD_START != TempData)
			{
				DataIndex = 0;
			}
			else
			{
				pDa->RxdDataBuf[DataIndex] = TempData;
				DataIndex++;
			}
		}
		else if (DataIndex < CBDIS_RXD_LEN-1)
		{
			pDa->RxdDataBuf[DataIndex] = TempData;
			DataIndex++;
		}
		else if (DataIndex == CBDIS_RXD_LEN-1)
		{
			pDa->RxdDataBuf[DataIndex] = TempData;
			DataIndex++;

			/*******    ��У���       *******/
			pDa->CheckSum = 0;

			for(TempCount=0;TempCount<CBDIS_RXD_LEN-1;TempCount++)
			{
				pDa->CheckSum += pDa->RxdDataBuf[TempCount];
			}

			/******* ���У��Ͷԣ�����ָ�� *******/
			if(pDa->RxdDataBuf[CBDIS_RXD_LEN-1] == pDa->CheckSum )
			{

				/******* �ɹ������µ�һ֡���� *******/
				CbDisSetCtrlData(pDa,&CbCtrlData);

			}

			/******* ��λ�����¿�ʼ�µ�һ֡̽�� *******/
			DataIndex = 0;
		}
		else
		{
			DataIndex = 0;
		}
	}

	/***  û�гɹ������µ�һ֡���� ****/

}

CBDIS_CTRL_STRUCT CbDisCtrl =
{
		.pSendDisCtrl = XbotCbSendDisCtrl,
		.pDealRcData  = XbotCbDealRxDisCtrl,
};
CBDIS_CTRL_DATA_STRUCT CbDisCtrlData =
{


};














