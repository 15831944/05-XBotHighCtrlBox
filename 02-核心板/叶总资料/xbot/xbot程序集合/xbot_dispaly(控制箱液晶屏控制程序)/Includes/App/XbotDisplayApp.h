/**
  ******************************************************************************
	*�ļ���XbotApp.h
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������Xbot�������ͷ�ļ�
	*��ע�����Ա���кܶྲ̬��Ա������Ϊ���ǻص�����ʹ�ã�����б�Ҫ�Ļ��������޸ĵ��÷�ʽ��Ϊ��ͨ�ĳ�Ա
	*
  ******************************************************************************  
	*/ 
	
/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _XBOT_DISPLAY_APP_H
#define _XBOT_DISPLAY_APP_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "SerialPort.h"
#include "LCDdisplay.h"
#include "TerminalControl.h"
#include "Timer.h"
#include "LEDLighter.h"
#include "Key.h"
#include "STM32_SysTick.h"

/* ���Ͷ��� --------------------------------------------------------------------*/

/* �궨��-----------------------------------------------------------------------*/ 


class XbotDisplayApp
{
public:
	XbotDisplayApp();
	~XbotDisplayApp();
	void runOnTime2();												//�����ڶ�ʱ��TIM2�еĺ���
	void runOnTime3();												//�����ڶ�ʱ��TIM3�еĺ���
	void runOnTime4();												//�����ڶ�ʱ��TIM4�еĺ���
	void initLCD();

private:
	LCDdisplay *LCDManager;										//����Һ����
	TerminalControl *terminalManager; 				//��XBOT�����佻��
	SerialPort *terminalPort;									//���նˣ�XBOT�����䣩ͨ�ŵĴ���
	SerialPort *lcdPort;											//��LCDҺ����ͨ�ŵĴ���
	Timer *t1;																//��ʱ��1
	Timer *t2;																//��ʱ��2
	Timer *t3;															//��ʱ��3
	LEDLighter *led_1;
	LEDLighter *led_2;
	Key *key_M;
	Key *key_A;
	Key *key_B;
	Key *key_C;
	Key *key_D;
	int8_t keysValue;													//������ֵ
	uint8_t maskKeysValue;										//���͵��ն˵İ���ֵ
	uint8_t workMode;													//����ģʽ
	uint8_t debugMode;												//����ģʽ
	int8_t interfaceIndex;										//������
	uint8_t *error;														//�������
	uint8_t errorStatus;											//����״̬
	uint8_t pageID;														//����ͼƬ��ID
	uint8_t languagePosition;									//���Ե�ͼƬƫ��λ�� 
	bool enabledShowError;										//��Ϣ������ʾ���ı�־
private:
	bool updateLCDdata();
	uint8_t checkError();											//��������Ϣ
	void disOneError(uint8_t,uint8_t,uint8_t);//��ʾ�������Ϣ
	void disErrorIcon();											//��ʾ����ͼ��
	bool disError(bool);											//��ʾ������Ϣ

	void setWorkMode(uint8_t);

	void setMainButtonPress(uint8_t button);	//���������水������
	void setMainButtonNormal(uint8_t button);	//���������水������������״̬��
	void setButtonPress(uint8_t button);			//������ͨ���水������
	void setButtonChecked(uint8_t button);		//������ͨ���水��ѡ��
	void setButtonNormal(uint8_t button);			//������ͨ���水������������״̬��
	void disSwingArmWorkMode(bool);						//���ðڱ�ģʽ��ͼƬ
	void disArmWorkMode(bool);								//�����ֱ�ģʽ��ͼƬ
	void disOtherWorkMode(bool);							//��������ģʽ��ͼƬ

	void disPageStart();											//��ʾ��������
	void disPageMain(int8_t,int8_t,bool);			//��ʾ���˵�����
  void disPageAngle(int8_t,int8_t,bool);		//��ʾ�ǶȽ���
	void disPageSwingArmCtrl(int8_t,int8_t);	//��ʾ�ڱۿ��ƽ���
	void disPageArmCtrl(int8_t,int8_t);				//��ʾ�ֱۿ��ƽ���
	void disPageOtherCtrl(int8_t,int8_t);			//��ʾ�������ƽ���
	void disPageDubugCtrl(int8_t,int8_t);			//��ʾӦ�����ƽ���
	bool disPageWeaponCtrl();									//��ʾ�������ƽ���
// 	void disPageWarning();										//��ʾ��Ϣ�������

};
#endif /* _XBOT_APP_H */









