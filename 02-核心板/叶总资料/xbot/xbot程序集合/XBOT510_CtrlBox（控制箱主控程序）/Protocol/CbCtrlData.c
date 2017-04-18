/*
 * CbCtrlData.c
 *
 *  Created on: 2011-6-21
 *      Author: wulin
 */

#include "Protocol/CbCtrlData.h"


CB_CTRL_DATA_STRUCT CbCtrlData =
{
		.RobotSelfPowerVal = 0X00,
		.TestMode = TEST_NC,
		.FireState= 0X00,


//				uint8_t TxdDataBuf[CB_TXD_LEN];
//				uint8_t RxdDataBuf[CB_RXD_LEN];
//
//				uint8_t TxdCheckSum;
//				uint8_t RxdCheckSum;
//
//				uint8_t DevID;					//�豸�˿ں�
//
//				uint8_t LeftMoveCtrl;			//��������
//				uint8_t RightMoveCtrl;			//�ҵ������
//				uint8_t LeftMoveSpeed;			//�����ٶ�
//				uint8_t RightMoveSpeed;			//�ҵ���ٶ�
//
//				uint8_t Arm12Ctrl;				//��е��12�ؽڿ���
//				uint8_t Arm34Ctrl;				//��е��34�ؽڿ���
//				uint8_t Arm50Ctrl;				//��е��50�ؽڿ���
//				uint8_t Arm78Ctrl;				//��е��78�ؽڿ���
//				uint8_t Arm6Ctrl;				//��е��6�ؽڿ���
//
//				uint8_t ExCtrl;					//���������ź�
//				uint8_t SwCtrl;					//�����������ź�
//				uint8_t CamZoomCtrl;			//ͼ�񼰽�������
//
//
//				uint8_t Arm12356Speed;			//��е��12356�ٶȿ���
//
//
//				uint8_t ComSwState;				//�������߿���
//
//				uint8_t FireState;				//����״̬
//
//				uint8_t Arm0Angle;				//������ת
//				uint8_t Arm1Angle;				//������ת
//				uint8_t Arm2Angle;				//��۸���
//				uint8_t Arm3Angle;				//С�۸���
//				uint8_t Arm4Angle;				//��ؽڸ���
//				uint8_t Arm5Angle;				//��צ��ת
//				uint8_t Arm6Angle;				//��̨����
//				uint8_t Arm7Angle;				//��̨��ת
//
//				uint8_t HandWidth;				//��צץ��
//				uint8_t CamPtAngle;				//ǰ������ͷ����
//
//				uint8_t Arm0ModeTime;			//�����˶�ʱ��
//				uint8_t Arm18ModeTime;			//��е���˶�ʱ��
//
//				uint8_t CtrlBoxPowerVal;		//�������ѹ
//				uint8_t RobotSelfPowerVal;		//���������ѹ
//
//				uint8_t Arm0WorkMode;			//���ȹ���ģʽ
//				uint8_t Arm18WorkMode;			//��е�۹���ģʽ
//				uint8_t YtWorkMode;				//��̨����ģʽ
//
		.KeyVal=0,					//СҺ�����İ���״̬
		.SendToXbotCounter=0,		//���͵�����������֡������
		.ReceiveFormXbotCounter=0,	//�����Ի���������֡������
		.SendToDisCounter=0,		//���͵�Һ��������֡������
		.ReceiveFormDisCounter=0,	//������Һ��������֡������
		.signal=0
};





















