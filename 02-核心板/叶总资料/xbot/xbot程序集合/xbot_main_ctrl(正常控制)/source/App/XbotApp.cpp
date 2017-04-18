/**
  ******************************************************************************
	*�ļ���XbotApp.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������Xbot�������ʵ���ļ�
	*��ע��
	*
  ******************************************************************************  
	*/ 


/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "XbotApp.h"
#include <stdlib.h>
#include "STM32F4_SysTick.h"
#include <math.h>
/* ���Ͷ��� --------------------------------------------------------------------*/

/* �궨��-----------------------------------------------------------------------*/ 

//����ֵ��
#define ABS(X)			((X)>0?(X):(-(X)))
//���߾���ֵ˭��˭С��
#define MAX(X,Y)		((ABS(X))>(ABS(Y))?(ABS(X)):(ABS(Y)))
#define MIN(X,Y)		((ABS(X))<(ABS(Y))?(ABS(X)):(ABS(Y)))

#define SEND_CHECK_TIME_MAX 		10
#define CHECK_TIME_MAX 					(SEND_CHECK_TIME_MAX+1)
#define CHECK_DRIVER_NUM 				13
#define TERMINAL_FRAME_LEN    	13

//��ַ��
#define 	LEFTRUN_DDR						0x00
#define 	RIGHTRUN_DDR					0x01
#define 	SUPPORT_ARM_DDR				0x02
#define 	POWER_DDR							0x03
	
#define 	BIG_ARM_ROTATE_DDR		0x00
#define 	BIG_ARM_PITCH_ADDR		0x01
#define 	FORE_ARM_PITCH_DDR		0x02
#define 	WRIST_PITCH_DDR				0x03
#define 	WRIST_ROTATE_DDR			0x04
#define 	PAN_TILT_PITCH_DDR  	0x05
#define 	PAN_TILT_ROTATE_DDR 	0x06
#define 	FINGER_MEDIATE_DDR 		0x07
#define 	CAMERA_PITCH_DDR 			0x08
#define 	OTHER_DEVICE_DDR 			0x09

//�������ú� 
#define		WIRE_LESS_PORT_NUM		6
#define		WIRE_PORT_NUM					4
#define		CODED_DISC_PORT_NUM		5
#define		ARM_PORT_NUM					1
#define		UNDERPAN_PORT_NUM			2
#define		GPS_PORT_NUM					3

#define		WIRE_LESS_PORT_BAUD		19200
#define		WIRE_PORT_BAUD				19200
#define		CODED_DISC_PORT_BAUD	115200
#define		ARM_PORT_BAUD					38400
#define		UNDERPAN_PORT_BAUD		38400
#define		GPS_PORT_BAUD					38400

//��������������������
#define NEW_DRIVER_PROGRAM

//�°�XBOT511��������
#define NEWXBOT

//��ʽ��������������
#define NEWOPTICALBOBBIN  

//ʹ�õ�λ�� ��������
#define USEPOTENTIOMETER

//����������¶�����
#define WARNINGTEMPERATURE 90

//�ǶȲ�ѯָ��ID
#define ANGLE_INQUIRE_ID				0X08
//ȡ����λָ��ID
#define ANGLE_FREE_ID						0X02
//����Ƕ���λָ��ID
#define ANGLE_REINIT_ID					0X06
//����Ƕ�ָ��ID
#define ANGLE_SAVE_ID						0X07
//�ٶȲ�ѯָ��ID
#define SPEED_INQUIRE_ID				0X09
//�ٶ�ʹ��ָ��
#define ENASPEED_ID							0X0C

#define FB_OK_1 					0X4F
#define FB_OK_2 					0X4B
#define FB_SAVE_ID 				0x67
#define FB_REINIT_ID 			0x66
#define FB_FREE_POS_ID 		0x62
#define FB_POS_SPEED_ID 	0x41
#define FB_POS_USPEED_ID 	0x43
#define FB_ENASPEED_ID 		0x4C
#define FB_POS_ANGLE_ID 	0x68
#define FB_SPEED_ID				0x49
#define FB_ECTQ_ID				0x72
#define FB_TEMPERATURE_ID	0x73


#define ARM0_ANGLE_0			((uint32_t)0)
#define ARM0_ANGLE_45			((uint32_t)128)
#define ARM0_ANGLE_90			((uint32_t)256)
#define ARM0_ANGLE_135		((uint32_t)384)
#define ARM0_ANGLE_145		((uint32_t)412)
// #define ARM0_ANGLE_192		((uint32_t)545)
#define ARM0_ANGLE_185		((uint32_t)527)
#define ARM0_ANGLE_192		((uint32_t)538)
#define ARM0_ANGLE_200		((uint32_t)569)
#define ARM0_ANGLE_210		((uint32_t)594)
#define ARM0_ANGLE_180		((uint32_t)512)
#define ARM0_ANGLE_225		((uint32_t)640)
#define ARM0_ANGLE_232		((uint32_t)660)
#define ARM0_ANGLE_270		((uint32_t)768)
#define ARM0_ANGLE_280		((uint32_t)796)
#define ARM0_ANGLE_290		((uint32_t)825)

#define ARM0_ANGLE_300		((uint32_t)853)
#define ARM0_ANGLE_315		((uint32_t)896)
#define ARM0_ANGLE_330		((uint32_t)938)
#define ARM0_ANGLE_340		((uint32_t)967)
#define ARM0_ANGLE_343		((uint32_t)976)
#define ARM0_ANGLE_348		((uint32_t)997)
#define ARM0_ANGLE_360		((uint32_t)1024)

//֧��Ԥ��λ�ǶȺ� ��������ֵ����
// 	#define XBOT_SUB_ARM0			((uint32_t)(-35))

#ifdef XBOT_SUB_ARM0
	#define XBOT_HHH_ARM0				(ARM0_ANGLE_145+XBOT_SUB_ARM0)
	#define XBOT_III_ARM0				(ARM0_ANGLE_232+XBOT_SUB_ARM0)
	#define XBOT_JJJ_ARM0				(ARM0_ANGLE_348+XBOT_SUB_ARM0)
	#define XBOT_KKK_ARM0				(ARM0_ANGLE_192+XBOT_SUB_ARM0)
	#define XBOT_LLL_ARM0				(ARM0_ANGLE_210+XBOT_SUB_ARM0)
	#define XBOT_CRITICAL_ARM0	(ARM0_ANGLE_300+XBOT_SUB_ARM0)
	
	#define XBOT_CRITICAL_ARM0_UP	 	(ARM0_ANGLE_330+XBOT_SUB_ARM0) //֧����λ��������330��
	#define XBOT_CRITICAL_ARM0_DN		(ARM0_ANGLE_290+XBOT_SUB_ARM0) //֧����λ��������290��
	#define XBOT_CRITICAL_ARM0_UP_1	(ARM0_ANGLE_340+XBOT_SUB_ARM0) //֧����λ��������330��
	#define XBOT_CRITICAL_ARM0_DN_1	(ARM0_ANGLE_280+XBOT_SUB_ARM0) //֧����λ��������290��
#else
	#define XBOT_HHH_ARM0				ARM0_ANGLE_145
	#define XBOT_III_ARM0				ARM0_ANGLE_232
	#define XBOT_JJJ_ARM0				ARM0_ANGLE_348
	#define XBOT_KKK_ARM0				ARM0_ANGLE_192
	#define XBOT_LLL_ARM0				ARM0_ANGLE_210
	#define XBOT_CRITICAL_ARM0	ARM0_ANGLE_300
	
	#define XBOT_CRITICAL_ARM0_UP	ARM0_ANGLE_330 //֧����λ��������330��
	#define XBOT_CRITICAL_ARM0_DN	ARM0_ANGLE_290 //֧����λ��������290��
	#define XBOT_CRITICAL_ARM0_UP_1	ARM0_ANGLE_340 //֧����λ��������330��
	#define XBOT_CRITICAL_ARM0_DN_1	ARM0_ANGLE_280 //֧����λ��������290��
#endif


//Ԥ��λ���ƽǶ�ֵ
#define XBOT_AAAA_ARM0		XBOT_HHH_ARM0
#define XBOT_AAAA_ARM1		0
#define XBOT_AAAA_ARM2		-1500
#define XBOT_AAAA_ARM3		2900
#define XBOT_AAAA_ARM4		1600
#define XBOT_AAAA_ARM5		0
#define XBOT_AAAA_ARM6		16000
#define XBOT_AAAA_ARM7		0

#define XBOT_BBBB_ARM0		XBOT_LLL_ARM0
#define XBOT_BBBB_ARM1		0
#define XBOT_BBBB_ARM2		-10500
#define XBOT_BBBB_ARM3 		5500
#define XBOT_BBBB_ARM4		4400
#define XBOT_BBBB_ARM5 		0
#define XBOT_BBBB_ARM6		16000
#define XBOT_BBBB_ARM7		0

#define XBOT_CCCC_ARM0		XBOT_JJJ_ARM0
#define XBOT_CCCC_ARM1		0
#define XBOT_CCCC_ARM2		0 //��Cģʽ��£ʱ ��۸����ĽǶ�����
#define XBOT_CCCC_ARM3 		600//��Cģʽ��£ʱ С�۸����ĽǶȼ�С
#define XBOT_CCCC_ARM4		200//��Cģʽ��£ʱ �������ĽǶȼ�С


#define XBOT_CCCC_ARM5 		0
#define XBOT_CCCC_ARM6		16000
#define XBOT_CCCC_ARM7		0

#define XBOT_DDDD_ARM0		XBOT_LLL_ARM0
#define XBOT_DDDD_ARM1		0
#define XBOT_DDDD_ARM2		-12600
#define XBOT_DDDD_ARM3 		5400
#define XBOT_DDDD_ARM4		10900
#define XBOT_DDDD_ARM5 		0
#define XBOT_DDDD_ARM6		-2000
#define XBOT_DDDD_ARM7		0

#define XBOT_EEEE_ARM0		XBOT_LLL_ARM0
#define XBOT_EEEE_ARM1		0
#define XBOT_EEEE_ARM2		-3100
#define XBOT_EEEE_ARM3 		6200
#define XBOT_EEEE_ARM4		6200
#define XBOT_EEEE_ARM5 		0
#define XBOT_EEEE_ARM6		13700
#define XBOT_EEEE_ARM7		0

//���ο��ٶȺ�
#define REFER_SPEED_MAX_ARM0		7000
// #define REFER_SPEED_MAX_ARM1		5000
#define REFER_SPEED_MAX_ARM1		8000
#define REFER_SPEED_MAX_ARM2		5000
#define REFER_SPEED_MAX_ARM3		5000
#define REFER_SPEED_MAX_ARM4		5000
#define REFER_SPEED_MAX_ARM5		12000
#define REFER_SPEED_MAX_ARM6		9000
#define REFER_SPEED_MAX_ARM7		2000
#define REFER_SPEED_MAX_ARM8		9000
//��С�ο��ǶȺ�
#define REFER_SPEED_MIN_ARM0		250
#define REFER_SPEED_MIN_ARM1		400
#define REFER_SPEED_MIN_ARM2		250
#define REFER_SPEED_MIN_ARM3		250
#define REFER_SPEED_MIN_ARM4		250
#define REFER_SPEED_MIN_ARM5		600
#define REFER_SPEED_MIN_ARM6		450
#define REFER_SPEED_MIN_ARM7		100
#define REFER_SPEED_MIN_ARM8		450

//��λ����ֵ
// #define XBOT_ZERO_A1		0
// #define XBOT_ZERO_A2		0
// #define XBOT_ZERO_A3		700
// #define XBOT_ZERO_A4		400
// #define XBOT_ZERO_A5		0
// #define XBOT_ZERO_A6		18000
// #define XBOT_ZERO_A7		0
// #define XBOT_ZERO_A8		0

#define XBOT_ZERO_A1		0
#define XBOT_ZERO_A2		-9000
#define XBOT_ZERO_A3		18000
#define XBOT_ZERO_A4		18000
#define XBOT_ZERO_A5		0
#define XBOT_ZERO_A6		16000
#define XBOT_ZERO_A7		0
#define XBOT_ZERO_A8		0

//��λ���迪��
#define RE_INIT_ALL_ARM

#ifdef RE_INIT_ALL_ARM

	#define RE_INIT_ARM1
	#define RE_INIT_ARM2
	#define RE_INIT_ARM3
	#define RE_INIT_ARM4
	#define RE_INIT_ARM5
	#define RE_INIT_ARM6
	#define RE_INIT_ARM7
	#define RE_INIT_ARM8
#endif

//�����ؽ��ٶ�ϵ�� ֻ��д�ɷ�����ʽ ��Ҫд��С����ʽ Ҳ��Ҫ������ x/y->  (x*5000)/(y*500*maxspeed)
//(x*10)/(y*max)->x/(y*(max/10))->x/y=SPEED_COEFFICIENT*max/10
#define SPEED_COEFFICIENT_ARM0	7137/3500          //֧�۸��� 
#define SPEED_COEFFICIENT_ARM1	121/16					 	 //�����ת
#define SPEED_COEFFICIENT_ARM2	36504/6125				 //��۸��� 
#define SPEED_COEFFICIENT_ARM3	36504/6125				 //С�۸���
#define SPEED_COEFFICIENT_ARM4	36504/6125				 //������

#define SPEED_COEFFICIENT_ARM5	1397/200						//��צ��ת *9/12
#define SPEED_COEFFICIENT_ARM6	1397/300						//��̨���� 
#define SPEED_COEFFICIENT_ARM7	2783/1000				 		//��̨��ת 
#define SPEED_COEFFICIENT_ARM8	1397/200				 		//��צ�г� 

#ifdef NEWOPTICALBOBBIN	
#define LRMOTERMAXSPEED_WIRE_WORK				3000
#else
#define LRMOTERMAXSPEED_WIRE_WORK				8000 //���������������ٶȼ���
#endif
#define LRMOTERMAXSPEED_WIRELESS_WORK		8000

#define PI 3.1415926536

#define YYY_LINE_RADIAN (0)
#define ZZZ_LINE_RADIAN (PI/2)
#define BIG_ARM_LEN 	55800
#define FORE_ARM_LEN 	53820
#define WRIST_ARM_LEN 25000

//���캯��
XbotApp::XbotApp()
{
	SysTick_DelayMs(5000);				//��ʱ2�룬�ȴ��豸����
	workModel=NORMAL;							//����ģʽ��Ĭ��Ϊ����ģʽ
	signalType=WIRELESS_WORK_MODE;//�ź�����Ĭ���������ź�
	sendEnaSpeedOk=true;
	reInitPosSendOk=true;					//��λ������ɱ�־ Ĭ����� Ϊtrue
	saveSendOk=true;							//����ָ����ɱ�־ Ĭ����� 
	offLimitSendOk=true;					//��λָ�����ɱ�־ Ĭ����� 
	reWeaponSendOk=true;					//�������䷢����ɱ�־ Ĭ����� 
	WireType=false;								//Ĭ��Ϊ��ͨ����
	riciveCboxFlag=false;
	xyzFlag=false;
	checkTime=			new int8_t[CHECK_DRIVER_NUM];
	ectQuantity=0;

	FBTemperature_1=0;
	FBTemperature_2=0;
	FBTemperature_3=0;
	
	fBTerminalData=	new uint8_t[TERMINAL_FRAME_LEN]; //�ն˷��������ݴ�
	for(int i=0;i<TERMINAL_FRAME_LEN;i++)
		fBTerminalData[i]=0;

	fBLeftSpeed=				new ctrData();				//�����������ٶ��ݴ�
	fBRightSpeed=				new ctrData();				//�������ҵ���ٶ��ݴ�
	
	fBEctQuantity_1=		new ctrData();				//�����ĵ�Դ�����ݴ�
	fBEctQuantity_2=		new ctrData();				//�����ĵ�Դ�����ݴ�
	fBEctQuantity_3=		new ctrData();				//�����ĵ�Դ�����ݴ�
	fBEctQuantity_4=		new ctrData();				//�����ĵ�Դ�����ݴ�

	led_1 = new LEDLighter(GPIOC,GPIO_Pin_0);	//Ĭ�ϵ���
	led_2 = new LEDLighter(GPIOC,GPIO_Pin_1);	//Ĭ�ϵ���
	led_1->setLightOff();
	led_2->setLightOff();
	GPSPort=new SerialPort(GPS_PORT_NUM,GPS_PORT_BAUD);					//���ն�����ͨ�ŵĴ���

//�豸��ʼ��
	Terminal=				new TerminalControl(wirePort,wireLessPort);	//�ն�ͨ�ŵ�Э�������

	leftRunM=				new MotorControl(underpanPort);							//�н�����
	rightRunM=			new MotorControl(underpanPort);							//�н��ҵ��

	power=					new PowerControl(underpanPort);							//��Դ����ͨ��Э�������
	OtherDevice=		new OtherDeviceControl(armPort);						//�����豸��ͨ��Э�����
	CodedDisc=			new CodedDiscControl(codedDiscPort);				//�������̵�ͨ��Э�������
	gpsDevice=			new GpsImuControl(GPSPort);									//GPS�豸��ͨ��Э�������
	opticalBobbinDevice=new OpticalBobbin(armPort);							//�Զ������̵�ͨ��Э�������
	
//�豸��ַ�趨
	leftRunM->					setAddr(LEFTRUN_DDR);
	rightRunM->					setAddr(RIGHTRUN_DDR);
	supportArmM->				setAddr(SUPPORT_ARM_DDR);
	power->							setAddr(POWER_DDR);
	
	bigArmRotateM->			setAddr(BIG_ARM_ROTATE_DDR);
	bigArmPitchM->			setAddr(BIG_ARM_PITCH_ADDR);
	forearmPitchM->			setAddr(FORE_ARM_PITCH_DDR);
	wristPitchM->				setAddr(WRIST_PITCH_DDR);
	wristRotateM->			setAddr(WRIST_ROTATE_DDR);
	panTiltPitchM->			setAddr(PAN_TILT_PITCH_DDR);
	panTiltRotateM->		setAddr(PAN_TILT_ROTATE_DDR);
	fingerMediateM->		setAddr(FINGER_MEDIATE_DDR);
	cameraPitchM->			setAddr(CAMERA_PITCH_DDR);
	OtherDevice->				setAddr(OTHER_DEVICE_DDR);
	
//������λ�ľ��Բο��Ƕ�
	bigArmRotateM->			setZeroAngle(XBOT_ZERO_A1);
	bigArmPitchM->			setZeroAngle(XBOT_ZERO_A2);
	forearmPitchM->			setZeroAngle(XBOT_ZERO_A3);
	wristPitchM->				setZeroAngle(XBOT_ZERO_A4);
	wristRotateM->			setZeroAngle(XBOT_ZERO_A5);
	panTiltPitchM->			setZeroAngle(XBOT_ZERO_A6);
	panTiltRotateM->		setZeroAngle(XBOT_ZERO_A7);
	fingerMediateM->		setZeroAngle(XBOT_ZERO_A8);	

//�������ο��ٶ�
	supportArmM->				setReferSpeedMax(REFER_SPEED_MAX_ARM0);
	bigArmRotateM->			setReferSpeedMax(REFER_SPEED_MAX_ARM1);
	bigArmPitchM->			setReferSpeedMax(REFER_SPEED_MAX_ARM2);
	forearmPitchM->			setReferSpeedMax(REFER_SPEED_MAX_ARM3);
	wristPitchM->				setReferSpeedMax(REFER_SPEED_MAX_ARM4);
	wristRotateM->			setReferSpeedMax(REFER_SPEED_MAX_ARM5);
	panTiltPitchM->			setReferSpeedMax(REFER_SPEED_MAX_ARM6);
	panTiltRotateM->		setReferSpeedMax(REFER_SPEED_MAX_ARM7);
	
//������С�ο��ٶ�
	supportArmM->				setReferSpeedMin(REFER_SPEED_MIN_ARM0);
	bigArmRotateM->			setReferSpeedMin(REFER_SPEED_MIN_ARM1);
	bigArmPitchM->			setReferSpeedMin(REFER_SPEED_MIN_ARM2);
	forearmPitchM->			setReferSpeedMin(REFER_SPEED_MIN_ARM3);
	wristPitchM->				setReferSpeedMin(REFER_SPEED_MIN_ARM4);
	wristRotateM->			setReferSpeedMin(REFER_SPEED_MIN_ARM5);
	panTiltPitchM->			setReferSpeedMin(REFER_SPEED_MIN_ARM6);
	panTiltRotateM->		setReferSpeedMin(REFER_SPEED_MIN_ARM7);

	fBbigArmRotateA->DATA_16=0;						//�����Ĵ����ת����Ƕ��ݴ��ʼ��
	fBbigArmPitchA->DATA_16=0; 						//�����Ĵ�۸�������Ƕ��ݴ��ʼ��
	fBforearmPitchA->DATA_16=0;						//������С�۸�������Ƕ��ݴ��ʼ��
	fBwristPitchA->DATA_16=0;							//����������������Ƕ��ݴ��ʼ��
	fBwristRotateA->DATA_16=0;						//������������ת����Ƕ��ݴ��ʼ��
	fBpanTiltPitchA->DATA_16=0;						//��������̨��������Ƕ��ݴ��ʼ��
	fBpanTiltRotateA->DATA_16=0;					//��������̨��ת����Ƕ��ݴ��ʼ��
	fBfingerMediateA->DATA_16=0;					//��������צ��ϵ���Ƕ��ݴ��ʼ��
	fBcameraPitchA->DATA_16=0;						//�����������������Ƕ��ݴ��ʼ��
	fBDiscA->DATA_16=0;										//�����ľ������������ݴ��ʼ��
	resetEnaSpeed();							//����ʹ���ٶ�ָ��
//��ʱ����ʼ��
	t1=new Timer(TIM2);
	t1->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM2_SubPriority);
	t1->setTimeOut(1);

	t2=new Timer(TIM3);
	t2->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM3_SubPriority);
	t2->setTimeOut(7);

	t3=new Timer(TIM4);
	t3->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM4_SubPriority);
	t3->setTimeOut(100);

//�򿪶�ʱ��	
// 	t1->start();
// 	t2->start();
// 	t3->start();
// 	armPort->writeLine("xbotApp init ok!");
}
	workIdType XbotApp::workId=TTTModel;												//����ID Ĭ��Ϊֱ�ӿ���
	bool XbotApp::limitFlag=true;																//��λ��־ Ĭ����λ Ϊtrue
	CodeDiscData * XbotApp::fBDiscA=new CodeDiscData();					//�����ľ������������ݴ�	
	ctrData * XbotApp::fBbigArmRotateA=			new ctrData();			//�����Ĵ����ת����Ƕ��ݴ�
	ctrData * XbotApp::fBbigArmPitchA=			new ctrData(); 			//�����Ĵ�۸�������Ƕ��ݴ�
	ctrData * XbotApp::fBforearmPitchA=			new ctrData();			//������С�۸�������Ƕ��ݴ�
	ctrData * XbotApp::fBwristPitchA=				new ctrData();			//����������������Ƕ��ݴ�
	ctrData * XbotApp::fBwristRotateA=			new ctrData();			//������������ת����Ƕ��ݴ�
	ctrData * XbotApp::fBpanTiltPitchA=			new ctrData();			//��������̨��������Ƕ��ݴ�
	ctrData * XbotApp::fBpanTiltRotateA=		new ctrData();			//��������̨��ת����Ƕ��ݴ�
	ctrData * XbotApp::fBfingerMediateA=		new ctrData();			//��������צ��ϵ���Ƕ��ݴ�
	ctrData * XbotApp::fBcameraPitchA=			new ctrData();			//�����������������Ƕ��ݴ�

	SerialPort* XbotApp::wireLessPort=			new SerialPort(WIRE_LESS_PORT_NUM,WIRE_LESS_PORT_BAUD);		//���ն�����ͨ�ŵĴ���
	SerialPort* XbotApp::wirePort=					new SerialPort(WIRE_PORT_NUM,WIRE_PORT_BAUD);							//���ն�����ͨ�ŵĴ���
	SerialPort* XbotApp::codedDiscPort=			new SerialPort(CODED_DISC_PORT_NUM,CODED_DISC_PORT_BAUD);	//������ͨ�ŵĴ���
	SerialPort* XbotApp::armPort=						new SerialPort(ARM_PORT_NUM,ARM_PORT_BAUD);								//�ͻ�е��ͨ�ŵĴ���
	SerialPort* XbotApp::underpanPort=			new SerialPort(UNDERPAN_PORT_NUM,UNDERPAN_PORT_BAUD);			//�͵���������Լ���Դ���ư�ͨ�ŵĴ���

	MotorControl * XbotApp::supportArmM=		new MotorControl(underpanPort);						//֧�۵��
	MotorControl * XbotApp::bigArmRotateM=	new MotorControl(armPort);								//�����ת���
	MotorControl * XbotApp::bigArmPitchM=		new MotorControl(armPort); 								//��۸������
	MotorControl * XbotApp::forearmPitchM=	new MotorControl(armPort);								//С�۸������
	MotorControl * XbotApp::wristPitchM=		new MotorControl(armPort);								//���������
	MotorControl * XbotApp::wristRotateM=		new MotorControl(armPort);								//������ת���
	MotorControl * XbotApp::panTiltPitchM=	new MotorControl(armPort);								//��̨�������
	MotorControl * XbotApp::panTiltRotateM=	new MotorControl(armPort);								//��̨��ת���
	MotorControl * XbotApp::fingerMediateM=	new MotorControl(armPort);								//��צ��ϵ��
	MotorControl * XbotApp::cameraPitchM=		new MotorControl(armPort);								//����������

//��������
XbotApp::~XbotApp()
{
	delete wireLessPort;
	delete wirePort;
	delete codedDiscPort;
	delete armPort;
	delete underpanPort;
// 	delete GPSPort;
	delete Terminal;
	delete leftRunM;
	delete rightRunM;
	delete supportArmM;
	delete bigArmRotateM;
	delete bigArmPitchM;
	delete forearmPitchM;
	delete wristPitchM;
	delete wristRotateM;
	delete panTiltPitchM;
	delete panTiltRotateM;
	delete fingerMediateM;
	delete cameraPitchM;
	delete power;
	delete OtherDevice;
	delete CodedDisc;
}

/**
  * ��  �ܣ������ڶ�ʱ��2�еĺ�������Ҫ�����ǽ����͸��¸����豸������
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::runOnTime2()
{
	signalType=Terminal->getSerialWorkMode();
	if(power->checkPowerKey()&&saveSendOk==true)								//����Դ�����Ƿ��� ������¸�λ����ָ��
	{
		resetSave();
	}
	if(workModel==MIRROR)											//�������
	{
		controlArmISO();												//���������� ���ݽ���ת��
		return;
	}
	if(signalType==NOSIGNAL_WORK_MODE)
	{
		stopAllMoter();													//�ź��ж� ͣ�����е��
		riciveCboxFlag=true;
	}
	
	checkEnaSpeed();														//����豸�Ƿ�׼�����
	if(!sendEnaSpeedOk)													//�豸���δ��� ֱ���˳�
		return;
	
	checkOffLimit();
	if(!offLimitSendOk)												//��λָ���δ��� ֱ���˳�
		return;
	
	checkReInit();
	if(!reInitPosSendOk)											//��λ����ָ���δ��� ֱ���˳�
		return;

#ifdef 	NEW_DRIVER_PROGRAM
	checkSave();
	if(!saveSendOk)														//����ָ���δ��� ֱ���˳�
		return;
#endif
	
	if(Terminal->reciveData())								//����ն˿������ݣ�����ɹ�����һ֡���������ݲ���������
	{
		riciveCboxFlag=true;
		disposeTerminalData();									//�����ն˵�����
		updateSendTerminalData();								//����Ҫ���͵��ն˵�����
		updateSendDriverData();									//����Ҫ���͵������豸������
		Terminal->sendcommand();								//�������ݵ��ն�
	}
	disposeArmsData();											//���ղ������е�ۼ������豸����������
	disposUnderpanData();										//���ղ��������������Լ���Դ����ģ�������
	disposCodedDiscData();									//���ղ�������Ա�����������

	//����U0ָ���ʱ��
	bigArmRotateM->	updateUspeedTime();
	bigArmPitchM	->updateUspeedTime();
	forearmPitchM->	updateUspeedTime();
	wristPitchM->		updateUspeedTime();
	wristRotateM->	updateUspeedTime();
	panTiltPitchM->	updateUspeedTime();
	panTiltRotateM->updateUspeedTime();
	fingerMediateM->updateUspeedTime();
	cameraPitchM->	updateUspeedTime();
}

void XbotApp::openUserInterrupt()
{
#ifdef USEPOTENTIOMETER                 //ʹ�õ�λ��
	CodedDisc->initADC();
#endif
	wireLessPort->open();						//���ն�����ͨ�ŵĴ���
	wirePort->open();								//���ն�����ͨ�ŵĴ���
	codedDiscPort->open();					//������ͨ�ŵĴ���
	armPort->open();								//�ͻ�е��ͨ�ŵĴ���
	underpanPort->open();						//�͵���������Լ���Դ���ư�ͨ�ŵĴ���
	GPSPort->open();
	t1->start();
	t2->start();
	t3->start();
}

/**
  * ��  �ܣ������ڶ�ʱ��3�еĺ�������Ҫ�����Ƿ������ݵ������˵��ⲿ�豸
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::runOnTime3()
{

	static unsigned char index=0;
	static unsigned char batteryIndex=0;

#ifndef NEWXBOT
	static bool bigArmPitchU0Flag=false;
	static bool forearmPitchU0Flag=false;
	static bool wristPitchPitchU0Flag=false;
#endif	

	sendSaveCommand();					//�����Ƕȱ���
	if(!saveSendOk)
		return;
	
	sendEnaSpeedCommand();			//ʹ���˶��ؽ�
	if(!sendEnaSpeedOk)
		return;
	
	sendOffLimitCommand();			//����ȡ����λ
	if(!offLimitSendOk)
		return;	

	sendReInitCommand();				//������λ����
	if(!reInitPosSendOk)
		return;	
	
	sendWeaponCommand();				//������������ �˴�Ӧ�������ж� ���е���ٶ�Ϊ��ʱ������
	if(!reWeaponSendOk)
		return;	
	
	if(riciveCboxFlag==false)
		return;
	
	switch(index)
	{
		case 0:
			bigArmRotateM->sendSpeedCommand();
			if(signalType==NOSIGNAL_WORK_MODE)
			{
				leftRunM->setPWMSpeed(0);
				leftRunM->sendSpeedCommand(0x03);
			}
			else
				leftRunM->sendSpeedCommand(0x02);
			break;
		case 1://��۸���
#ifndef NEWXBOT
			if(bigArmPitchM->getPWMSpeed()==0)
				bigArmPitchM->sendSpeedCommand();
			else
			{
				if(bigArmPitchU0Flag)
				{
					bigArmPitchM->sendSpeedCommand();
					bigArmPitchU0Flag=false;
				}
				else
				{
					bigArmPitchM->sendAngleCommand(ANGLE_INQUIRE_ID);
					bigArmPitchU0Flag=true;
				}					
			}
#else
		 bigArmPitchM->sendSpeedCommand();
#endif						
			power->sendGetTemperatureCommand(0x00);
			break;
		case 2://С�۸���
#ifndef NEWXBOT
			if(forearmPitchM->getPWMSpeed()==0)
				forearmPitchM->sendSpeedCommand();
			else
			{
				if(forearmPitchU0Flag)
				{
					forearmPitchM->sendSpeedCommand();
					forearmPitchU0Flag=false;
				}
				else
				{
					forearmPitchM->sendAngleCommand(ANGLE_INQUIRE_ID);
					forearmPitchU0Flag=true;
				}
			}
#else
			forearmPitchM->sendSpeedCommand();
#endif
			if(signalType==NOSIGNAL_WORK_MODE)
			{
				rightRunM->setPWMSpeed(0);
				rightRunM->sendSpeedCommand(0x03);
			}
			else
				rightRunM->sendSpeedCommand(0x02);
			break;
		case 3:
#ifndef NEWXBOT
			if(wristPitchM->getPWMSpeed()==0)
			{
				wristPitchM->sendSpeedCommand();
			}
			else
			{
				if(wristPitchPitchU0Flag)
				{
					wristPitchM->sendSpeedCommand();
					wristPitchPitchU0Flag=false;
				}
				else
				{
					wristPitchM->sendAngleCommand(ANGLE_INQUIRE_ID);
					wristPitchPitchU0Flag=true;
				}
			}
#else
			wristPitchM->sendSpeedCommand();
#endif
			power->sendGetTemperatureCommand(0x01);
			break;
		case 4:
			wristRotateM->sendSpeedCommand();
			if(signalType==NOSIGNAL_WORK_MODE)
			{
				supportArmM->setPWMSpeed(0);
				supportArmM->sendSpeedCommand(0x03);
			}
			else
				supportArmM->sendSpeedCommand(0x02);
			break;
		case 5:
			panTiltPitchM->sendSpeedCommand();
			power->sendGetTemperatureCommand(0x02);
			break;
		case 6:
// 			panTiltRotateM->sendSpeedCommand(0x01);
			panTiltRotateM->sendSpeedCommand();
			leftRunM->sendSpeedCommand(SPEED_INQUIRE_ID); //��ѯ�ٶ�
			break;
		case 7:
			fingerMediateM->sendSpeedCommand();
			break;
		case 8:
			cameraPitchM->sendSpeedCommand();
			rightRunM->sendSpeedCommand(SPEED_INQUIRE_ID); //��ѯ�ٶ�
			break;
		case 9:
			OtherDevice->sendOtherDeviceCommand();
			break;
		case 10://�����Զ������̵�����
#ifdef NEWOPTICALBOBBIN
			if(signalType==WIRE_WORK_MODE)									//����ģʽ
				opticalBobbinDevice->sendOpticalBobbinCommand();
#endif
			power->sendGetEctQuantityCommand(batteryIndex);			//���͵�����ѯ����,��ѯ�ĸ����
			batteryIndex++;
			batteryIndex&=0x03;
			break;
// 		default:
// 			break;
	}
	index++;
	if(index==11)
	{
		index=0;
		riciveCboxFlag=false;
	}
}

/**
  * ��  �ܣ������ڶ�ʱ��4�еĺ�������Ҫ�����Ƿ������̽ǶȲ�ѯ�����Լ�GPS�ȵĲ�ѯ��Ϣ
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::runOnTime4()
{
	
/*���Կ��Ź�	*/
// 	GPSPort->writeLine("this is time4 run!\r\n");
// 	while(1)
// 	{
// 	}
	power->sendPowerOnOffCommand();								//
	#ifndef USEPOTENTIOMETER  										//û��ʹ�õ�λ�������
		CodedDisc->sendCodeDiscCommand();							//���;������̵����ݲ�ѯָ��
	#endif
	//gpsServe->sendGetGpsCommand();					 		//����GPS��IMU����	���ýӿ�
	gpsDevice->sendsetLEDColorCommand();

	if(signalType==WIRELESS_WORK_MODE)
	{
		led_1->reverseLight();
	}
	else if(signalType==WIRE_WORK_MODE)
	{
		led_2->reverseLight();
	}
	else
	{
		led_1->setLightOff();
		led_2->setLightOff();
	}
}

/**
  * ��  �ܣ�����ȡ�������λ���ÿ���豸��෢��SEND_CHECK_TIME_MAX��
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::sendOffLimitCommand()
{
	//ֻ����λһ�Σ�
	if(offLimitSendOk)
		return;
	
	if(checkTime[0]<SEND_CHECK_TIME_MAX)
	{
		checkTime[0]++;
		bigArmRotateM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[0]<CHECK_TIME_MAX)
	{
		checkTime[0]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	
	
	if(checkTime[1]<SEND_CHECK_TIME_MAX)
	{
		checkTime[1]++;
		bigArmPitchM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[1]<CHECK_TIME_MAX)
	{
		checkTime[1]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}

	if(checkTime[2]<SEND_CHECK_TIME_MAX)
	{
		checkTime[2]++;
		forearmPitchM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[2]<CHECK_TIME_MAX)
	{
		checkTime[2]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}

	if(checkTime[3]<SEND_CHECK_TIME_MAX)
	{
		checkTime[3]++;
		wristPitchM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[3]<CHECK_TIME_MAX)
	{
		checkTime[3]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}

	if(checkTime[4]<SEND_CHECK_TIME_MAX)
	{
		checkTime[4]++;
		wristRotateM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[4]<CHECK_TIME_MAX)
	{
		checkTime[4]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[5]<SEND_CHECK_TIME_MAX)
	{
		checkTime[5]++;
		panTiltPitchM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[5]<CHECK_TIME_MAX)
	{
		checkTime[5]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[6]<SEND_CHECK_TIME_MAX)
	{
		checkTime[6]++;
		panTiltRotateM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[6]<CHECK_TIME_MAX)
	{
		checkTime[6]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}

	if(checkTime[7]<SEND_CHECK_TIME_MAX)
	{
		checkTime[7]++;
		fingerMediateM->sendAngleCommand(ANGLE_FREE_ID);
		return;
	}
	else if(checkTime[7]<CHECK_TIME_MAX)
	{
		checkTime[7]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	
	offLimitSendOk=true;//����ȡ����λ���
}
/**
  * ��  �ܣ�����������λָ�� ���ݿ��غ����ѡ����Щ�ؽ�����
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::sendReInitCommand()
{
	if(reInitPosSendOk)
		return;
#ifdef RE_INIT_ARM1
	if(checkTime[0]<SEND_CHECK_TIME_MAX)
	{
		checkTime[0]++;
		bigArmRotateM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[0]<CHECK_TIME_MAX)
	{
		checkTime[0]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	
#endif

#ifdef RE_INIT_ARM2
	if(checkTime[1]<SEND_CHECK_TIME_MAX)
	{
		checkTime[1]++;
		bigArmPitchM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[1]<CHECK_TIME_MAX)
	{
		checkTime[1]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	
#endif

#ifdef RE_INIT_ARM3
	if(checkTime[2]<SEND_CHECK_TIME_MAX)
	{
		checkTime[2]++;
		forearmPitchM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[2]<CHECK_TIME_MAX)
	{
		checkTime[2]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	
#endif

#ifdef RE_INIT_ARM4
	if(checkTime[3]<SEND_CHECK_TIME_MAX)
	{
		checkTime[3]++;
		wristPitchM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[3]<CHECK_TIME_MAX)
	{
		checkTime[3]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	
#endif

#ifdef RE_INIT_ARM5
	if(checkTime[4]<SEND_CHECK_TIME_MAX)
	{
		checkTime[4]++;
		wristRotateM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[4]<CHECK_TIME_MAX)
	{
		checkTime[4]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	
#endif

#ifdef RE_INIT_ARM6
	if(checkTime[5]<SEND_CHECK_TIME_MAX)
	{
		checkTime[5]++;
		panTiltPitchM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[5]<CHECK_TIME_MAX)
	{
		checkTime[5]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	
#endif
	
#ifdef RE_INIT_ARM7
	if(checkTime[6]<SEND_CHECK_TIME_MAX)
	{
		checkTime[6]++;
		panTiltRotateM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[6]<CHECK_TIME_MAX)
	{
		checkTime[6]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	
#endif

#ifdef RE_INIT_ARM8
	if(checkTime[7]<SEND_CHECK_TIME_MAX)
	{
		checkTime[7]++;
		fingerMediateM->sendAngleCommand(ANGLE_REINIT_ID);
		return;
	}
	else if(checkTime[7]<CHECK_TIME_MAX)
	{
		checkTime[7]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}
#endif
	reInitPosSendOk=true;//����������λ���
}

/**
  * ��  �ܣ����ͱ����������� ֻ�йػ�ʱ������
  * ��  ������
  * ����ֵ����
  * ��  ע����С��ʱʱ�䣺600+8*150+200=
  */
void XbotApp::sendSaveCommand()
{
#ifdef NEW_DRIVER_PROGRAM
	if(saveSendOk)
		return;
	if(checkTime[9]<3)
	{
		checkTime[9]++;
		SysTick_DelayMs(100);				//��ʱ600MS����֤���ֹͣ
		return;
	}
	if(checkTime[0]<SEND_CHECK_TIME_MAX)
	{
		checkTime[0]++;
		bigArmRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[0]<CHECK_TIME_MAX)
	{
		checkTime[0]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}
	
	if(checkTime[1]<SEND_CHECK_TIME_MAX)
	{
		checkTime[1]++;
		bigArmPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[1]<CHECK_TIME_MAX)
	{
		checkTime[1]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[2]<SEND_CHECK_TIME_MAX)
	{
		checkTime[2]++;
		forearmPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[2]<CHECK_TIME_MAX)
	{
		checkTime[2]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[3]<SEND_CHECK_TIME_MAX)
	{
		checkTime[3]++;
		wristPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[3]<CHECK_TIME_MAX)
	{
		checkTime[3]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[4]<SEND_CHECK_TIME_MAX)
	{
		checkTime[4]++;
		wristRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[4]<CHECK_TIME_MAX)
	{
		checkTime[4]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[5]<SEND_CHECK_TIME_MAX)
	{
		checkTime[5]++;
		panTiltPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[5]<CHECK_TIME_MAX)
	{
		checkTime[5]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[6]<SEND_CHECK_TIME_MAX)
	{
		checkTime[6]++;
		panTiltRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[6]<CHECK_TIME_MAX)
	{
		checkTime[6]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[7]<SEND_CHECK_TIME_MAX)
	{
		checkTime[7]++;
		fingerMediateM->sendAngleCommand(ANGLE_SAVE_ID);
		return;
	}
	else if(checkTime[7]<CHECK_TIME_MAX)
	{
		checkTime[7]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}
	else if(checkTime[8]<1)
	{
		checkTime[8]=1;
		SysTick_DelayMs(2000);				//��ʱ2000MS����֤���������㹻��ʱ�䱣��Ƕ�
		power-> shutDown();
		power->sendPowerOnOffCommand();
		return;
	}
	else
	{
		return;
	}

#else
	if(saveSendOk)
		return;
	static uint8_t index=0x00;
	if(index==0x00)
	{
		t1->stop();
		t3->stop();
		t2->setTimeOut(5);
		bigArmRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x01)
	{
		bigArmPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x02)
	{
		forearmPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x03)
	{
		wristPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x04)
	{
		wristRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x05)
	{
		panTiltPitchM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x06)
	{
		panTiltRotateM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 	if(index==0x07)
	{
		fingerMediateM->sendAngleCommand(ANGLE_SAVE_ID);
		index++;
		return;
	}
	else 
	{
		SysTick_DelayMs(5000);				//��ʱ2000MS����֤���������㹻��ʱ�䱣��Ƕ�
		SysTick_DelayMs(5000);				//��ʱ2000MS����֤���������㹻��ʱ�䱣��Ƕ�
		power-> shutDown();
		power->sendPowerOnOffCommand();
		return;
	}
#endif
}
/**
  * ��  �ܣ�����������������
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::sendWeaponCommand()
{
	if(reWeaponSendOk)
		return;
	static uint8_t index=0x00;
	if(index<0x0a)
	{
		OtherDevice->sendWeaponControlCommand();
		index++;
		return;
	}
	else 
	{
		reWeaponSendOk=true;
		index=0x00;
	}
}

/**
  * ��  �ܣ�����ʹ���ٶ�ָ��
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::sendEnaSpeedCommand()
{
	if(sendEnaSpeedOk)
		return;

	if(checkTime[0]<SEND_CHECK_TIME_MAX)
	{
		checkTime[0]++;
		bigArmRotateM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[0]<CHECK_TIME_MAX)
	{
		checkTime[0]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	
	
	if(checkTime[1]<SEND_CHECK_TIME_MAX)
	{
		checkTime[1]++;
		bigArmPitchM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[1]<CHECK_TIME_MAX)
	{
		checkTime[1]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[2]<SEND_CHECK_TIME_MAX)
	{
		checkTime[2]++;
		forearmPitchM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[2]<CHECK_TIME_MAX)
	{
		checkTime[2]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[3]<SEND_CHECK_TIME_MAX)
	{
		checkTime[3]++;
		wristPitchM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[3]<CHECK_TIME_MAX)
	{
		checkTime[3]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[4]<SEND_CHECK_TIME_MAX)
	{
		checkTime[4]++;
		wristRotateM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[4]<CHECK_TIME_MAX)
	{
		checkTime[4]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[5]<SEND_CHECK_TIME_MAX)
	{
		checkTime[5]++;
		panTiltPitchM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[5]<CHECK_TIME_MAX)
	{
		checkTime[5]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	

	if(checkTime[6]<SEND_CHECK_TIME_MAX)
	{
		checkTime[6]++;
		panTiltRotateM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[6]<CHECK_TIME_MAX)
	{
		checkTime[6]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}

	if(checkTime[7]<SEND_CHECK_TIME_MAX)
	{
		checkTime[7]++;
		fingerMediateM->sendSpeedCommand(ENASPEED_ID);
		return;
	}
	else if(checkTime[7]<CHECK_TIME_MAX)
	{
		checkTime[7]++;//Ԥ��CHECK_TIME_MAX-SEND_CHECK_TIME_MAX������ ��֤�����ʱ����
		return;
	}	
	sendEnaSpeedOk=true;//�������
	for(int i=0;i<13;i++)
		checkTime[i]=0;
}
/**
  * ��  �ܣ����ȡ����λ�ķ���
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::checkOffLimit()
{
	uint8_t *temData=NULL;
	uint8_t armDataNum=ARM_PORT_NUM-1;
	if(offLimitSendOk)
		return;
	if(checkTime[0]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x00&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[0]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[1]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x01&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[1]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[2]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x02&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[2]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[3]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x03&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[3]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[4]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x04&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[4]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[5]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x05&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[5]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[6]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x06&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[6]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[7]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x07&&temData[2]==FB_FREE_POS_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[7]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	offLimitSendOk=true;
	limitFlag=false;
}

/**
  * ��  �ܣ����������λָ��ķ���
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::checkReInit()
{
	uint8_t *temData=NULL;
	uint8_t armDataNum=ARM_PORT_NUM-1;
	if(reInitPosSendOk)
		return;
#ifdef RE_INIT_ARM1
	if(checkTime[0]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x00&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[0]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM2
	if(checkTime[1]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x01&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[1]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM3
	if(checkTime[2]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x02&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[2]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM4
	if(checkTime[3]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x03&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[3]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM5
	if(checkTime[4]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x04&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[4]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM6
	if(checkTime[5]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x05&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[5]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM7
	if(checkTime[6]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x06&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[6]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	
#ifdef RE_INIT_ARM8
	if(checkTime[7]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x07&&temData[2]==FB_REINIT_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[7]=CHECK_TIME_MAX;
			}
		}
		return;
	}
#endif	
	reInitPosSendOk=true;
}
/**
  * ��  �ܣ���Ᵽ��Ƕ�ָ��ķ������ú���û��ʹ�ã���Ϊ�Ľ����������ı���
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::checkSave()
{
	uint8_t *temData=NULL;
	uint8_t armDataNum=ARM_PORT_NUM-1;
	if(saveSendOk)
		return;
	if(checkTime[0]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x00&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[0]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[1]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x01&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[1]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[2]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x02&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[2]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[3]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x03&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[3]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[4]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x04&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[4]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[5]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x05&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[5]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[6]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x06&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[6]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[7]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x07&&temData[2]==FB_SAVE_ID&&temData[3]==FB_OK_1&&temData[4]==FB_OK_2)
			{
				checkTime[7]=CHECK_TIME_MAX;
			}
		}
		return;
	}
// 	saveSendOk=true;
}

/**
  * ��  �ܣ����ʹ���ٶ�ָ���Ƿ������
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::checkEnaSpeed()
{
	uint8_t *temData=NULL;
	uint8_t armDataNum=ARM_PORT_NUM-1;
	if(sendEnaSpeedOk)
		return;
	if(checkTime[0]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x00&&temData[2]==FB_ENASPEED_ID)
			{
				fBbigArmRotateA->DATA_8[1]=temData[3];
				fBbigArmRotateA->DATA_8[0]=temData[4];
				checkTime[0]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[1]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x01&&temData[2]==FB_ENASPEED_ID)
			{
				fBbigArmPitchA->DATA_8[1]=temData[3];
				fBbigArmPitchA->DATA_8[0]=temData[4];
				checkTime[1]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[2]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x02&&temData[2]==FB_ENASPEED_ID)
			{
				fBforearmPitchA->DATA_8[1]=temData[3];
				fBforearmPitchA->DATA_8[0]=temData[4];
				checkTime[2]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[3]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x03&&temData[2]==FB_ENASPEED_ID)
			{
				fBwristPitchA->DATA_8[1]=temData[3];
				fBwristPitchA->DATA_8[0]=temData[4];
				checkTime[3]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[4]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x04&&temData[2]==FB_ENASPEED_ID)
			{
				fBwristRotateA->DATA_8[1]=temData[3];
				fBwristRotateA->DATA_8[0]=temData[4];
				checkTime[4]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[5]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x05&&temData[2]==FB_ENASPEED_ID)
			{
				fBpanTiltPitchA->DATA_8[1]=temData[3];
				fBpanTiltPitchA->DATA_8[0]=temData[4];
				checkTime[5]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[6]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x06&&temData[2]==FB_ENASPEED_ID)
			{
				fBpanTiltRotateA->DATA_8[1]=temData[3];
				fBpanTiltRotateA->DATA_8[0]=temData[4];
				checkTime[6]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	if(checkTime[7]<CHECK_TIME_MAX)
	{
		if(BaseControl::reciveData(armPort))
		{
			temData=BaseControl::getReciveData(armDataNum);
			if((temData[1]&0x0f)==0x07&&temData[2]==FB_ENASPEED_ID)
			{
				fBfingerMediateA->DATA_8[1]=temData[3];
				fBfingerMediateA->DATA_8[0]=temData[4];
				checkTime[7]=CHECK_TIME_MAX;
			}
		}
		return;
	}
	sendEnaSpeedOk=true;
}
/**
  * ��  �ܣ�����ȡ����λ����
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::resetOffLimit()
{
// 	limitFlag=false;
	offLimitSendOk=false;
	for(int i=0;i<CHECK_DRIVER_NUM;i++)//�����ʱ����������
	{
		checkTime[i]=0;
	}
}
/**
  * ��  �ܣ�������λ��������
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::resetReInit()
{
	reInitPosSendOk=false;
	for(int i=0;i<CHECK_DRIVER_NUM;i++)//�����ʱ����������
	{
		checkTime[i]=0;
	}
}

/**
  * ��  �ܣ������Ƕȱ�������
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::resetSave()
{
	Timer::stop(TIM3); //�رն�ʱ��3
	t2->setTimeOut(150);
	Timer::start(TIM3); //�򿪶�ʱ��3
	Timer::start(TIM4); //�򿪶�ʱ��4
	
	if(workModel==MIRROR)	
	{
		workModel=NORMAL;
	}
 	saveSendOk=false;
	for(int i=0;i<CHECK_DRIVER_NUM;i++)//�����ʱ����������
	{
		checkTime[i]=0;
	}
}
/**
  * ��  �ܣ�����������������
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::resetWeapon()
{
	reWeaponSendOk=false;
}

/**
  * ��  �ܣ�����ʹ���ٶ�ָ��
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::resetEnaSpeed()
{
	sendEnaSpeedOk=false;
	for(int i=0;i<CHECK_DRIVER_NUM;i++)//�����ʱ����������
	{
		checkTime[i]=0;
	}
}
/**
  * ��  �ܣ������ն˿�������
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::disposeTerminalData()
{
	uint8_t* temData=Terminal->getReciveData();	// ��ȡ�ն˷��������� ���ݴ�
	//�ȼ�⹤��ģʽ
	if(temData[1]==0x30&&temData[2]==0xAA&&temData[3]==0xBB&&temData[4]==0xCC&&temData[5]==0xDD) \
		//&&temData[6]==0x00&&temData[7]==0x00&&temData[8]==0x00&&temData[9]==0x00&&temData[10]==0x00&&temData[11]==0x00)
	{
		workModel=MIRROR;					//�л�������ģʽ ����͸������
		t2->stop();
		t3->stop();
	}
	else if(temData[1]==0x30&&temData[2]==0x11&&temData[3]==0x22&&temData[4]==0x33&&temData[5]==0x44) \
		//&&temData[6]==0x00&&temData[7]==0x00&&temData[8]==0x00&&temData[9]==0x00&&temData[10]==0x00&&temData[11]==0x00)
	{
		resetOffLimit();
	}
	else if(temData[1]==0x30&&temData[2]==0x55&&temData[3]==0x66&&temData[4]==0x77&&temData[5]==0x88) \
		//&&temData[6]==0x00&&temData[7]==0x00&&temData[8]==0x00&&temData[9]==0x00&&temData[10]==0x00&&temData[11]==0x00)
	{
		resetReInit();
	}
	else if(temData[1]==0x50&&temData[2]==0xAA&&temData[3]==0xBB&&temData[4]==0xCC&&temData[5]==0xDD \
		&&temData[6]==0xEE&&temData[7]==0xFF&&temData[8]==0x11&&temData[9]==0x22&&temData[10]==0x33&&temData[11]==0x44)
	{
		resetWeapon();
	}
	else	//����ָ��
	{
		workModel=NORMAL;
		if((temData[9]&0x0f)==0x00)//ģʽ����λȫΪ0
		{	
			workId=TTTModel;
		}
		else 
		{
			if((temData[9]&0x08)==0x08)//�ڱ�ģʽ����λΪ1
			{
				if((temData[6]&0x07)==0x01)
				{
					if((temData[4]&0x07)==0x00)
						workId=HHHModel;
					else
						workId=SSSModel;
				}
				else if((temData[6]&0x07)==0x02)
				{
					if((temData[4]&0x07)==0x00)
						workId=IIIModel;
					else
						workId=SSSModel;
				}
				else if((temData[6]&0x07)==0x03)
				{
					if((temData[4]&0x07)==0x00)
						workId=JJJModel;
					else
					{
						if((temData[4]&0x07)==0x03&&(temData[9]&0x04)==0x04)
							workId=CCCModel;
						else
							workId=SSSModel;
					}
				}
				else if((temData[6]&0x07)==0x04)
				{
					if((temData[4]&0x07)==0x00)
						workId=KKKModel;
				}
				else if((temData[6]&0x07)==0x05)
				{
					if((temData[4]&0x07)==0x00)
						workId=LLLModel;
					else
					{
						if((temData[4]&0x07)==0x01&&(temData[9]&0x04)==0x04)
							workId=AAAModel;
						else if((temData[4]&0x07)==0x02&&(temData[9]&0x04)==0x04)
							workId=BBBModel;
						else if((temData[4]&0x07)==0x04&&(temData[9]&0x04)==0x04)
							workId=DDDModel;
						else if((temData[4]&0x07)==0x05&&(temData[9]&0x04)==0x04)
							workId=EEEModel;
						else
							workId=SSSModel;
					}
				}
				else
				{
					workId=SSSModel;
				}
			}
			else if((temData[9]&0x0C)==0x04)//��е��ģʽ����λΪ1 ����Ŀ���ģʽλΪ0 ������ά����ģʽ
			{
				if((temData[4]&0x07)==0x07)
				{
					if((temData[5]&0x07)!=0x00)
					{
						if((temData[5]&0x08)==0x00)
						{
							workId=ZUUModel;				//Z����ģʽ
						}
						else
						{
							workId=ZDDModel;				//Z����ģʽ
						}
					}
					else if((temData[7]&0x07)!=0x00)
					{
						if((temData[7]&0x08)==0x00)
						{
							workId=YFFModel;				//Y��ǰģʽ
						}
						else
						{
							workId=YBBModel;				//Y���ģʽ
						}
					}
					else if((temData[7]&0x70)!=0x00)
					{
						if((temData[7]&0x80)==0x00)
						{
							workId=XRRModel;				//X����ģʽ
						}
						else
						{
							workId=XLLModel;				//X����ģʽ
						}
					}
					else
						workId=SSSModel;
				}
				else if((temData[4]&0x07)==0x06)
				{
					workId=XYZModel;
				}
				else
					workId=SSSModel;
			}
			else if((temData[9]&0x03)==0x02)//����ģʽ
			{
				workId=MMMModel;
			}
			else if((temData[9]&0x03)==0x01)//����ģʽ
			{
				workId=NNNModel;
			}
		}
		for(int i=0;i<TERMINAL_FRAME_LEN;i++)
		{
			fBTerminalData[i]=temData[i];
		}
	}
}

/**
  * ��  �ܣ������е�۷���������
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::disposeArmsData()
{
	if(bigArmRotateM->getNumCounter()>10)//����10��û�з���
	{
		bigArmRotateM->setErrorFlag(0x08);
	}
	if(bigArmPitchM->getNumCounter()>10)
	{
		bigArmPitchM->setErrorFlag(0x08);
	}
	if(forearmPitchM->getNumCounter()>10)
	{
		forearmPitchM->setErrorFlag(0x08);
	}
	if(wristPitchM->getNumCounter()>10)
	{
		wristPitchM->setErrorFlag(0x08);
	}
	if(wristRotateM->getNumCounter()>10)
	{
		wristRotateM->setErrorFlag(0x08);
	}
	if(panTiltPitchM->getNumCounter()>10)
	{
		panTiltPitchM->setErrorFlag(0x08);
	}
	if(panTiltRotateM->getNumCounter()>10)
	{
		panTiltRotateM->setErrorFlag(0x08);
	}
	if(fingerMediateM->getNumCounter()>10)
	{
		fingerMediateM->setErrorFlag(0x08);
	}
	if(cameraPitchM->getNumCounter()>10)
	{
		cameraPitchM->setErrorFlag(0x08);
	}
	if(OtherDevice->getNumCounter()>10)
	{
		OtherDevice->setErrorFlag(0x08);
	}
	if(opticalBobbinDevice->getNumCounter()>10)//���ղ������ݣ�Ĭ������ͨ����
	{
// 		opticalBobbinDevice->setErrorFlag(0x08);
		WireType=false;
	}
// 	if(signalType==WIRELESS_WORK_MODE)//���ߵ������
// 	{
// 		opticalBobbinDevice->setErrorFlag(0x00);
// 	}
	if(!BaseControl::reciveData(armPort))		  //���ղ������е�ۼ������豸����������
	{
		return;
	}
	uint8_t* temData=BaseControl::getReciveData(ARM_PORT_NUM-1);//��ȡ���ڽ��յ�����
	uint8_t temError=(temData[1]&0xf0)>>4;
	if(temError!=0)
		temError+=0x08;
	
	
#ifdef NEWXBOT
	if(temData[2]==FB_POS_SPEED_ID||temData[2]==FB_POS_ANGLE_ID||temData[2]==FB_POS_USPEED_ID)//���������ɴ��ش����ٶ��趨ָ��������ĽǶȷ��� 0x41 0x43 0x68
#else
	if(temData[2]==FB_POS_SPEED_ID||temData[2]==FB_POS_ANGLE_ID)//���������ɴ��ش����ٶ��趨ָ��������ĽǶȷ��� 0x41 0x68
#endif
	{
		switch(temData[1]&0x0f)
		{
			case BIG_ARM_ROTATE_DDR:											//�����ת
				bigArmRotateM->resetNumCounter();
				bigArmRotateM->setErrorFlag(temError);
				fBbigArmRotateA->DATA_8[1]=temData[3];			//�߰�λ
				fBbigArmRotateA->DATA_8[0]=temData[4];			//�Ͱ�λ
				break;
			
			case BIG_ARM_PITCH_ADDR:											//��۸���
				bigArmPitchM->resetNumCounter();
				bigArmPitchM->setErrorFlag(temError);
				fBbigArmPitchA->DATA_8[1]=temData[3];				//�߰�λ
				fBbigArmPitchA->DATA_8[0]=temData[4];				//�Ͱ�λ
				break;
			
			case FORE_ARM_PITCH_DDR:											//С�۸���
				forearmPitchM->resetNumCounter();
				forearmPitchM->setErrorFlag(temError);
				fBforearmPitchA->DATA_8[1]=temData[3];			//�߰�λ
				fBforearmPitchA->DATA_8[0]=temData[4];			//�Ͱ�λ
				break;
			
			case WRIST_PITCH_DDR:													//������
				wristPitchM->resetNumCounter();
				wristPitchM->setErrorFlag(temError);
				fBwristPitchA->DATA_8[1]=temData[3];				//�߰�λ
				fBwristPitchA->DATA_8[0]=temData[4];				//�Ͱ�λ
				break;
			
			case WRIST_ROTATE_DDR:												//������ת
				wristRotateM->resetNumCounter();
				wristRotateM->setErrorFlag(temError);
				fBwristRotateA->DATA_8[1]=temData[3];				//�߰�λ
				fBwristRotateA->DATA_8[0]=temData[4];				//�Ͱ�λ
				break;
			
			case PAN_TILT_PITCH_DDR:											//��̨����
				panTiltPitchM->resetNumCounter();
				panTiltPitchM->setErrorFlag(temError);
				fBpanTiltPitchA->DATA_8[1]=temData[3];			//�߰�λ
				fBpanTiltPitchA->DATA_8[0]=temData[4];			//�Ͱ�λ
				break;
			
			case PAN_TILT_ROTATE_DDR:											//��̨��ת
				panTiltRotateM->resetNumCounter();
				panTiltRotateM->setErrorFlag(temError);
				fBpanTiltRotateA->DATA_8[1]=temData[3];			//�߰�λ
				fBpanTiltRotateA->DATA_8[0]=temData[4];			//�Ͱ�λ
				break;
			
			case FINGER_MEDIATE_DDR:											//��צ���
				fingerMediateM->resetNumCounter();
				fingerMediateM->setErrorFlag(temError);
				fBfingerMediateA->DATA_8[1]=temData[3];			//�߰�λ
				fBfingerMediateA->DATA_8[0]=temData[4];			//�Ͱ�λ
				break;
			case CAMERA_PITCH_DDR:												//����������� Ŀǰû�нǶȷ���
				cameraPitchM->resetNumCounter();
				cameraPitchM->setErrorFlag(temError);
				break;
			default:
				break;
		}
	}
	if(workId==CCCModel)//��Cģʽ��
	{
		if(ABS(XBOT_CCCC_ARM2-(fBbigArmPitchA->DATA_16))<600&&(bigArmPitchM->getErrorFlag()==0x0b||bigArmPitchM->getErrorFlag()==0x0c))
		{
			bigArmPitchM->setErrorFlag(0x00);
		}
		if(ABS(XBOT_CCCC_ARM3-(fBforearmPitchA->DATA_16))<600&&(forearmPitchM->getErrorFlag()==0x0b||forearmPitchM->getErrorFlag()==0x0c))
		{
			forearmPitchM->setErrorFlag(0x00);
		}
		if(ABS(XBOT_CCCC_ARM4-(fBwristPitchA->DATA_16))<600&&(wristPitchM->getErrorFlag()==0x0b||wristPitchM->getErrorFlag()==0x0c))
		{
			wristPitchM->setErrorFlag(0x00);
		}
	}
	if((temData[1]&0x0f)==OTHER_DEVICE_DDR)
	{
		OtherDevice->resetNumCounter();
		OtherDevice->setErrorFlag(temError);
	}
	if((temData[1]&0x0f)==0x0A)//�����̵ķ���
	{
		opticalBobbinDevice->resetNumCounter();
		opticalBobbinDevice->setErrorFlag(temError);
		opticalBobbinDevice->setWireLength(temData[4]);
		WireType=true;																//���յ����� Ϊ����������
	}
}

/**
  * ��  �ܣ���������豸����������
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::disposUnderpanData()
{
	static int16_t timeIndex=0;
	if(timeIndex<5000)
	{
		timeIndex++;
	}
	else if(timeIndex==5000)
	{
		timeIndex++;
		power->resetNumCounter();
	}
	else
	{
		if(power->getNumCounter()>10)
		{
			power->setErrorFlag(0x08);
		}
	}
	if(leftRunM->getNumCounter()>10)//����10��û�з���
	{
		leftRunM->setErrorFlag(0x08);
	}
	if(rightRunM->getNumCounter()>10)
	{
		rightRunM->setErrorFlag(0x08);
	}
	if(supportArmM->getNumCounter()>10)
	{
		supportArmM->setErrorFlag(0x08);
	}

	
	if(!BaseControl::reciveData(underpanPort)) //���ղ��������������Լ���Դ����ģ�������
	{
		return;
	}
	uint8_t* temData=BaseControl::getReciveData(UNDERPAN_PORT_NUM-1);	//��ȡ���ڽ��յ�����
	uint8_t temError=(temData[1]&0xf0)>>4;
	(temError==0)?(temError=0):(temError+=0x08);
	switch(temData[1]&0x0f)
	{
		case LEFTRUN_DDR: 		//����
			leftRunM->resetNumCounter();
			if(temError==0)
			{
					if(FBTemperature_1>WARNINGTEMPERATURE)
					{
						leftRunM->setErrorFlag(0x09);
					}
					else
						leftRunM->setErrorFlag(0);
			}
			else
			{
				leftRunM->setErrorFlag(temError);
			}
			if(temData[2]==FB_SPEED_ID)										//�����ٶ�
			{
				fBLeftSpeed->DATA_8[1]=temData[3];					//�߰�λ
				fBLeftSpeed->DATA_8[0]=temData[4];					//�Ͱ�λ
			}
			break;
		case RIGHTRUN_DDR: 		//�ҵ��
			rightRunM->resetNumCounter();
		
			if(temError==0)
			{
					if(FBTemperature_2>WARNINGTEMPERATURE)
					{
						rightRunM->setErrorFlag(0x09);
					}
					else
						rightRunM->setErrorFlag(0);
			}
			else
			{
				rightRunM->setErrorFlag(temError);
			}
			if(temData[2]==FB_SPEED_ID)										//�����ٶ�
			{
				fBRightSpeed->DATA_8[1]=temData[3];					//�߰�λ
				fBRightSpeed->DATA_8[0]=temData[4];					//�Ͱ�λ
			}
			break;
		case SUPPORT_ARM_DDR:	//֧�۵��
			supportArmM->resetNumCounter();
			if(temError==0)
			{
					if(FBTemperature_3>WARNINGTEMPERATURE)
					{
						supportArmM->setErrorFlag(0x09);
					}
					else
						supportArmM->setErrorFlag(0);
			}
			else
			{
				supportArmM->setErrorFlag(temError);
			}
			break;
		case POWER_DDR:				//��Դ���ư�
			power->resetNumCounter();
			power->setErrorFlag(temError);
			if(temData[2]==FB_ECTQ_ID)														//�������ǵ�ѹֵ
			{
				if((temData[3]&0xc0)==0x00)													//���1����
				{
					fBEctQuantity_1->DATA_8[1]=(temData[3]&0x3f);			//�߰�λ
					fBEctQuantity_1->DATA_8[0]=temData[4];						//�Ͱ�λ
				}
				else if((temData[3]&0xc0)==0x40)										//���2����
				{
					fBEctQuantity_2->DATA_8[1]=(temData[3]&0x3f);			//�߰�λ
					fBEctQuantity_2->DATA_8[0]=temData[4];						//�Ͱ�λ
				}
				else if((temData[3]&0xc0)==0x80)										//���3����
				{
					fBEctQuantity_3->DATA_8[1]=(temData[3]&0x3f);			//�߰�λ
					fBEctQuantity_3->DATA_8[0]=temData[4];						//�Ͱ�λ
				}
				else if((temData[3]&0xc0)==0xc0)										//���4����
				{
					fBEctQuantity_4->DATA_8[1]=(temData[3]&0x3f);			//�߰�λ
					fBEctQuantity_4->DATA_8[0]=temData[4];						//�Ͱ�λ
				}
				ectQuantity=subEctQuantity();
				gpsDevice->setPowerLEDColorFromVoltage(ectQuantity);
	// 				if(gpsDevice->setPowerLEDColorFromVoltage(ectQuantity))//��ѹ̫С �Զ��ػ�������
	// 				{
	// 					resetSave();
	// 				}
// 				if(ectQuantity<118)//��ѹ���� ����
// 				{
// 					power->setErrorFlag(0x0c);
// 				}
			}
			else if(temData[2]==FB_TEMPERATURE_ID)										//�������ǵ���¶�ֵ
			{
				if((temData[3]&0xc0)==0x00)													//�����¶�
				{
					FBTemperature_1=temData[4];
				}
				else if((temData[3]&0xc0)==0x40)										//�ҵ���¶�
				{
					FBTemperature_2=temData[4];
				}
				else if((temData[3]&0xc0)==0x80)										//֧�۵���¶�
				{
					FBTemperature_3=temData[4];
				}
			}
			break;
		default:
			break;
	}
}


/**
  * ��  �ܣ�������Ա������豸����������
  * ��  ������
  * ����ֵ����
  * 
  */
void  XbotApp::disposCodedDiscData()
{
#ifndef USEPOTENTIOMETER                 //û��ʹ�õ�λ��
	if(CodedDisc->getNumCounter()>10)
	{
		CodedDisc->setErrorFlag(0x08);
	}
	else
	{
		CodedDisc->resetErrorFlag();
	}
	
	if(!CodedDisc->reciveData())								//���ղ�������Ա�����������
	{
		return;
	}
	fBDiscA->DATA_16=CodedDisc->getAngle()->DATA_16;
	CodedDisc->resetNumCounter();
#else																			//ʹ���˵�λ��
	int temAngle=0;
	temAngle=CodedDisc->getADCAngle()*17/72;//ת��Ϊ1024 һ�ܵĽǶ�ֵ
	if(temAngle<114) //909-1023
		temAngle=temAngle+909;
	else
		temAngle=temAngle-114;
	fBDiscA->DATA_16=temAngle;							//ת��Ϊ������һ���ĽǶ�
#endif
}


/**
  * ��  �ܣ����·��͵��ն˵�����
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::updateSendTerminalData()
{
	static int index=0;
	uint8_t temBuf[13]={0XA5,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XA5};
	temBuf[1]|=index;
	temBuf[2]=(uint8_t)((-fBLeftSpeed->DATA_16)/96); //*0.0142 ����Ϊ����96  �з�����
	temBuf[3]=(uint8_t)((-fBRightSpeed->DATA_16)/96);
	if(index==0)
	{
		temBuf[4]=(uint8_t)((-(fBbigArmRotateA->DATA_16)/200+180)%180);										//�ش������ת�Ƕ� �޷�����
		temBuf[5]=(uint8_t)((fBwristRotateA->DATA_16/200+180)%180);												//�ش�������ת�Ƕ� �޷�����
		temBuf[6]=(uint8_t)((fBfingerMediateA->DATA_16/200+180)%180);											//�ش���צ��ϽǶ� �޷�����
		temBuf[7]=(uint8_t)(fBEctQuantity_1->DATA_16/2);	  															//�ش����1��ѹ ��λ0.2v
		temBuf[8]=(power->getErrorFlag()<<4)|(OtherDevice->getErrorFlag()&0x0f);					//��Դ���ư�+�ƺ�����ͷ�����豨������
		temBuf[9]=(bigArmRotateM->getErrorFlag()<<4)|(bigArmPitchM->getErrorFlag()&0x0f);	//�����ת+��۸�����������
	}
	else if(index==1)
	{
		temBuf[4]=(uint8_t)((-fBbigArmPitchA->DATA_16/200+270)%180); 											//�ش���۸����Ƕ� �޷�����
		temBuf[5]=(uint8_t)((fBpanTiltPitchA->DATA_16/200+190)%180);											//�ش���̨�����Ƕ� �޷�����
		temBuf[6]=(uint8_t)(fBDiscA->DATA_U16*45/256);																		//�ش��������̵ĽǶ� �޷�����
		temBuf[7]=(uint8_t)(fBEctQuantity_2->DATA_16/2);	  															//�ش����2��ѹ ��λ0.2v
		temBuf[8]=(opticalBobbinDevice->getErrorFlag()<<4)|(CodedDisc->getErrorFlag()&0x0f);			//������+֧�����̱�������
		temBuf[9]=(forearmPitchM->getErrorFlag()<<4)|(wristPitchM->getErrorFlag()&0x0f);					//С�۸���+��������������
	}
	else if(index==2)
	{
		temBuf[4]=(uint8_t)((-fBforearmPitchA->DATA_16/200+270)%180);											//�ش�С�۸����Ƕ� �޷�����
		temBuf[5]=(uint8_t)((fBpanTiltRotateA->DATA_16/200+180)%180);											//�ش���̨��ת�Ƕ� �޷�����
		if(signalType==WIRE_WORK_MODE&&WireType==true)																		//���ߺ����߷ֱ�����������ʣ���߳�
		{
			temBuf[6]=opticalBobbinDevice->getWireLength();																	//������ʣ���߳�
		}
		else// if(signalType==WIRELESS_WORK_MODE)
		{
			temBuf[6]=0;																																		//������ʣ���߳�
		}
		temBuf[7]=(uint8_t)(fBEctQuantity_3->DATA_16/2);	  															//�ش����3��ѹ ��λ0.2v
		temBuf[8]=(leftRunM->getErrorFlag()<<4)|(rightRunM->getErrorFlag()&0x0f);								//����+�ҵ����������
		temBuf[9]=(wristRotateM->getErrorFlag()<<4)|(panTiltPitchM->getErrorFlag()&0x0f);				//������ת+��̨������������
	}
	else if(index==3)
	{
		temBuf[4]=(uint8_t)((fBwristPitchA->DATA_16/200+180)%180);												//�ش��������Ƕ� �޷�����
// 		temBuf[5]=(uint8_t)(fBcameraPitchA->DATA_16/200);																//�ش�ǰ����������Ƕ�  �޷����� ��ʱû�нǶȻش�
		temBuf[5]=0x00;																																		//�ش�ǰ����������Ƕ� ��ʱû�нǶȻش�
		temBuf[6]=ectQuantity;																														//ϵͳ��ѹ����ƽ����ѹ
		temBuf[7]=(uint8_t)(fBEctQuantity_4->DATA_16/2);	  															//�ش����4��ѹ ��λ0.2v
		temBuf[8]=(supportArmM->getErrorFlag()<<4)|(cameraPitchM->getErrorFlag()&0x0f);					//֧�۵��+���������������
		temBuf[9]=(panTiltRotateM->getErrorFlag()<<4)|(fingerMediateM->getErrorFlag()&0x0f);			//��̨��ת+��ץ�гֱ�������
	}

	for(int i=1;i<10;i++)//����У���
	{
		temBuf[12]+=temBuf[i];
	}
	Terminal->updateSendBuf(temBuf);
	index++;
	index&=0x03;
}
/**
  * ��  �ܣ����㱾���ѹ
  * ��  ������
  * ����ֵ�������ѹ
  * 
  */
uint8_t XbotApp::subEctQuantity()
{
	uint8_t index=0;
	uint16_t temSubEctQuantity=0;
	uint8_t temEctQuantity[4]={0};
	temEctQuantity[0]=(uint8_t)(fBEctQuantity_1->DATA_16/2);
	temEctQuantity[1]=(uint8_t)(fBEctQuantity_2->DATA_16/2);
	temEctQuantity[2]=(uint8_t)(fBEctQuantity_3->DATA_16/2);
	temEctQuantity[3]=(uint8_t)(fBEctQuantity_4->DATA_16/2);
	if(temEctQuantity[0]>50)
	{
		index++;
		temSubEctQuantity+=temEctQuantity[0];
	}
	if(temEctQuantity[1]>50)
	{
		index++;
		temSubEctQuantity+=temEctQuantity[1];
	}
		if(temEctQuantity[2]>50)
	{
		index++;
		temSubEctQuantity+=temEctQuantity[2];
	}
		if(temEctQuantity[3]>50)
	{
		index++;
		temSubEctQuantity+=temEctQuantity[3];
	}
	if(index==0)
		temSubEctQuantity=0;
	else
		temSubEctQuantity/=index;
	return (uint8_t)temSubEctQuantity;
}

/**
  * ��  �ܣ����·��͵��豸������
  * ��  ������
  * ����ֵ����
  * 
  */

void XbotApp::updateSendDriverData()
{	
	static bool CCCUFlag_1=false;
	static bool CCCUFlag_2=false;
	static bool CCCUFlag_3=false;	
	
	static uint16_t CCCUTime_1=0;
	static uint16_t CCCUTime_2=0;
	static uint16_t CCCUTime_3=0;	
	
	int temsetPanTiltPitchSpeed=0;
	int temsetPanTiltRotateSpeed=0;
// 	int temLeftSpeed;
// 	int temRightSpeed;
	int LandRMoterMaxSpeed=LRMOTERMAXSPEED_WIRELESS_WORK;
	stopAllMoter();
	
	//��������־����
	bigArmRotateM	->setErrorFlag_1(0x00);
	bigArmPitchM	->setErrorFlag_1(0x00);
	forearmPitchM	->setErrorFlag_1(0x00);
	wristPitchM		->setErrorFlag_1(0x00);
	panTiltPitchM	->setErrorFlag_1(0x00);
	fingerMediateM->setErrorFlag_1(0x00);
	supportArmM		->setErrorFlag_1(0x00);
	
#ifdef NEWOPTICALBOBBIN
	if(signalType==WIRE_WORK_MODE&&WireType==true)//���ߺ����߷ֱ������ٶ�
	{
		LandRMoterMaxSpeed=LRMOTERMAXSPEED_WIRE_WORK;
	}
	else// if(signalType==WIRELESS_WORK_MODE)
	{
		LandRMoterMaxSpeed=LRMOTERMAXSPEED_WIRELESS_WORK;
	}
#endif
//��ʻģʽ��ץȡģʽ���ж�
	if(fBbigArmPitchA->DATA_16<-800)
	{
		LandRMoterMaxSpeed=1500;
	}
	if((fBTerminalData[9]&0xc0)==0x40) //����
	{
		cameraPitchM->setSpeed(-5000);
	}
	else if((fBTerminalData[9]&0xc0)==0x80) //�¸�
	{
		cameraPitchM->setSpeed(5000);
	}
	else
	{
		cameraPitchM->resetSpeed();
	}
	if(workId!=CCCModel)
	{
		//��ֹûѹ�� ��Cģʽ�������һ����ʱ�򣬲���Cģʽ��û��ֹͣ��������Cģʽ��������
		CCCUTime_1=0;
		CCCUTime_2=0;
		CCCUTime_3=0;
		if((ABS(XBOT_CCCC_ARM2-(fBbigArmPitchA->DATA_16))<400)||(ABS(XBOT_CCCC_ARM3-(fBforearmPitchA->DATA_16))<400)||(ABS(XBOT_CCCC_ARM4-(fBwristPitchA->DATA_16))<400))
		{
			if((bigArmPitchM->getPWMSpeed()>0)||(forearmPitchM->getPWMSpeed()<0)||(wristPitchM->getPWMSpeed()<0))
			{
				return;
			}
		}
		bigArmPitchM->setPWMSpeed(0);
		forearmPitchM->setPWMSpeed(0);
		wristPitchM->setPWMSpeed(0);
		CCCUFlag_1=false;
		CCCUFlag_2=false;
		CCCUFlag_3=false;
	}

	//���������豸�Ĳ���
	if((fBTerminalData[10]&0x80)==0x80) //��̨��
	{
		OtherDevice-> headLightOn();
	}
	else
	{
		OtherDevice-> headLightOff();
	}

	if((fBTerminalData[10]&0x20)==0x20) //�����
	{
		OtherDevice-> floodLightOn();
	}
	else
	{
		OtherDevice-> floodLightOff();
	}
	
	if((fBTerminalData[10]&0x40)==0x40)//�����
	{
		OtherDevice-> laserSightOn();
	}
	else
	{
		OtherDevice-> laserSightOff();
	}
	
	OtherDevice-> setVideoSelect((fBTerminalData[11]&0xe0)>>5);
	OtherDevice-> setVideoZoom(fBTerminalData[11]&0x1f);
	

	if(fBTerminalData[8]&0x80)
	{
		fingerMediateM->setErrorFlag_1(setFingerMediateSpeed(-((int16_t)((fBTerminalData[8]&0x70)>>0x04)*1285)));
	}
	else
	{
		fingerMediateM->setErrorFlag_1(setFingerMediateSpeed((int16_t)((fBTerminalData[8]&0x70)>>0x04)*1285));
	}
		{
			/**
			*��Ҫ���������ҵ������ȵĺ����ٶȲ����ķ����ϰ�����෴��ȱ��
			*
			*/
// 			if((fBTerminalData[1]&0x0f)==0x0a)//������������
// 			{
// 				rightRunM->setSpeed((int16_t)((fBTerminalData[3]*LandRMoterMaxSpeed)/160));
// 				leftRunM->setSpeed(-(int16_t)((fBTerminalData[2]*LandRMoterMaxSpeed)/160));
// 			}
// 			else if((fBTerminalData[1]&0x0f)==0x08)//ҡ�����¨L���� �������
// 			{
// 				leftRunM->setSpeed(-(int16_t)((fBTerminalData[2]*LandRMoterMaxSpeed)/160)); 
// 				rightRunM->resetSpeed();
// 			}
// 			else if((fBTerminalData[1]&0x0f)==0x02)//ҡ�����¨K���� �ҵ�����
// 			{
// 				rightRunM->setSpeed((int16_t)((fBTerminalData[3]*LandRMoterMaxSpeed)/160));
// 				leftRunM ->resetSpeed();
// 			}
// 			else

			{
#ifdef NEWOPTICALBOBBIN
				if(opticalBobbinDevice->getWireLength()<5&&signalType==WIRE_WORK_MODE\
						&&(WireType==true)\
						&&(((fBTerminalData[1]&0x0f)==0x01)\
						||((fBTerminalData[1]&0x0f)==0x04)\
						||((fBTerminalData[1]&0x0f)==0x05)))//�����������µ��߳�����5�� �������������߿��� ������ǰ��״̬
				{
					leftRunM->resetSpeed();
					rightRunM->resetSpeed();
				}
				else
#endif
				{
					if(fBTerminalData[2]>150)
						fBTerminalData[2]=150;
					if(fBTerminalData[3]>150)
						fBTerminalData[3]=150;
// 						temLeftSpeed=(fBTerminalData[3]*LandRMoterMaxSpeed)/150;
// 						temRightSpeed=(fBTerminalData[2]*LandRMoterMaxSpeed)/150;

						if((fBTerminalData[1]&0x03)==0x01)//������ǰ 
						rightRunM->setSpeed((int16_t)((fBTerminalData[3]*LandRMoterMaxSpeed)/150));
					else if((fBTerminalData[1]&0x03)==0x02)//�������
						rightRunM->setSpeed(-(int16_t)((fBTerminalData[3]*LandRMoterMaxSpeed)/150));
					else
						rightRunM->resetSpeed();
					
 					if((fBTerminalData[1]&0x0c)==0x04)//�ҵ����ǰ
 						leftRunM->setSpeed(-(int16_t)((fBTerminalData[2]*LandRMoterMaxSpeed)/150));
					else if((fBTerminalData[1]&0x0c)==0x08)//�ҵ�����
						leftRunM->setSpeed((int16_t)((fBTerminalData[2]*LandRMoterMaxSpeed)/150));
					else
						leftRunM->resetSpeed();				
					
					
				}
			}
		}
	switch((int)workId)
	{
		case TTTModel: 				//�ؽڿ���ģʽ
			if(fBTerminalData[4]&0x77||fBTerminalData[5]&0x70)
				xyzFlag=false;
#ifdef NEWOPTICALBOBBIN
		if(signalType==WIRE_WORK_MODE)//�������Զ��շ���
		{
			if((fBTerminalData[1]&0x0f)==0x0a||(fBTerminalData[1]&0x0f)==0x08||(fBTerminalData[1]&0x0f)==0x02)//������������
			{
				opticalBobbinDevice->setWorkStatus(0x02);
				opticalBobbinDevice->setLeftSpeed((uint8_t)(ABS(fBLeftSpeed->DATA_16)/35));
				opticalBobbinDevice->setRightSpeed((uint8_t)(ABS(fBRightSpeed->DATA_16)/35));
			}
			else if((fBTerminalData[1]&0x0f)==0x05||(fBTerminalData[1]&0x0f)==0x01||(fBTerminalData[1]&0x0f)==0x04)//�����������ǰ
			{
				opticalBobbinDevice->setWorkStatus(0x01);
				opticalBobbinDevice->setLeftSpeed((uint8_t)(ABS(fBLeftSpeed->DATA_16)/35));
				opticalBobbinDevice->setRightSpeed((uint8_t)(ABS(fBRightSpeed->DATA_16)/35));
			}
			else if((fBTerminalData[1]&0x0f)==0x06)//�ҵ����ǰ�����������ת ||(fBTerminalData[1]&0x03)==0x02
			{
				opticalBobbinDevice->setWorkStatus(0x03);
				opticalBobbinDevice->setLeftSpeed((uint8_t)(ABS(fBLeftSpeed->DATA_16)/35));
				opticalBobbinDevice->setRightSpeed((uint8_t)(ABS(fBRightSpeed->DATA_16)/35));
			}
			else if((fBTerminalData[1]&0x0f)==0x09)//�ҵ�����������ǰ����ת ||(fBTerminalData[1]&0x03)==0x01
			{
				opticalBobbinDevice->setWorkStatus(0x04);
				opticalBobbinDevice->setLeftSpeed((uint8_t)(ABS(fBLeftSpeed->DATA_16)/35));
				opticalBobbinDevice->setRightSpeed((uint8_t)(ABS(fBRightSpeed->DATA_16)/35));
			}
			else
			{
				opticalBobbinDevice->setWorkStatus(0x00);
				opticalBobbinDevice->setLeftSpeed(0);
				opticalBobbinDevice->setRightSpeed(0);
			}
		}
#endif
		

			if(fBTerminalData[4]&0x80)
			{
				bigArmRotateM->setErrorFlag_1(setBigArmRotateSpeed((int16_t)((fBTerminalData[4]&0x70)>>0x04)*1142));
			}
			else
			{
				bigArmRotateM->setErrorFlag_1(setBigArmRotateSpeed(-((int16_t)((fBTerminalData[4]&0x70)>>0x04)*1142)));
			}

			if(fBTerminalData[4]&0x08)
			{
				bigArmPitchM->setErrorFlag_1(setBigArmPitchSpeed((int16_t)((fBTerminalData[4]&0x07)*714)));
			}
			else
			{
				bigArmPitchM->setErrorFlag_1(setBigArmPitchSpeed(-((int16_t)((fBTerminalData[4]&0x07)*714))));
			}

			if(fBTerminalData[5]&0x80)
			{
				forearmPitchM->setErrorFlag_1(setForearmPitchSpeed(-((int16_t)((fBTerminalData[5]&0x70)>>0x04)*714)));
			}
			else
			{
				forearmPitchM->setErrorFlag_1(setForearmPitchSpeed((int16_t)((fBTerminalData[5]&0x70)>>0x04)*714));
			}

			if(fBTerminalData[5]&0x08)
			{
				wristPitchM->setErrorFlag_1(setWristPitchSpeed(-((int16_t)((fBTerminalData[5]&0x07)*714))));
			}
			else
			{
				wristPitchM->setErrorFlag_1(setWristPitchSpeed((int16_t)((fBTerminalData[5]&0x07)*714)));
			}


			if(fBTerminalData[6]&0x80)
			{
				wristRotateM->setSpeed((int16_t)((fBTerminalData[6]&0x70)>>0x04)*1714);
			}
			else
			{
				wristRotateM->setSpeed(-((int16_t)((fBTerminalData[6]&0x70)>>0x04)*1714));
			}

			if(fBTerminalData[7]&0x08)
			{
				temsetPanTiltPitchSpeed=(int16_t)(fBTerminalData[7]&0x07);
				temsetPanTiltPitchSpeed=temsetPanTiltPitchSpeed*temsetPanTiltPitchSpeed*183;
				panTiltPitchM->setErrorFlag_1(setPanTiltPitchSpeed(temsetPanTiltPitchSpeed));
			}
			else
			{
				temsetPanTiltPitchSpeed=(int16_t)(fBTerminalData[7]&0x07);
				temsetPanTiltPitchSpeed=-temsetPanTiltPitchSpeed*temsetPanTiltPitchSpeed*183;
				panTiltPitchM->setErrorFlag_1(setPanTiltPitchSpeed(temsetPanTiltPitchSpeed));
			}

			if(fBTerminalData[7]&0x80)
			{
				temsetPanTiltRotateSpeed=(int16_t)((fBTerminalData[7]&0x70)>>0x04);
				temsetPanTiltRotateSpeed=temsetPanTiltRotateSpeed*temsetPanTiltRotateSpeed*40;
				panTiltRotateM->setSpeed(temsetPanTiltRotateSpeed);
			}
			else
			{
				temsetPanTiltRotateSpeed=(int16_t)((fBTerminalData[7]&0x70)>>0x04);
				temsetPanTiltRotateSpeed=-temsetPanTiltRotateSpeed*temsetPanTiltRotateSpeed*40;
				panTiltRotateM->setSpeed(temsetPanTiltRotateSpeed);
			}

			if(fBTerminalData[6]&0x08)
			{
				supportArmM->setErrorFlag_1(setSupportArmSpeed(-((int16_t)((fBTerminalData[6]&0x07)*1000))));
			}
			else
			{
				supportArmM->setErrorFlag_1(setSupportArmSpeed((int16_t)((fBTerminalData[6]&0x07)*1000)));
			}

			break;
		case AAAModel:
				xyzFlag=false;
				if(unlockArms(XBOT_AAAA_ARM0))//unlockArmsִ�н������
					allArmRunToPos(XBOT_AAAA_ARM1,XBOT_AAAA_ARM2,XBOT_AAAA_ARM3,XBOT_AAAA_ARM4,XBOT_AAAA_ARM5,XBOT_AAAA_ARM6,XBOT_AAAA_ARM7,XBOT_AAAA_ARM0);
			break;
		case BBBModel:
			xyzFlag=false;
			if(unlockArms(XBOT_BBBB_ARM0))
				allArmRunToPos(XBOT_BBBB_ARM1,XBOT_BBBB_ARM2,XBOT_BBBB_ARM3,XBOT_BBBB_ARM4,XBOT_BBBB_ARM5,XBOT_BBBB_ARM6,XBOT_BBBB_ARM7,XBOT_BBBB_ARM0);
			break;
			
		case CCCModel:
			xyzFlag=false;
			allArmRunToPos(XBOT_CCCC_ARM1,XBOT_CCCC_ARM2,XBOT_CCCC_ARM3,XBOT_CCCC_ARM4,XBOT_CCCC_ARM5,XBOT_CCCC_ARM6,XBOT_CCCC_ARM7,XBOT_CCCC_ARM0);
			if((bigArmPitchM->getSpeed()==0)&&(forearmPitchM->getSpeed()==0)&&(wristPitchM->getSpeed()==0))//������λ ֮�����������ؽڵ��г̿�Uģʽ���
			{
				if((ABS(XBOT_CCCC_ARM1-(fBbigArmRotateA->DATA_16))<50))//�����ת�ؽڵ���
				{
// 					if((-(fBbigArmPitchA->DATA_16)>350) || ((fBwristPitchA->DATA_16)>600) || ((fBforearmPitchA->DATA_16)>1200))
					{
						//���
						if(((XBOT_CCCC_ARM2-fBbigArmPitchA->DATA_16)>1000)&&(CCCUTime_1<10000))
						{
							bigArmPitchM->setPWMSpeed(22000);
							bigArmPitchM->resetUspeedTime();
							CCCUTime_1++;
						}
						else if(((XBOT_CCCC_ARM2-fBbigArmPitchA->DATA_16)>500)&&(CCCUTime_1<10000))//����3��
						{
							bigArmPitchM->setPWMSpeed(12000);
							bigArmPitchM->resetUspeedTime();
							CCCUTime_1++;
						}
						else if(!CCCUFlag_1)
						{
							bigArmPitchM->setPWMSpeed(10000);
							bigArmPitchM->resetUspeedTime();
							CCCUFlag_1=true;
						}
						
						//С��
						if(((fBforearmPitchA->DATA_16-XBOT_CCCC_ARM3)>1000)&&(CCCUTime_2<10000))
						{
							forearmPitchM->setPWMSpeed(-22000);
							forearmPitchM->resetUspeedTime();
							CCCUTime_2++;
						}
						else if(((fBforearmPitchA->DATA_16-XBOT_CCCC_ARM3)>500)&&(CCCUTime_2<10000))
						{
							forearmPitchM->setPWMSpeed(-12000);
							forearmPitchM->resetUspeedTime();
							CCCUTime_2++;
						}
						else if(!CCCUFlag_2)
						{
							forearmPitchM->setPWMSpeed(-10000);
							forearmPitchM->resetUspeedTime();
							CCCUFlag_2=true;
						}

						//����
						if(((fBwristPitchA->DATA_16-XBOT_CCCC_ARM4)>1000)&&(CCCUTime_3<10000))
						{
							wristPitchM->setPWMSpeed(-22000);
							wristPitchM->resetUspeedTime();
							CCCUTime_3++;
						}
						else if(((fBwristPitchA->DATA_16-XBOT_CCCC_ARM4)>500)&&(CCCUTime_3<10000))
						{
							wristPitchM->setPWMSpeed(-12000);
							wristPitchM->resetUspeedTime();
							CCCUTime_3++;
						}
						else if(!CCCUFlag_3)
						{
							wristPitchM->setPWMSpeed(-10000);
							wristPitchM->resetUspeedTime();
							CCCUFlag_3=true;
						}
					}
					/****
// 					else
// 					{
// 						//����һ��Uָ��
// 						if(CCCUFlag_1==false)
// 						{
// 							bigArmPitchM->setPWMSpeed(10000);
// 							bigArmPitchM->resetUspeedTime();
// 							CCCUFlag_1=true;
// 						}
// 						//����һ��Uָ��
// 						if(CCCUFlag_3==false)
// 						{
// 							wristPitchM->setPWMSpeed(-10000);
// 							wristPitchM->resetUspeedTime();
// 							CCCUFlag_3=true;
// 						}
// 						if(CCCUFlag_2==false)
// 						{
// 							forearmPitchM->setPWMSpeed(-10000);
// 							forearmPitchM->resetUspeedTime();
// 							CCCUFlag_2=true;
// 						}
// 					}
					
					//��һ������۸�������������λ,С�����е�10������
// 					if(XBOT_CCCC_ARM2-(fBbigArmPitchA->DATA_16)>300||(fBwristPitchA->DATA_16)-XBOT_CCCC_ARM4>300)//��ۻ�����û����//&&(fBforearmPitchA->DATA_16)-XBOT_CCCC_ARM3>1000)
// 					{
// 						//���
// 						if(XBOT_CCCC_ARM2-(fBbigArmPitchA->DATA_16)>600&&CCCUTime_1<10000)
// 						{
// 							bigArmPitchM->setPWMSpeed(22000);
// 							bigArmPitchM->resetUspeedTime();
// 							CCCUTime_1++;
// 						}
// 						else if(XBOT_CCCC_ARM2-(fBbigArmPitchA->DATA_16)>300&&CCCUTime_1<10000)//����3��
// 						{
// 							bigArmPitchM->setPWMSpeed(7000);
// 							bigArmPitchM->resetUspeedTime();
// 							CCCUTime_1++;
// 						}
// 						
// 						//С��
// 						if((fBforearmPitchA->DATA_16)-XBOT_CCCC_ARM3>1000)//&&CCCUTime_2<10000)
// 						{
// 							forearmPitchM->setPWMSpeed(-22000);
// 							forearmPitchM->resetUspeedTime();
// 						}
// 						else//С��10�� ֹͣ
// 						{
// 							forearmPitchM->setPWMSpeed(0);
// 							forearmPitchM->resetUspeedTime();
// 						}
// 						
// 						//����
// 						if((fBwristPitchA->DATA_16)-XBOT_CCCC_ARM4>600&&CCCUTime_3<10000)
// 						{
// 							wristPitchM->setPWMSpeed(-22000);
// 							wristPitchM->resetUspeedTime();
// 							CCCUTime_3++;
// 						}
// 						else if((fBwristPitchA->DATA_16)-XBOT_CCCC_ARM4>300&&CCCUTime_3<10000)
// 						{
// 							wristPitchM->setPWMSpeed(-8000);
// 							wristPitchM->resetUspeedTime();
// 							CCCUTime_3++;
// 						}
// 						
// 					}
// 					else //��ۺ�С�۶�����
// 					{
// 						//����һ��Uָ��
// 						if(CCCUFlag_1==false)
// 						{
// 							bigArmPitchM->setPWMSpeed(5000);
// 							bigArmPitchM->resetUspeedTime();
// 							CCCUFlag_1=true;
// 						}
// 						//����һ��Uָ��
// 						if(CCCUFlag_3==false)
// 						{
// 							wristPitchM->setPWMSpeed(-5000);
// 							wristPitchM->resetUspeedTime();
// 							CCCUFlag_3=true;
// 						}
// 						
// 						if((fBforearmPitchA->DATA_16)-XBOT_CCCC_ARM3>600&&CCCUTime_2<10000)
// 						{
// 							forearmPitchM->setPWMSpeed(-22000);
// 							forearmPitchM->resetUspeedTime();
// 							CCCUTime_2++;
// 						}
// 						else if((fBforearmPitchA->DATA_16)-XBOT_CCCC_ARM3>300&&CCCUTime_2<10000)
// 						{
// 							forearmPitchM->setPWMSpeed(-8000);
// 							forearmPitchM->resetUspeedTime();
// 							CCCUTime_2++;
// 						}
// 						else //����һ��Uָ��
// 						{
// 							if(CCCUFlag_2==false)
// 							{
// 								forearmPitchM->setPWMSpeed(-5000);
// 								forearmPitchM->resetUspeedTime();
// 								CCCUFlag_2=true;
// 							}
// 						}
// 					}
*/
				}
				else//�����תû�е���
				{
						if(bigArmRotateM->getSpeed()==0)
						{
							if(XBOT_CCCC_ARM1-(fBbigArmRotateA->DATA_16)<0)
							{
								bigArmRotateM->setSpeed(200);
							}
							else
							{
								bigArmRotateM->setSpeed(-200);
							}
						}
				}
			}
			else //if(fBforearmPitchA->DATA_16<500)//����
			{
				if(bigArmPitchM->getSpeed()!=0&&bigArmPitchM->getSpeed()<3000)
					bigArmPitchM->setSpeed(3000);
				
				if(forearmPitchM->getSpeed()!=0&&forearmPitchM->getSpeed()>-3000)
					forearmPitchM->setSpeed(-3000);
				
				if(wristPitchM->getSpeed()!=0&&wristPitchM->getSpeed()>-3000)
					wristPitchM->setSpeed(-3000);
				
				if(bigArmRotateM->getSpeed()>0&&bigArmRotateM->getSpeed()<500)
					bigArmRotateM->setSpeed(500);
				
				if(bigArmRotateM->getSpeed()<0&&bigArmRotateM->getSpeed()>-500)
					bigArmRotateM->setSpeed(-500);
				
				bigArmPitchM->setPWMSpeed(0);
				forearmPitchM->setPWMSpeed(0);
				wristPitchM->setPWMSpeed(0);
			}
			break;
		case DDDModel:
			xyzFlag=false;
			if(unlockArms(XBOT_DDDD_ARM0))
				allArmRunToPos(XBOT_DDDD_ARM1,XBOT_DDDD_ARM2,XBOT_DDDD_ARM3,XBOT_DDDD_ARM4,XBOT_DDDD_ARM5,XBOT_DDDD_ARM6,XBOT_DDDD_ARM7,XBOT_DDDD_ARM0);
			break;
		case EEEModel:
			xyzFlag=false;
			if(unlockArms(XBOT_EEEE_ARM0))
				allArmRunToPos(XBOT_EEEE_ARM1,XBOT_EEEE_ARM2,XBOT_EEEE_ARM3,XBOT_EEEE_ARM4,XBOT_EEEE_ARM5,XBOT_EEEE_ARM6,XBOT_EEEE_ARM7,XBOT_EEEE_ARM0);
			break;
		case HHHModel:
			suppArmRunToPos(XBOT_HHH_ARM0);
			break;
		case IIIModel:
			suppArmRunToPos(XBOT_III_ARM0);
			break;
		case JJJModel:
			suppArmRunToPos(XBOT_JJJ_ARM0);
			break;
		case KKKModel:
			suppArmRunToPos(XBOT_KKK_ARM0);
			break;
		case LLLModel:
			suppArmRunToPos(XBOT_LLL_ARM0);
			break;


		case MMMModel: //����ģʽ
#ifdef NEWOPTICALBOBBIN			
			//�ж��Ƿ�Ϊ����
			if(signalType==WIRE_WORK_MODE&&WireType==true)
			{
				if(opticalBobbinDevice->getWireLength()>5||limitFlag==false)//��ʣ���߳�����5�ף�������ȡ����λ��ģʽ����������
				{
					opticalBobbinDevice->setWorkStatus(0x05);
					opticalBobbinDevice->setLeftSpeed(0);
					opticalBobbinDevice->setRightSpeed(0);
				}
				else
				{
					opticalBobbinDevice->setWorkStatus(0x00);
					opticalBobbinDevice->setLeftSpeed(0);
					opticalBobbinDevice->setRightSpeed(0);
				}
			}
			else
#endif
			{
				panTiltRunToMMMModel();
			}
			break;
		case NNNModel: //����ģʽ
#ifdef NEWOPTICALBOBBIN			
			//�ж��Ƿ�Ϊ����
			if(signalType==WIRE_WORK_MODE&&WireType==true)
			{
				opticalBobbinDevice->setWorkStatus(0x06);
				opticalBobbinDevice->setLeftSpeed(0);
				opticalBobbinDevice->setRightSpeed(0);
			}
			else
#endif
			{
				fingerRunToNNNModel();
			}
			break;
		case SSSModel:
			stopAllMoter();
			break;
		case XLLModel:
			xyzFlag=false;
			runOnXXXLine(-5000*((fBTerminalData[7]&0x70)>>4)/0x09);
			break;
		case XRRModel:
			xyzFlag=false;
			runOnXXXLine(5000*((fBTerminalData[7]&0x70)>>4)/0x09);
			break;
		case YFFModel:
			xyzFlag=false;
			runOnYYYLine(-5000*(fBTerminalData[7]&0x07)/0x09);
			break;
		case YBBModel:
			xyzFlag=false;
			runOnYYYLine(5000*(fBTerminalData[7]&0x07)/0x09);
			break;
		case ZUUModel:
			xyzFlag=false;
			runOnZZZLine(5000*(fBTerminalData[5]&0x07)/0x0c);
			break;
		case ZDDModel:
			xyzFlag=false;
			runOnZZZLine(-5000*(fBTerminalData[5]&0x07)/0x0c);
			break;
		case XYZModel:
			XbotArmSetXyzCtrlMode();
			break;
	}
}

/**
  * ��  �ܣ���̨���е���λ״̬
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::panTiltRunToMMMModel()
{
		int a1=(int)fBbigArmRotateA->DATA_16;
		int a2=(int)fBbigArmPitchA->DATA_16;
		int a3=(int)fBforearmPitchA->DATA_16;
		int a4=(int)fBwristPitchA->DATA_16;
		int a5=(int)fBwristRotateA->DATA_16;
		int a6=(int)XBOT_AAAA_ARM6;
		int a7=(int)XBOT_AAAA_ARM7;
		int a8=(int)(fBDiscA->DATA_16);//֧�۵ĽǶȲ������
		allArmRunToPos(a1,a2,a3,a4,a5,a6,a7,a8);
	
}

/**
  * ��  �ܣ���ץ���е���λ״̬����ץ�г��˶���50�ȣ���ץ��ת�˶���0��
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::fingerRunToNNNModel()
{
	int temFingerMediateA =(int)fBfingerMediateA->DATA_16;//��ǰ����ץ�гֽǶ�
	int temWristRotateA =(int)fBwristRotateA->DATA_16;		//��ǰ����ץ��ת�Ƕ�
	int temSpeed=0;
	 
	if(temWristRotateA>0)//�������˶�
	{
		if(temWristRotateA>1000) //10������ȫ������
		{
			wristRotateM->setSpeed(-12000);
		}
		else if(temWristRotateA>200)//3��10�ȣ���������
		{
			wristRotateM->setSpeed(-6000);
		}
		else if(temWristRotateA>100) //1��2��,400�ٶ�����
		{
			wristRotateM->setSpeed(-400);
		}
		else//ֹͣ����
		{
			wristRotateM->resetSpeed();
		}
	}
	else//�������˶�
	{
		if(temWristRotateA<-1000) //10������ȫ������
		{
			wristRotateM->setSpeed(12000);
		}
		else if(temWristRotateA<-200)//3��10�ȣ���������
		{
			wristRotateM->setSpeed(6000);
		}
		else if(temWristRotateA<100) //1��2��,400�ٶ�����
		{
			wristRotateM->setSpeed(400);
		}
		else//ֹͣ����
		{
			wristRotateM->resetSpeed();
		}
	}
	if(temFingerMediateA>5050)//�������˶� 
	{
		if(temFingerMediateA>5500) //5������ȫ������
		{
			temSpeed=-9000;
		}
		else if(temFingerMediateA>5150)//3��5�ȣ���������
		{
			temSpeed=-4500;
		}
		else if(temFingerMediateA>5050) //1��2��,300�ٶ�����
		{
			temSpeed=-300;
		}
		else//ֹͣ����
		{
			temSpeed=0;
		}
	}
	else//�������˶�
	{
		if(temFingerMediateA<5000) //5������ȫ������
		{
			temSpeed=9000;
		}
		else if(temFingerMediateA<5300)//3��5�ȣ���������
		{
			temSpeed=4500;
		}
		else if(temFingerMediateA<5500) //1��2��,300�ٶ�����
		{
			temSpeed=300;
		}
		else//ֹͣ����
		{
			temSpeed=0;
		}
	}
	fingerMediateM->setErrorFlag_1(setFingerMediateSpeed(temSpeed));
}

/**
  * ��  �ܣ�֧�����е�ָ���Ƕ� �ٶȷ��ŵ��ٽ�Ƕ�Ϊ300��
  * ��  ����ָ���ĽǶ�
  * ����ֵ����
  * 
  */
#define MAXSUPPARMSPEED REFER_SPEED_MAX_ARM0

#define MIDDLESUPPARMSPEED 2000

#define MINSUPPARMSPEED 500

#define SUBANGLE_SUPP_1 20
#define SUBANGLE_SUPP_2 10
#define SUBANGLE_SUPP_3 4

#ifdef USEPOTENTIOMETER

void XbotApp::suppArmRunToPos(int angle,bool showError)
{
	int16_t temAngle=fBDiscA->DATA_16;														//��ȡ��ǰ�ĽǶ�
	int16_t subAngle=0;
	int temSpeed=0;
	if((angle>XBOT_CRITICAL_ARM0_DN&&angle<XBOT_CRITICAL_ARM0_UP)||(temAngle>XBOT_CRITICAL_ARM0_DN&&temAngle<XBOT_CRITICAL_ARM0_UP))	//ָ���ĽǶȻ��ߵ�ǰ�Ƕ���������Χ��
	{
		return;
	}
// 	if(CodedDisc->getErrorFlag()==0x08)														//�����豸��ʧ
// 		return;
	if(angle<=XBOT_CRITICAL_ARM0_DN)																	//ָ���ĽǶ�С�������ٽ�����
	{
		if(temAngle>=XBOT_CRITICAL_ARM0_UP&&temAngle<ARM0_ANGLE_360)	//��ǰ�Ƕ��������ٽ�������360֮�䣬�����˶�
		{
			subAngle=angle+ARM0_ANGLE_360-temAngle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=REFER_SPEED_MAX_ARM0;
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=MIDDLESUPPARMSPEED;
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=MINSUPPARMSPEED;
			}
			else
			{
				temSpeed=0;
			}
		}
		else if(temAngle>=ARM0_ANGLE_0&&temAngle<angle)						//��ǰ�Ƕ���0����ָ���Ƕ�֮�䣬�����˶�
		{
			subAngle=angle-temAngle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=REFER_SPEED_MAX_ARM0;
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=MIDDLESUPPARMSPEED;
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=MINSUPPARMSPEED;
			}
			else
			{
				temSpeed=0;
			}
		}
		else																											//��ǰ�Ƕ���ָ���Ƕ��������ٽ����޽Ƕ�֮�䣬�����˶�
		{
			subAngle=temAngle-angle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=(-REFER_SPEED_MAX_ARM0);
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=(-MIDDLESUPPARMSPEED);
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=(-MINSUPPARMSPEED);
			}
			else
			{
				temSpeed=0;
			}
		}
	}
	else 																												//ָ���ĽǶȴ��ڵ��������ٽ�����
	{
		if(temAngle>=XBOT_CRITICAL_ARM0_UP&&temAngle<angle)					//��ǰ�Ƕ��������ٽ�������ָ���Ƕ�֮�� �����˶�
		{
			subAngle=angle-temAngle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=(REFER_SPEED_MAX_ARM0);
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=(MIDDLESUPPARMSPEED);
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=(MINSUPPARMSPEED);
			}
			else
			{
				temSpeed=0;
// 				supportArmM->resetSpeed();
			}			
		}
		else if(temAngle>=angle&&temAngle<ARM0_ANGLE_360)					//��ǰ�Ƕ���ָ���Ƕ���360��֮�� �����˶�
		{
			subAngle=temAngle-angle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=(-REFER_SPEED_MAX_ARM0);
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=(-MIDDLESUPPARMSPEED);
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=(-MINSUPPARMSPEED);
			}
			else
			{
				temSpeed=0;
			}
		}
		else 																											//��ǰ�Ƕ���0���������ٽ�����֮�� �����˶�
		{
			subAngle=angle-temAngle;
			if(subAngle>SUBANGLE_SUPP_1)
			{
				temSpeed=(-REFER_SPEED_MAX_ARM0);
			}
			else if(subAngle>SUBANGLE_SUPP_2)
			{
				temSpeed=(-MIDDLESUPPARMSPEED);
			}
			else if(subAngle>SUBANGLE_SUPP_3)
			{
				temSpeed=(-MINSUPPARMSPEED);
			}
// 			else if(subAngle>2)
// 			{
// 				temSpeed=(-200);
// 			}
			else
			{
				temSpeed=0;
			}
		}
	}
	if(showError)
		supportArmM->setErrorFlag_1(setSupportArmSpeed(temSpeed));
	else
		setSupportArmSpeed(temSpeed);
}

#else

void XbotApp::suppArmRunToPos(int angle,bool showError)
{
	int16_t temAngle=fBDiscA->DATA_16;													//��ȡ��ǰ�ĽǶ�
	int16_t subAngle=0;
	int temSpeed=0;
	if(CodedDisc->getErrorFlag()==0x08)													//�����豸��ʧ
		return;
	if(angle<XBOT_CRITICAL_ARM0)																//ָ���ĽǶ�С���ٽ�Ƕ�
	{
		if(temAngle>=XBOT_CRITICAL_ARM0&&temAngle<ARM0_ANGLE_360)	//��ǰ�Ƕ����ٽ�Ƕ���360֮�䣬�����˶�
		{
			subAngle=angle+ARM0_ANGLE_360-temAngle;
			if(subAngle>100)
			{
				temSpeed=5000;
			}
			else if(subAngle>50)
			{
				temSpeed=4500;
			}
			else if(subAngle>10)
			{
				temSpeed=1000;
			}
			else if(subAngle>5)
			{
				temSpeed=500;
			}
			else if(subAngle>2)
			{
				temSpeed=200;
			}
			else
			{
				temSpeed=0;
			}
		}
		else if(temAngle>ARM0_ANGLE_0&&temAngle<angle)						//��ǰ�Ƕ���0����ָ���Ƕ�֮�䣬�����˶�
		{
			subAngle=angle-temAngle;
			if(subAngle>100)
			{
				temSpeed=5000;
			}
			else if(subAngle>50)
			{
				temSpeed=4500;
			}
			else if(subAngle>10)
			{
				temSpeed=1000;
			}
			else if(subAngle>5)
			{
				temSpeed=500;
			}
			else if(subAngle>2)
			{
				temSpeed=200;
			}
			else
			{
				temSpeed=0;
			}
		}
		else																											//��ǰ�Ƕ���ָ���Ƕ����ٽ�Ƕ�֮�䣬�����˶�
		{
			subAngle=temAngle-angle;
			if(subAngle>100)
			{
				temSpeed=(-5000);
			}
			else if(subAngle>50)
			{
				temSpeed=(-4500);
			}
			else if(subAngle>10)
			{
				temSpeed=(-1000);
			}
			else if(subAngle>5)
			{
				temSpeed=(-500);
			}
			else if(subAngle>2)
			{
				temSpeed=(-200);
			}
			else
			{
				temSpeed=0;
			}
		}
	}
	else 																												//ָ���ĽǶȴ����ٽ�Ƕ�
	{
		if(temAngle>=XBOT_CRITICAL_ARM0&&temAngle<angle)					//��ǰ�Ƕ����ٽ�Ƕ���ָ���Ƕ�֮�� �����˶�
		{
			subAngle=angle-temAngle;
			if(subAngle>100)
			{
				temSpeed=(5000);
			}
			else if(subAngle>50)
			{
				temSpeed=(4500);
			}
			else if(subAngle>10)
			{
				temSpeed=(1000);
			}
			else if(subAngle>5)
			{
				temSpeed=(500);
			}
			else if(subAngle>2)
			{
				temSpeed=(200);
			}
			else
			{
				supportArmM->resetSpeed();
			}			
		}
		else if(temAngle>=angle&&temAngle<ARM0_ANGLE_360)					//��ǰ�Ƕ���ָ���Ƕ���360��֮�� �����˶�
		{
			subAngle=temAngle-angle;
			if(subAngle>100)
			{
				temSpeed=(-5000);
			}
			else if(subAngle>50)
			{
				temSpeed=(-4500);
			}
			else if(subAngle>10)
			{
				temSpeed=(-1000);
			}
			else if(subAngle>5)
			{
				temSpeed=(-500);
			}
			else if(subAngle>2)
			{
				temSpeed=(-200);
			}
			else
			{
				temSpeed=0;
			}
		}
		else 																											//��ǰ�Ƕ���0�����ٽ�Ƕ�֮�� �����˶�
		{
			subAngle=angle-temAngle;
			if(subAngle>100)
			{
				temSpeed=(-5000);
			}
			else if(subAngle>50)
			{
				temSpeed=(-4500);
			}
			else if(subAngle>10)
			{
				temSpeed=(-1000);
			}
			else if(subAngle>5)
			{
				temSpeed=(-500);
			}
			else if(subAngle>2)
			{
				temSpeed=(-200);
			}
			else
			{
				temSpeed=0;
			}
		}
	}
	if(showError)
		supportArmM->setErrorFlag_1(setSupportArmSpeed(temSpeed));
	else
		setSupportArmSpeed(temSpeed);
}
#endif

/**
  * ��  �ܣ�������ȡ֧�۵ĽǶȲ� ���ص���1024/4096�ƵĽǶ�
  * ��  ����ָ������ĽǶ�
  * ����ֵ����ǰ�Ƕ���ָ���ǶȵĲ�
  * 
  */
#ifdef USEPOTENTIOMETER

int16_t XbotApp::getSuppArmSubAngle(int angle)
{
	int16_t temAngle=fBDiscA->DATA_16;													//��ȡ��ǰ�ĽǶ� 4096��
	int16_t subAngle=0;
	if((angle>XBOT_CRITICAL_ARM0_DN&&angle<XBOT_CRITICAL_ARM0_UP)||(temAngle>XBOT_CRITICAL_ARM0_DN&&temAngle<XBOT_CRITICAL_ARM0_UP))	//ָ���ĽǶȻ��ߵ�ǰ�Ƕ���������Χ��
	{
		return 0;
	}	

	if(angle<=XBOT_CRITICAL_ARM0_DN)																//ָ���ĽǶ�С�ڵ����ٽ�Ƕ�����
	{
		if(temAngle>=XBOT_CRITICAL_ARM0_UP&&temAngle<ARM0_ANGLE_360)	//��ǰ�Ƕ����ٽ�Ƕ�������360֮�䣬�����˶�
		{
			subAngle=angle+ARM0_ANGLE_360-temAngle;
		}
		else
		{
			subAngle=angle-temAngle;
		}
	}
	else 																														//ָ���ĽǶȴ��ڵ����ٽ�Ƕ�����
	{
		if(temAngle>=XBOT_CRITICAL_ARM0_UP&&temAngle<ARM0_ANGLE_360)	//��ǰ�Ƕ����ٽ�Ƕ�������360֮��
		{
			subAngle=angle-temAngle;
		}
		else 																													//��ǰ�Ƕ���0�����ٽ�Ƕ�����֮�� �����˶�
		{
			subAngle=angle-temAngle-ARM0_ANGLE_360;
		}
	}
	return subAngle;
}
#else
int16_t XbotApp::getSuppArmSubAngle(int angle)
{
	int16_t temAngle=fBDiscA->DATA_16;													//��ȡ��ǰ�ĽǶ� 1024��
	int16_t subAngle=0;
	if(angle<XBOT_CRITICAL_ARM0)																//ָ���ĽǶ�С���ٽ�Ƕ�
	{
		if(temAngle>=XBOT_CRITICAL_ARM0&&temAngle<ARM0_ANGLE_360)	//��ǰ�Ƕ����ٽ�Ƕ���360֮�䣬�����˶�
		{
			subAngle=angle+ARM0_ANGLE_360-temAngle;
		}
		else
		{
			subAngle=angle-temAngle;
		}
	}
	else 																												//ָ���ĽǶȴ����ٽ�Ƕ�
	{
		if(temAngle>=XBOT_CRITICAL_ARM0&&temAngle<ARM0_ANGLE_360)	//��ǰ�Ƕ����ٽ�Ƕ���ָ���Ƕ�֮��
		{
			subAngle=angle-temAngle;
		}
		else 																											//��ǰ�Ƕ���0�����ٽ�Ƕ�֮�� �����˶�
		{
			subAngle=angle-temAngle-ARM0_ANGLE_360;
		}
	}
	return subAngle;
}
#endif



/**
  * ��  �ܣ��������ݽǶȲ��ʱ�������֧�۵��ٶȣ�֧�۱Ƚ����⣬�˶�������趨Ҫ�����ٽ�Ƕ�
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::setSuppArmspeed(int subA,int sunT,int sunMaxT)
{
	if(ABS(subA)>100)//����� ��1 ��
	{
		if(ABS(subA)>1000)
			setSupportArmSpeed((int16_t)(5000*sunT/sunMaxT));
		else if(ABS(subA)>500)
			supportArmM->setSpeed((int16_t)(3500*sunT/sunMaxT));
		else if(ABS(subA)>300)
			setSupportArmSpeed((int16_t)(((int32_t)2250)*sunT/sunMaxT));
		else
			setSupportArmSpeed((int16_t)(((int32_t)600)*sunT/sunMaxT));
	}
	else								//�ٶ���0
	{
		supportArmM->resetSpeed();
	}
}


/**
  * ��  �ܣ����йؽ����е�ָ���Ƕȣ�����ǰ���������ץץ�ֹؽ�
  * ��  ����ָ���ĽǶ�
					angle_1�������ת
					angle_2����۸���
					angle_3��С�۸���
					angle_4��������
					angle_5��������ת
					angle_6����̨����
					angle_7����̨��ת
					angle_8��֧�۸���
  * ����ֵ����
  * ��  ע������ͬ������ķ�ʽ�����ĳЩ�ؽڷ���������λ����ùؽڵȴ���Ӧ�ĸ���Դ�ؽڵ���Ǹ���λ�ú�����˶�
  */
void XbotApp::allArmRunToPos(int angle_1,int angle_2,int angle_3,int angle_4,int angle_5,int angle_6,int angle_7,int angle_8)
{
	int subAngle[8]={0};
	int subtime[8]={0};
	int subMaxTime=0;
	//�����豸���˾Ͳ���������
// 	if(checkBlockError()==false)													//û�е����ת
	{
		subAngle[0]=(angle_1-(int)fBbigArmRotateA->DATA_16);
		subAngle[1]=(angle_2-(int)fBbigArmPitchA->DATA_16);
		subAngle[2]=(angle_3-(int)fBforearmPitchA->DATA_16);
		subAngle[3]=(angle_4-(int)fBwristPitchA->DATA_16);
		subAngle[4]=(angle_5-(int)fBwristRotateA->DATA_16);
		subAngle[5]=(angle_6-(int)fBpanTiltPitchA->DATA_16);
		subAngle[6]=(angle_7-(int)fBpanTiltRotateA->DATA_16);
// 		subAngle[7]=((int)getSuppArmSubAngle(angle_8))*1125/32;//֧�۵ĽǶȲ������
		subAngle[7]=angle_8;
		//ʱ���Ϊ�ǶȲ���ٶ�ϵ�������ٱȣ��ĳ˻� �����ٱ�Խ��ʱ��Խ��������ٶ�Խ�� ʱ��Խ��
		subtime[0]=subAngle[0]*SPEED_COEFFICIENT_ARM1;
		subtime[1]=subAngle[1]*SPEED_COEFFICIENT_ARM2;
		subtime[2]=subAngle[2]*SPEED_COEFFICIENT_ARM3;
		subtime[3]=subAngle[3]*SPEED_COEFFICIENT_ARM4;
		subtime[4]=subAngle[4]*SPEED_COEFFICIENT_ARM5;
		subtime[5]=subAngle[5]*SPEED_COEFFICIENT_ARM6;
		subtime[6]=subAngle[6]*SPEED_COEFFICIENT_ARM7;
// 		subtime[7]=subAngle[7]*SPEED_COEFFICIENT_ARM0;
		subtime[7]=0;
		subMaxTime=maxTime(subtime);
		
		suppArmRunToPos(subAngle[7],false); //�˴�һ��Ҫ���ϸ�ָ��֮��
		
		if(subMaxTime==0||limitFlag==false)//����λ״̬�²�ִ��
			return;

// 	setSuppArmspeed(subAngle[7],subtime[7],subMaxTime);
		panTiltRotateM->	setSpeedFromSubAngle(subAngle[6],subtime[6],subMaxTime);
		panTiltPitchM->		setSpeedFromSubAngle(setPanTiltPitchSpeed,subAngle[5],subtime[5],subMaxTime);	
		wristRotateM->		setSpeedFromSubAngle(subAngle[4],subtime[4],subMaxTime);
		wristPitchM->			setSpeedFromSubAngle(setWristPitchSpeed,subAngle[3],subtime[3],subMaxTime);
		forearmPitchM->		setSpeedFromSubAngle(setForearmPitchSpeed,subAngle[2],subtime[2],subMaxTime);
		bigArmPitchM->		setSpeedFromSubAngle(setBigArmPitchSpeed,subAngle[1],subtime[1],subMaxTime);
		bigArmRotateM->		setSpeedFromSubAngle(setBigArmRotateSpeed,subAngle[0],subtime[0],subMaxTime);
	}
	checkBlockError();
}
/**
  * ��  �ܣ������ת����۸�����С�۸��������ؽ����е�ָ��λ��
  * ��  ����ָ���ĽǶ�
					angle_1�������ת
					angle_2����۸���
					angle_3��С�۸���
					speed	 ���ٶ�

  * ����ֵ����
  * ��  ע������ͬ������ķ�ʽ�����ĳЩ�ؽڷ���������λ����ùؽڵȴ���Ӧ�ĸ���Դ�ؽڵ���Ǹ���λ�ú�����˶�
  */
void XbotApp::threeArmRunToPos(int angle_1,int angle_2,int angle_3,int speed)
{
	int subAngle[3]={0};
	int subtime[3]={0};
	int subMaxTime=0;
	//�����豸���˾Ͳ���������
// 	if(CodedDisc->getErrorFlag()==0x00)													//�����豸����
	{
		subAngle[0]=(angle_1-(int)fBbigArmRotateA->DATA_16);
		subAngle[1]=(angle_2-(int)fBbigArmPitchA->DATA_16);
		subAngle[2]=(angle_3-(int)fBforearmPitchA->DATA_16);


		//ʱ���Ϊ�ǶȲ���ٶ�ϵ�������ٱȣ��ĳ˻� �����ٱ�Խ��ʱ��Խ��������ٶ�Խ�� ʱ��Խ��
		subtime[0]=subAngle[0]*SPEED_COEFFICIENT_ARM1;
		subtime[1]=subAngle[1]*SPEED_COEFFICIENT_ARM2;
		subtime[2]=subAngle[2]*SPEED_COEFFICIENT_ARM3;

		subMaxTime=maxTime_1(subtime);
		if(subMaxTime==0||limitFlag==false)//����λ״̬�²�ִ��
			return;
		forearmPitchM->		setSpeedFromSubAngle_1(subAngle[2],subtime[2]*ABS(speed)/7,subMaxTime);
		bigArmPitchM->		setSpeedFromSubAngle_1(subAngle[1],subtime[1]*ABS(speed)/7,subMaxTime);
		bigArmRotateM->		setSpeedFromSubAngle_1(subAngle[0],subtime[0]*ABS(speed)/7,subMaxTime);
	}
}
/**
  * ��  �ܣ�����ĵ�λʱ��,�������ٶ�Ԥ������
  * ��  ���������ʱ�������
  * ����ֵ������ʱ��
  * 
  */
int XbotApp::maxTime(int *data)
{
	int *temData=data;
	int32_t max=0;
	
//ģ�������ٶȣ�����Ƿ���λ
	if((data[0]==0)||((data[0]>0?setBigArmRotateSpeed(1000):setBigArmRotateSpeed(-1000))!=0))
		data[0]=0;
	setBigArmRotateSpeed(0);
	
	if((data[1]==0)||((data[1]>0?setBigArmPitchSpeed(1000):setBigArmPitchSpeed(-1000))!=0))
		data[1]=0;
	setBigArmPitchSpeed(0);
	
	if((data[2]==0)||((data[2]>0?setForearmPitchSpeed(1000):setForearmPitchSpeed(-1000))!=0))
		data[2]=0;
	setForearmPitchSpeed(0);
	
	if((data[3]==0)||((data[3]>0?setWristPitchSpeed(1000):setWristPitchSpeed(-1000))!=0))
		data[3]=0;
	setWristPitchSpeed(0);
	
// 	if((data[4]>0?setBigArmRotateSpeed(1000):setBigArmRotateSpeed(-1000))!=0)
// 		data[4]=0;
	
	if((data[5]==0)||((data[5]>0?setPanTiltPitchSpeed(1000):setPanTiltPitchSpeed(-1000))!=0))
		data[5]=0;
	setPanTiltPitchSpeed(0);
	
// 	if((data[6]>0?setBigArmRotateSpeed(1000):setBigArmRotateSpeed(-1000))!=0)
// 		data[6]=0;
// 	
	if((data[7]==0)||((data[7]>0?setSupportArmSpeed(1000):setSupportArmSpeed(-1000))!=0))
		data[7]=0;
	setSupportArmSpeed(0);
	
	max=MAX(temData[0],temData[1]);
	max=MAX(max,temData[2]);
	max=MAX(max,temData[3]);
	max=MAX(max,temData[4]);
	max=MAX(max,temData[5]);
	max=MAX(max,temData[6]);
	max=MAX(max,temData[7]);
	return max;
}

/**
  * ��  �ܣ�����ĵ�λʱ��,������άģʽ
  * ��  ���������ʱ�������
  * ����ֵ������ʱ��
  * 
  */
int XbotApp::maxTime_1(int *data)
{
	int *temData=data;
	int32_t max=0;
	max=MAX(temData[0],temData[1]);
	max=MAX(max,temData[2]);
	return max;
}

/**
  * ��  �ܣ�ֹͣ���еĵ��
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::stopAllMoter()
{
	leftRunM->resetSpeed();						//�н�����
	rightRunM->resetSpeed();					//�н��ҵ��
	supportArmM->resetSpeed();				//֧�۵��
	bigArmRotateM->resetSpeed();			//�����ת���
	bigArmPitchM->resetSpeed(); 			//��۸������
	forearmPitchM->resetSpeed();			//С�۸������
	wristPitchM->resetSpeed();				//���������
	wristRotateM->resetSpeed();				//������ת���
	panTiltPitchM->resetSpeed();			//��̨�������
	panTiltRotateM->resetSpeed();			//��̨��ת���
	fingerMediateM->resetSpeed();			//��צ��ϵ��
	cameraPitchM->resetSpeed();				//����������
}


/**
  * ��  �ܣ��������������ٶ�
  * ��  �����趨���ٶȵĲο�ֵ
  * ����ֵ��
  * 0�������ٶ�����
  * 1������̨�����ؽ� �����ĸ�����λ
  * 2�����︺����������λ
  * 3����С�۸����Ƕ�̫С �����ĸ�����λ
  * 4������С�۸����ǶȽ�С �����˶���������צ�����������λ
  * 5������������������λ
  * 6����צ�����ĸ�����λ
  */
uint8_t XbotApp::setWristPitchSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;																					//״̬������־
	int16_t temForearmPitchAngle=fBforearmPitchA->DATA_16;			
	int16_t temWristAngle=fBwristPitchA->DATA_16;									//����Ƕ�
	int16_t temPanTiltPitchAngle=fBpanTiltPitchA->DATA_16;				//��̨�Ƕ�
	int16_t temFingerMediateAngle=fBfingerMediateA->DATA_16;			//��ץ���ϽǶ�
	if(temSpeed==0)
	{
		wristPitchM->resetSpeed();
		return statusFlag;
	}
	if(limitFlag)
	{
		if(temSpeed<0)//�������˶�
		{
			if(temPanTiltPitchAngle<11800)
			{
					if(temWristAngle>2500)
						wristPitchM->setSpeed(temSpeed);
					else if(temWristAngle>2100)
						wristPitchM->setSpeed(temSpeed/3);
					else if(temWristAngle>2000)
					{
						wristPitchM->setSpeed(-200);
						statusFlag=1;									//����̨�����ؽ� �����ĸ�����λ
					}
					else
					{
						wristPitchM->resetSpeed();
						statusFlag=1;									//����̨�����ؽ� �����ĸ�����λ
					}
			}
			else
			{
					if(temWristAngle>1400)
						wristPitchM->setSpeed(temSpeed);
					else if(temWristAngle>1000)
						wristPitchM->setSpeed(temSpeed/3);
					else if(temWristAngle>900)
					{
						wristPitchM->setSpeed(-200);
						statusFlag=2;									//���︺����������λ
					}
					else
					{
						wristPitchM->resetSpeed();
						statusFlag=2;									//���︺����������λ
					}
			}
		}
		else	//�������˶�
		{
			if(temForearmPitchAngle<3500)
			{
// 				if(temWristAngle<4600)
// 				{
					if(temForearmPitchAngle<1400)
					{
						wristPitchM->resetSpeed();//��С�۸����Ƕ�̫С �����ĸ�����λ
						statusFlag=3;	
					}
					else
					{
						if(temWristAngle<4000)
							wristPitchM->setSpeed(temSpeed);
						else if(temWristAngle<4400)
							wristPitchM->setSpeed(temSpeed/3);
						else if(temWristAngle<4500)
						{
							wristPitchM->setSpeed(200);
							statusFlag=4;	
						}
						else
						{
							wristPitchM->resetSpeed();//����С�۸����ǶȽ�С �����˶���������צ�����������λ
							statusFlag=4;	
						}
					}
// 				}
// 				else //��̬����
// 				{
// 					if(temForearmPitchAngle<temWristAngle-3500)
// 					{
// 						wristPitchM->resetSpeed();
// 					}
// 					else
// 					{
// 						if(temWristAngle<temForearmPitchAngle+3000)
// 							wristPitchM->setSpeed(temSpeed);
// 						else if(temWristAngle<temForearmPitchAngle+3400)
// 							wristPitchM->setSpeed(temSpeed/3);
// 						else if(temWristAngle<temForearmPitchAngle+3500)
// 							wristPitchM->setSpeed(200);
// 						else
// 							wristPitchM->resetSpeed();
// 					}
// 				}
			}
			else 
			{
				if(temFingerMediateAngle<1100)
				{
					if(temWristAngle<17500)
						wristPitchM->setSpeed(temSpeed);
					else if(temWristAngle<17800)
						wristPitchM->setSpeed(temSpeed/3);
					else if(temWristAngle<17900)
					{
						wristPitchM->setSpeed(200);
						statusFlag=5;							 //����������������λ
					}
					else
					{
						wristPitchM->resetSpeed();
						statusFlag=5;							 //����������������λ
					}
				}
				else
				{
					if(temWristAngle<13300)
						wristPitchM->setSpeed(temSpeed);
					else if(temWristAngle<13700)
						wristPitchM->setSpeed(temSpeed/3);
					else if(temWristAngle<13800)
					{
						wristPitchM->setSpeed(200);
						statusFlag=6;							 //��צ�����ĸ�����λ
					}
					else
					{
						wristPitchM->resetSpeed();
						statusFlag=6;							 //��צ�����ĸ�����λ
					}
				}
			}
		}
	}
	else
	{
		wristPitchM->setSpeed(temSpeed);
	}
	return statusFlag;
}

/**
  * ��  �ܣ�������̨�������ٶ�
  * ��  �����趨���ٶȵĲο�ֵ
  * ����ֵ��
  *	 	0�����������ٶ�
  * 	1���������ǶȽ�С ������λ����
  *		2����̨���������������λ
  *		3����̨���������������λ
  */
uint8_t XbotApp::setPanTiltPitchSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;																					//״̬������־
	int16_t temWristPitchAngle=fBwristPitchA->DATA_16;					  //����Ƕ�
	int16_t temPanTiltPitchAngle=fBpanTiltPitchA->DATA_16;				//��̨�Ƕ�
	if(temSpeed==0)
	{
		panTiltPitchM->resetSpeed();
		return statusFlag;
	}
	
	if(limitFlag)
	{
		if(temSpeed>0)//�������˶�
		{
			if(temPanTiltPitchAngle<17400)//
				panTiltPitchM->setSpeed(temSpeed);
			else if(temPanTiltPitchAngle<17700)
				panTiltPitchM->setSpeed(temSpeed/2);
			else if(temPanTiltPitchAngle<17900)
			{
				panTiltPitchM->setSpeed(temSpeed/3);
				statusFlag=3;//����ﵽ�����������λ
			}
			else
			{
					panTiltPitchM->resetSpeed();
					statusFlag=3;//����ﵽ�����������λ
			}
		}
		else
		{
			if(temWristPitchAngle<1900)
			{
				if(temPanTiltPitchAngle>12500)
					panTiltPitchM->setSpeed(temSpeed);
				else if(temPanTiltPitchAngle>12100)
					panTiltPitchM->setSpeed(temSpeed/3);
				else if(temPanTiltPitchAngle>12000)
				{
					panTiltPitchM->setSpeed(200);
					statusFlag=1;//�������ǶȽ�С ������λ����
				}
				else
				{
					panTiltPitchM->resetSpeed();
					statusFlag=1;//�������ǶȽ�С ������λ����
				}
			}
			else
			{
				if(temPanTiltPitchAngle>-2300)
				{
					panTiltPitchM->setSpeed(temSpeed);
				}
				else if(temPanTiltPitchAngle>-2700)
				{
					panTiltPitchM->setSpeed(temSpeed/2);
				}
				else if(temPanTiltPitchAngle>-2900)
				{
					panTiltPitchM->setSpeed(temSpeed/3);
					statusFlag=2;//�������Ƕȴﵽ��������λ
				}
				else
				{
					panTiltPitchM->resetSpeed();
					statusFlag=2;//�������Ƕȴﵽ��������λ
				}
			}
		}
	}
	else//����λ
	{
		panTiltPitchM->setSpeed(temSpeed);
	}
	return statusFlag;
}


/**
  * ��  �ܣ�������ץ�г��ٶ�
  * ��  �����趨���ٶȵĲο�ֵ
  * ����ֵ��
  * 0�������Ƕȸ�ֵ
  * 1: ��צ�гֵ��︺����������λ
  * 2: ��צ�гֵ���������������λ
  * 3: ��צ������������
  */
uint8_t XbotApp::setFingerMediateSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;
	int16_t temWristAngle=fBwristPitchA->DATA_16;									//����Ƕ�
	int16_t temFingerMediateAngle=fBfingerMediateA->DATA_16;			//��ץ���ϽǶ�
	
	if(temSpeed==0)
	{
		fingerMediateM->resetSpeed();
		return statusFlag;
	}
	
	if(!limitFlag)
	{
		fingerMediateM->setSpeed(temSpeed);
		return statusFlag;
	}
	if(temSpeed<0)
	{
		if(temFingerMediateAngle>500)
			fingerMediateM->setSpeed(temSpeed);
		else if(temFingerMediateAngle>200)
			fingerMediateM->setSpeed(temSpeed/3);
		else if(temFingerMediateAngle>0)
		{
			fingerMediateM->setSpeed(-200);
			statusFlag=1;//��צ�гֵ��︺����������λ
		}
		else
		{
			fingerMediateM->resetSpeed();
			statusFlag=1;//��צ�гֵ��︺����������λ
		}
	}
	else
	{
		if(temWristAngle<13900)
		{
			if(temFingerMediateAngle<7950)
				fingerMediateM->setSpeed(temSpeed);
			else if(temFingerMediateAngle<8250)
				fingerMediateM->setSpeed(temSpeed/3);
			else if(temFingerMediateAngle<8350)
			{
				fingerMediateM->setSpeed(200);
				statusFlag=2;//��צ�гֵ���������������λ
			}
			else
			{
				fingerMediateM->resetSpeed();
				statusFlag=2;//��צ�гֵ���������������λ
			}
		}
		else
		{
			if(temFingerMediateAngle<500)
				fingerMediateM->setSpeed(temSpeed);
			else if(temFingerMediateAngle<900)
				fingerMediateM->setSpeed(temSpeed/3);
			else if(temFingerMediateAngle<1000)
			{
				fingerMediateM->setSpeed(200);
				statusFlag=3;//��צ������������
			}
			else
			{
				fingerMediateM->resetSpeed();
				statusFlag=3;//��צ������������
			}
		}
	}
	return statusFlag;
}

/**
  * ��  �ܣ�����С�۸����Ƕ�
  * ��  �����趨���ٶȵĲο�ֵ
  * ����ֵ��
  * 0�������ĽǶȸ�ֵ
  * 1: С�۸������︺�������С��λ
  * 2: С�۸������������ؽڸ���
  * 3: �������ؽڽǶ�̫С С�۸�������λ
  */
uint8_t XbotApp::setForearmPitchSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;
	int16_t temForearmPitchAngle=fBforearmPitchA->DATA_16;				//С�۽Ƕ�
	int16_t temWristAngle=fBwristPitchA->DATA_16;									//����Ƕ�
	if(temSpeed==0)
	{
		forearmPitchM->resetSpeed();
		return statusFlag;
	}
	if(!limitFlag)
	{
		forearmPitchM->setSpeed(temSpeed);
		return statusFlag;
	}
	if(temSpeed<0)
	{
		if(temWristAngle<4600)
		{
			if(temForearmPitchAngle>2500)
				forearmPitchM->setSpeed(temSpeed);
			else if(temForearmPitchAngle>2100)
				forearmPitchM->setSpeed(temSpeed/3);
			else if(temForearmPitchAngle>2000)
			{
				forearmPitchM->setSpeed(-200);
				statusFlag=1;//С�۸������︺�������С��λ
			}
			else
			{
				forearmPitchM->resetSpeed();
				statusFlag=1;//С�۸������︺�������С��λ
			}
		}
		else
		{
			if(temForearmPitchAngle>4200)
				forearmPitchM->setSpeed(temSpeed);
			else if(temForearmPitchAngle>3700)
				forearmPitchM->setSpeed(temSpeed/3);
			else if(temForearmPitchAngle>3600)
			{
				forearmPitchM->setSpeed(-200);
				statusFlag=2;
			}
			else
			{
				forearmPitchM->resetSpeed();//С�۸������������ؽڸ���
				statusFlag=2;
			}
		}
	}
	else
	{
		if(temWristAngle<600||temForearmPitchAngle<800)
		{
			forearmPitchM->resetSpeed();//�������ؽڽǶ�̫С С�۸�������λ
			statusFlag=3;
			return statusFlag;
		}
		
		if(temForearmPitchAngle<17500)
			forearmPitchM->setSpeed(temSpeed);
		else if(temForearmPitchAngle<17800)
			forearmPitchM->setSpeed(temSpeed/3);
		else if(temForearmPitchAngle<17900)
		{
			forearmPitchM->setSpeed(200);
			statusFlag=4;//С�۸������������������λ
		}
		else
		{
			forearmPitchM->resetSpeed();
			statusFlag=4;//С�۸������������������λ
		}
	}
	return statusFlag;
}

/**
  * ��  �ܣ����ô�۸����Ƕ�
  * ��  �����趨���ٶȵĲο�ֵ
  * ����ֵ��
	* 0���������ٶȸ�ֵ
  * 1��С��̫�Ͳ����Ĵ�۸�����λ
  * 2����۸������︺����������λ
  * 3���ɰ��ֲ����ĸ�������λ
  * 4������֧��δ֧�ز�������λ
  * 5����۵������ĽǶ���λ
  * 6���ɰ��ֲ�������������λ
  */
uint8_t XbotApp::setBigArmPitchSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;
	uint16_t temSupportArmAngle=(uint16_t)((int32_t)(fBDiscA->DATA_16)*1125/32);		//֧�۸����Ƕ�
	int16_t temBigArmPitchAngle=fBbigArmPitchA->DATA_16;				//��۸����Ƕ�
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;			//�����ת�Ƕ�
	int16_t temForearmPitchAngle=fBforearmPitchA->DATA_16;				//С�۽Ƕ�
	
	if(temSpeed==0)
	{
		bigArmPitchM->resetSpeed();
		return statusFlag;
	}
	if(!limitFlag)
	{
		bigArmPitchM->setSpeed(temSpeed);
		return statusFlag;
	}
	if(temSpeed<0)//̧��
	{
		if(temForearmPitchAngle<1400)//С��̫��
		{
			bigArmPitchM->resetSpeed(); //С��̫�Ͳ����Ĵ�۸�����λ
			statusFlag=1;
			return statusFlag;
		}
		if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32-300)&&temSupportArmAngle<(ARM0_ANGLE_270*1125/32+300))//֧�۳�����
		{
			if(temBigArmRotateAngle<1800&&temBigArmRotateAngle>-3600)//�����ת�ڰ�ȫ����
			{
				if(temBigArmPitchAngle>-17500)
					bigArmPitchM->setSpeed(temSpeed);
				else if(temBigArmPitchAngle>-17800)
					bigArmPitchM->setSpeed(temSpeed/3);
				else if(temBigArmPitchAngle>-17900)
				{
					bigArmPitchM->setSpeed(-200);
					statusFlag=2;
				}
				else
				{
					bigArmPitchM->resetSpeed();//��۸������︺����������λ
					statusFlag=2;
				}
			}
			else//�ǰ�ȫ���� ֻ��̧��162��
			{
				if(temBigArmPitchAngle>-15700)
					bigArmPitchM->setSpeed(temSpeed);
				else if(temBigArmPitchAngle>-16100)
					bigArmPitchM->setSpeed(temSpeed/3);
				else if(temBigArmPitchAngle>-16200)
				{
					bigArmPitchM->setSpeed(-200);
					statusFlag=3;
				}
				else
				{
					bigArmPitchM->resetSpeed();//�ɰ��ֲ����ĸ�������λ
					statusFlag=3;
				}
			}
		}
		else //֧��δ���� ֻ��̧�ߵ�50������
		{
			if(temBigArmPitchAngle>-4450)
				bigArmPitchM->setSpeed(temSpeed);
			else if(temBigArmPitchAngle>-4850)
				bigArmPitchM->setSpeed(temSpeed/3);
			else if(temBigArmPitchAngle>-4950)
			{
				bigArmPitchM->setSpeed(-200);
				statusFlag=4;
			}
			else
			{
				bigArmPitchM->resetSpeed();//����֧��δ֧�ز�������λ
				statusFlag=4;
			}
		}
	}
	else//�¸�
	{
		if(temBigArmRotateAngle<3600&&temBigArmRotateAngle>-1800)//�����ת�ڰ�ȫ������
		{
			if(temBigArmPitchAngle<-2000)
				bigArmPitchM->setSpeed(temSpeed);
			else if(temBigArmPitchAngle<-1600)
				bigArmPitchM->setSpeed(temSpeed/3);
			else if(temBigArmPitchAngle<-1500)
			{
				bigArmPitchM->setSpeed(200);
				statusFlag=5;
			}
			else
			{
				bigArmPitchM->resetSpeed();//��۵������ĽǶ���λ
				statusFlag=5;
			}
		}
		else
		{
			if(temBigArmPitchAngle<-3800)
				bigArmPitchM->setSpeed(temSpeed);
			else if(temBigArmPitchAngle<-3400)
				bigArmPitchM->setSpeed(temSpeed/3);
			else if(temBigArmPitchAngle<-3300)
			{
				bigArmPitchM->setSpeed(200);
				statusFlag=6;
			}
			else
			{
				bigArmPitchM->resetSpeed();//�ɰ��ֲ�������������λ
				statusFlag=6;
			}
		}
	}
	return statusFlag;
}

/**
  * ��  �ܣ����ô����ת�Ƕ�
  * ��  �����趨���ٶȵĲο�ֵ
  * ����ֵ��
  * 0�����������ٶ�
  * 1�������ת���ұ߰��ָ���
  * 2��֧��δ������ɵĸ���
  * 3����۸����Ƕ�̫����ɵĸ���
  * 4�������ת����߰��ָ���
  * 5��֧��δ������ɵĸ���
  * 6����۸����Ƕ�̫����ɵĸ���
  */
uint8_t XbotApp::setBigArmRotateSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;
	uint16_t temSupportArmAngle=(uint16_t)((int32_t)(fBDiscA->DATA_16)*1125/32);		//֧�۸����Ƕ�
	int16_t temBigArmPitchAngle=fBbigArmPitchA->DATA_16;				//��۸����Ƕ�
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;			//�����ת�Ƕ�
	if(temSpeed==0)
	{
		bigArmRotateM->resetSpeed();
		return statusFlag;
	}
	if(!limitFlag)
	{
		bigArmRotateM->setSpeed(temSpeed);
		return statusFlag;
	}
	if(temSpeed<0) 	//����
	{
		if(temBigArmPitchAngle<-1350) //��۸����ϸߵ�״̬��
		{
			if(temBigArmPitchAngle>-3200||temBigArmPitchAngle<-16300)//��۸����ڰ���֮��
			{
				if(temBigArmRotateAngle>-1200)
					bigArmRotateM->setSpeed(temSpeed);
				else if(temBigArmRotateAngle>-1600)
					bigArmRotateM->setSpeed(temSpeed/3);
				else if(temBigArmRotateAngle>-1700)
				{
					bigArmRotateM->setSpeed(-200);
					statusFlag=1;//�����ת���ұ߰��ָ���
				}
				else
				{
					bigArmRotateM->resetSpeed();
					statusFlag=1;//�����ת���ұ߰��ָ���
				}
			}
			else //��۸����ڰ���֮�� 
			{
				/////
				if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32-300)&&temSupportArmAngle<(ARM0_ANGLE_270*1125/32+300))//֧�۳���
					bigArmRotateM->setSpeed(temSpeed);
				else
				{
					if(temBigArmRotateAngle>-3500)
						bigArmRotateM->setSpeed(temSpeed);
					else if(temBigArmRotateAngle>-3900)
						bigArmRotateM->setSpeed(temSpeed/3);
					else if(temBigArmRotateAngle>-4000)
					{
						bigArmRotateM->setSpeed(-200);
						statusFlag=2;//֧��δ������ɵĸ���
					}
					else
					{
						bigArmRotateM->resetSpeed();
						statusFlag=2;//֧��δ������ɵĸ���
					}
				}
			}
		}
		else//��۸����Ƕ�̫��
		{
			bigArmRotateM->resetSpeed();//��۸����Ƕ�̫����ɵĸ���
			statusFlag=3;
		}
	}
	else						//����
	{
		if(temBigArmPitchAngle<-1350)
		{
			if(temBigArmPitchAngle>-3200||temBigArmPitchAngle<-16300)
			{
				if(temBigArmRotateAngle<3000)
					bigArmRotateM->setSpeed(temSpeed);
				else if(temBigArmRotateAngle<3400)
					bigArmRotateM->setSpeed(temSpeed/3);
				else if(temBigArmRotateAngle<3500)
				{
					bigArmRotateM->setSpeed(200);
					statusFlag=4;
				}
				else
				{
					bigArmRotateM->resetSpeed();//�����ת����߰��ָ���
					statusFlag=4;
				}
			}
			else
			{
				if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32-300)&&temSupportArmAngle<(ARM0_ANGLE_270*1125/32+300))//֧�۳���
					bigArmRotateM->setSpeed(temSpeed);
				else
				{
					if(temBigArmRotateAngle<4500)
						bigArmRotateM->setSpeed(temSpeed);
					else if(temBigArmRotateAngle<4900)
						bigArmRotateM->setSpeed(temSpeed/3);
					else if(temBigArmRotateAngle<5000)
					{
						bigArmRotateM->setSpeed(200);
						statusFlag=5;//֧��δ������ɵĸ���
					}
					else
					{
						bigArmRotateM->resetSpeed();
						statusFlag=5;//֧��δ������ɵĸ���
					}
				}
			}
		}
		else
		{
			bigArmRotateM->resetSpeed();//��۸����Ƕ�̫����ɵĸ���
			statusFlag=6; 
		}
	}
	return statusFlag;
}


/**
  * ��  �ܣ�����֧����ת�ٶ�
  * ��  �����趨���ٶȵĲο�ֵ
  * ����ֵ��
  * 0�����������ٶ�
  * 1����۵�λ���γɵĸ��棬�����˶�����ɻ�������б
  * 2����۵�λ���γɵĸ��棬�����˶�����ɻ�������б
  * 
  */

#ifdef USEPOTENTIOMETER

uint8_t XbotApp::setSupportArmSpeed(int16_t temSpeed) 
{
	uint8_t statusFlag=0;
	uint16_t temSupportArmAngle=(uint16_t)((int32_t)(fBDiscA->DATA_16)*1125/32);								//֧�۸����Ƕ� ת��Ϊ36000 ��
	int16_t temBigArmPitchAngle=fBbigArmPitchA->DATA_16;													//��۸����Ƕ�
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;												//�����ת�Ƕ�
	if(temSpeed==0)
	{
		supportArmM->resetSpeed();
		return statusFlag;
	}
	if(!limitFlag)
	{
		supportArmM->setSpeed(temSpeed);
		return statusFlag;
	}
	if(temSupportArmAngle>(XBOT_CRITICAL_ARM0_DN*1125/32+400)&&temSupportArmAngle<(XBOT_CRITICAL_ARM0_UP*1125/32-400))//�ھ������� ��ֹ�˶�������ػ� �ֶ�����λ�� ����ʹ��ȡ����λ ����λ��
	{
		statusFlag=5;
		supportArmM->resetSpeed();
		return statusFlag;
	}
	if(temSpeed<0) //�������˶�
	{
		if(temBigArmPitchAngle>-5100&&temBigArmRotateAngle>-4100&&temBigArmRotateAngle<5100)
		{
			if((temSupportArmAngle>(XBOT_CRITICAL_ARM0_UP_1*1125/32+500))||(temSupportArmAngle<(XBOT_CRITICAL_ARM0_DN*1125/32+500)))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle>(XBOT_CRITICAL_ARM0_UP_1*1125/32+300))
			{
				supportArmM->setSpeed(-2000);
			}
			else if(temSupportArmAngle>(XBOT_CRITICAL_ARM0_UP_1*1125/32+100))
			{
				supportArmM->setSpeed(-200);
				statusFlag=3;
			}
			else
			{
				supportArmM->resetSpeed();
				statusFlag=3;
			}
		}
		else
		{
			if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32+600))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32+300))
				supportArmM->setSpeed(temSpeed/5);
			else if(temSupportArmAngle>XBOT_LLL_ARM0*1125/32+100)
			{
				supportArmM->setSpeed(-200);
				statusFlag=1;
			}
			else
			{
				supportArmM->resetSpeed();//��۵�λ���γɵĸ��� 
				statusFlag=1;
			}
		}
	}
	else //�������˶�
	{
		if(temBigArmPitchAngle>-5100&&temBigArmRotateAngle>-4100&&temBigArmRotateAngle<5100)
		{
			if((temSupportArmAngle<(XBOT_CRITICAL_ARM0_DN_1*1125/32-500))||(temSupportArmAngle>(XBOT_CRITICAL_ARM0_UP*1125/32-500)))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle<(XBOT_CRITICAL_ARM0_DN_1*1125/32-300))
			{
				supportArmM->setSpeed(2000);
			}
			else  if(temSupportArmAngle<(XBOT_CRITICAL_ARM0_DN_1*1125/32-100))
			{
				supportArmM->setSpeed(200);
				statusFlag=4;
			}
			else
			{
				supportArmM->resetSpeed();
				statusFlag=4;
			}
		}
		else 
		{
			if(temSupportArmAngle<(ARM0_ANGLE_270*1125/32-500))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle<(ARM0_ANGLE_270*1125/32-300))
				supportArmM->setSpeed(2000);
			else if(temSupportArmAngle<ARM0_ANGLE_270*1125/32)
			{
				supportArmM->setSpeed(200);
				statusFlag=2;
			}
			else
			{
				supportArmM->resetSpeed();//��۵�λ���γɵĸ��� 
				statusFlag=2;
			}
		}
	}
	return statusFlag;
}
# else
uint8_t XbotApp::setSupportArmSpeed(int16_t temSpeed)
{
	uint8_t statusFlag=0;
	uint16_t temSupportArmAngle=(uint16_t)((int32_t)(fBDiscA->DATA_16)*1125/32);	//֧�۸����Ƕ�
	int16_t temBigArmPitchAngle=fBbigArmPitchA->DATA_16;													//��۸����Ƕ�
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;												//�����ת�Ƕ�
	if(temSpeed==0)
	{
		supportArmM->resetSpeed();
		return statusFlag;
	}
	if(!limitFlag)
	{
		supportArmM->setSpeed(temSpeed);
		return statusFlag;
	}
	
	if(temSpeed<0)
	{
		if(temBigArmPitchAngle>-5100&&temBigArmRotateAngle>-4100&&temBigArmRotateAngle<5100)
		{
			supportArmM->setSpeed(temSpeed);
		}
		else
		{
			if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32+500))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle>(XBOT_LLL_ARM0*1125/32+200))
				supportArmM->setSpeed(temSpeed/3);
			else if(temSupportArmAngle>XBOT_LLL_ARM0*1125/32)
			{
				supportArmM->setSpeed(-200);
				statusFlag=1;
			}
			else
			{
				supportArmM->resetSpeed();//��۵�λ���γɵĸ��� 
				statusFlag=1;
			}
		}
	}
	else
	{
		if(temBigArmPitchAngle>-5100&&temBigArmRotateAngle>-4100&&temBigArmRotateAngle<5100)
		{
			supportArmM->setSpeed(temSpeed);
		}
		else 
		{
			if(temSupportArmAngle<(ARM0_ANGLE_270*1125/32-800))
				supportArmM->setSpeed(temSpeed);
			else if(temSupportArmAngle<(ARM0_ANGLE_270*1125/32-300))
				supportArmM->setSpeed(temSpeed/3);
			else if(temSupportArmAngle<ARM0_ANGLE_270*1125/32)
			{
				supportArmM->setSpeed(200);
				statusFlag=2;
			}
			else
			{
				supportArmM->resetSpeed();//��۵�λ���γɵĸ��� 
				statusFlag=2;
			}
		}
	}
	return statusFlag;
}
#endif
/**
  * ��  �ܣ������е�������ĽǶ�����
  * ��  ������
  * ����ֵ����
  * 
  */
bool  XbotApp::unlockArms(int16_t angle)
{
	if(fBforearmPitchA->DATA_16<1500||fBwristPitchA->DATA_16<1100||fBbigArmPitchA->DATA_16>-800)
	{
		suppArmRunToPos(angle,false);

		if(fBforearmPitchA->DATA_16<1500)//С��С��14��
		{
			forearmPitchM->setPWMSpeed(20000);
			forearmPitchM	->resetUspeedTime();
		}
		else //С�۴���15��
		{
			forearmPitchM->setPWMSpeed(0);
			forearmPitchM	->resetUspeedTime();
		}
		
		if(fBwristPitchA->DATA_16<1100) //����С��11��
		{
			wristPitchM->setPWMSpeed(20000);
			wristPitchM	->resetUspeedTime();
		}
		else
		{
			wristPitchM	->resetUspeedTime();
			wristPitchM->setPWMSpeed(0);
		}
		
		if(fBbigArmPitchA->DATA_16>-800) //��۴���-8��
		{
			bigArmPitchM->setPWMSpeed(-20000);
			bigArmPitchM	->resetUspeedTime();
		}
		else//���С��-8��
		{
			bigArmPitchM->setPWMSpeed(0);
			bigArmPitchM	->resetUspeedTime();
		}
		return false;
	}
	return true;
}


/**
  * ��  �ܣ����Z���ϵ�����
  * ��  ������
  * ����ֵ����
  * 
  */
bool XbotApp::unlockForZup()
{
// 	uint16_t temSupportArmAngle=(uint16_t)((int32_t)(fBDiscA->DATA_16)*1125/32);		//֧�۸����Ƕ�

	if(unlockArms(XBOT_LLL_ARM0))//�ȴ������ؽ�
	{
		if((fBDiscA->DATA_16)<(XBOT_LLL_ARM0-4)||(fBDiscA->DATA_16)>(XBOT_LLL_ARM0+4))//֧��֧��
		{
			suppArmRunToPos(XBOT_LLL_ARM0,false);
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

/****************************************************************************************************/
/************************************XYZ�����㷨ģʽ**************************************************/
/****************************************************************************************************/

#define LL1			558
#define LL2			538.2
#define LL3			280.0		//117
#define HH0 		14.0
#define YY0 		7.0
#define M_PI_180	0.0001745329

#define L1L1 	311364								//558*558
#define L2L2 	289659.24							//538.2*538.2
#define L1L2 	300315.6							//558*538.2
#define L1L22 600631.2							//558*538.2*2

#define XBOT_DEV_ARM1	0X00		//�����ת
#define XBOT_DEV_ARM2	0X01		//��۸���
#define XBOT_DEV_ARM3	0X02		//С�۸���
#define XBOT_DEV_ARM4	0X03		//������
#define XBOT_DEV_ARM5	0X04		//������ת
#define XBOT_DEV_ARM6	0X05		//��̨����
#define XBOT_DEV_ARM7	0X06		//��̨��ת
#define XBOT_ARM_DEV_TOTAL 0x09

#define BIGARMSUBANGLE_1 (0)
#define BIGARMSUBANGLE 0.028443

void XbotApp::XbotArmSetXyzCtrlMode()
{
	int16_t temAngle[XBOT_ARM_DEV_TOTAL]={0};
	double 	Angle[XBOT_ARM_DEV_TOTAL]={0};		//��ؽڽǶ�ֵ����λ��
	int16_t SpeedY,SpeedX,SpeedZ;
	int16_t TempSpeed=0;
	int8_t direction=0;

	if(fBTerminalData[5]&0x08)
	{
		SpeedZ=-(fBTerminalData[5]&0x07);
	}
	
	else
	{
		SpeedZ=fBTerminalData[5]&0x07;
	}
	
	if(fBTerminalData[7]&0x08)
	{
		SpeedX=-(fBTerminalData[7]&0x07);
	}
	else
	{
		SpeedX=fBTerminalData[7]&0x07;
	}
	
	if(((fBTerminalData[7]&0x80)>>4)&0x08)
	{
		SpeedY=((fBTerminalData[7]&0x70)>>4)&0x07;
	}
	else
	{
		SpeedY=-((fBTerminalData[7]&0x70)>>4&0x07);
	}

	temAngle[XBOT_DEV_ARM1]=fBbigArmRotateA->DATA_16;
	temAngle[XBOT_DEV_ARM2]=18000+fBbigArmPitchA->DATA_16;
	temAngle[XBOT_DEV_ARM3]=(fBforearmPitchA->DATA_16);
	temAngle[XBOT_DEV_ARM4]=(fBwristPitchA->DATA_16);
	Angle[XBOT_DEV_ARM1] = (double)temAngle[XBOT_DEV_ARM1]*M_PI_180-BIGARMSUBANGLE_1;
	Angle[XBOT_DEV_ARM2] = (double)temAngle[XBOT_DEV_ARM2]*M_PI_180+BIGARMSUBANGLE;
	Angle[XBOT_DEV_ARM3] = (double)temAngle[XBOT_DEV_ARM3]*M_PI_180;
	if(SpeedY == 0x00 && SpeedZ == 0x00 && SpeedX == 0x00)
	{
		runOnXYZLine(0,Angle,0);
	}
	else
	{
		if(SpeedZ!=0)
		{
			direction=3;
			if(runOnXYZLine(direction,Angle,SpeedZ)<250)
			{
				if(SpeedZ<0)//�����ֱ�
				{
					if(fBforearmPitchA->DATA_16<2000)
					{
						setBigArmPitchSpeed(0);
						setForearmPitchSpeed(0);
						setWristPitchSpeed(0);
						return;
					}
					if((fBbigArmRotateA->DATA_16<3600)&&(fBbigArmRotateA->DATA_16>-1800))
						allArmRunToPos(fBbigArmRotateA->DATA_16,-1000,2000,2000,0,15000,0,XBOT_LLL_ARM0);
					else
						allArmRunToPos(fBbigArmRotateA->DATA_16,-3300,6600,6600,0,12700,0,XBOT_LLL_ARM0);
					return;
				}
				else	//�����ֱ�
				{
					if(unlockForZup())
					{
						allArmRunToPos(fBbigArmRotateA->DATA_16,-9000,18000,18000,0,7000,0,XBOT_LLL_ARM0);
						return;
					}
					else
						return;
				}
			}
		}
		else if(SpeedY!=0)
		{
			direction=1;
			runOnXYZLine(direction,Angle,SpeedY);
		}
		else if(SpeedX!=0)
		{
			direction=2;
			runOnXYZLine(direction,Angle,SpeedX);
		}
	}
	
	//��λ ��Ҫ�ǽǶ���λ
	if((temAngle[XBOT_DEV_ARM3]>15500&&(forearmPitchM->getSpeed()>0))||(temAngle[XBOT_DEV_ARM4]<600&&(wristPitchM->getSpeed()<0)))
	{
		bigArmRotateM->resetSpeed();
		bigArmPitchM->resetSpeed();
		forearmPitchM->resetSpeed();
		wristPitchM->resetSpeed();
		wristRotateM->resetSpeed();
	}

	//��צ��ת�ɿ�	
	if(fBTerminalData[6]&0x80)
	{
		TempSpeed=((int16_t)((fBTerminalData[6]&0x70)>>0x04)*1714);
	}
	else
	{
		TempSpeed=(-((int16_t)((fBTerminalData[6]&0x70)>>0x04)*1714));
	}	
	if(TempSpeed)
			wristRotateM->setSpeed(TempSpeed);
}

/**
  * ��  �ܣ���ץĩ����Zֱ���˶�
  * ��  �����˶��ٶ�
  * ����ֵ����
  * 
  */
void XbotApp::runOnZZZLine(int16_t speed)
{
	double temSpeed=0;
	double maxSpeed;
	double temBigArmPitchSpeed=0;
	double temforeArmPitchSpeed=0;
	double temWristPitchSpeed=0;
	double checkPos=0;
	double checkPos_1=0;
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;
	int16_t temForearmPitchAngle=fBforearmPitchA->DATA_16;
	int16_t temWristPitchAngle=fBwristPitchA->DATA_16;
	
	double bigArmPitchRadian= ((double)(fBbigArmPitchA->DATA_16+18000)*2*PI)/36000+ZZZ_LINE_RADIAN;	//��ۻ��Ƚ�
	double foreArmPitchRadian=((double)fBforearmPitchA->DATA_16*2*PI)/36000;				//С�ۻ��Ƚ�
	double wristPitchRadian =((double)fBwristPitchA->DATA_16*2*PI)/36000;
	
	double temRadian=PI-foreArmPitchRadian-bigArmPitchRadian;												//С��ĩ�����˶��켣ֱ��֮��ļн�

	double temRadian_1=wristPitchRadian-foreArmPitchRadian+(PI/2-bigArmPitchRadian+ZZZ_LINE_RADIAN); 
	
	double LLLCOSW1=BIG_ARM_LEN*cos(bigArmPitchRadian);
	double LLLCOSW2=FORE_ARM_LEN*cos(temRadian);
	
	double LLLSINW1=BIG_ARM_LEN*sin(bigArmPitchRadian-ZZZ_LINE_RADIAN);
	double LLLSINW2=FORE_ARM_LEN*sin(temRadian+ZZZ_LINE_RADIAN);
	
	checkPos=BIG_ARM_LEN*cos(bigArmPitchRadian-ZZZ_LINE_RADIAN)+FORE_ARM_LEN*cos(temRadian+ZZZ_LINE_RADIAN);
	checkPos_1=checkPos-WRIST_ARM_LEN*sin(temRadian_1);
	
	if(checkPos<30000)//||checkPos_1<30000)
	{
		if(speed>0)
		{
			if(unlockForZup())
			{
				allArmRunToPos(temBigArmRotateAngle,-9000,18000,18000,0,9000,0,XBOT_LLL_ARM0);
			}
		}
		else
		{
			if(temForearmPitchAngle<2000)
			{
				setBigArmPitchSpeed(0);
				setForearmPitchSpeed(0);
				setWristPitchSpeed(0);
				return;
			}
			if((temBigArmRotateAngle<3600)&&(temBigArmRotateAngle>-1800))
				allArmRunToPos(temBigArmRotateAngle,-1000,2000,2000,0,17000,0,XBOT_LLL_ARM0);
			else
				allArmRunToPos(temBigArmRotateAngle,-3300,6600,6600,0,14700,0,XBOT_LLL_ARM0);
		}
		return;
	}
	if(checkPos_1<37000)
	{
			setBigArmPitchSpeed(0);
			setForearmPitchSpeed(0);
			setWristPitchSpeed(0);
			return;
	}
	if(LLLSINW1>LLLSINW2)
		temSpeed=-(double)speed;
	else
		temSpeed=(double)speed;
	
	if(temSpeed<0&&((temForearmPitchAngle>13000)||(temWristPitchAngle>13000)))
	{
		temforeArmPitchSpeed=0;
		temBigArmPitchSpeed=0;
	}
	else
	{
		temforeArmPitchSpeed=temSpeed;
		temBigArmPitchSpeed=(temSpeed*LLLCOSW2)/(LLLCOSW1+LLLCOSW2);
	}

	temWristPitchSpeed=temforeArmPitchSpeed-temBigArmPitchSpeed;
	
	//�Ƚ������ٶȵĴ�С��ϵ
	maxSpeed=MAX(temBigArmPitchSpeed,temforeArmPitchSpeed);
	maxSpeed=MAX(maxSpeed,temWristPitchSpeed);
	
	temSpeed=ABS(temSpeed);
	temBigArmPitchSpeed=(temBigArmPitchSpeed/maxSpeed)*temSpeed;
	temforeArmPitchSpeed=(temforeArmPitchSpeed/maxSpeed)*temSpeed;
	temWristPitchSpeed=(temWristPitchSpeed/maxSpeed)*temSpeed;
	
	setBigArmPitchSpeed(temBigArmPitchSpeed);
	setForearmPitchSpeed(-temforeArmPitchSpeed);
	setWristPitchSpeed(-temWristPitchSpeed);

// 	bigArmPitchM->setSpeed(temBigArmPitchSpeed);
// 	forearmPitchM->setSpeed(-temforeArmPitchSpeed);
// 	wristPitchM->setSpeed(-temWristPitchSpeed);

	if(bigArmPitchM->getSpeed()==0||forearmPitchM->getSpeed()==0||wristPitchM->getSpeed()==0)//��һ���ؽڵ�����λֵ ֹͣ�˶�
	{
		setBigArmPitchSpeed(0);
		setForearmPitchSpeed(0);
		setWristPitchSpeed(0);
		return;
	}

}

/**
  * ��  �ܣ���ץĩ����Yֱ���˶�
  * ��  �����˶��ٶ�
  * ����ֵ����
  * 
  */
void XbotApp::runOnYYYLine(int16_t speed)
{
	double temSpeed=(double)speed;
// 	double temSpeed=0;
	double maxSpeed=0;
	double checkPos=0;
	double checkPos_1=0;
	double temBigArmPitchSpeed=0;
	double temforeArmPitchSpeed=0;
	double temWristPitchSpeed=0;
	double bigArmPitchRadian= ((double)(fBbigArmPitchA->DATA_16+18000)*2*PI)/36000+YYY_LINE_RADIAN;	//��ۻ��Ƚ�
	double foreArmPitchRadian=((double)fBforearmPitchA->DATA_16*2*PI)/36000;				//С�ۻ��Ƚ�
	double wristPitchRadian =((double)fBwristPitchA->DATA_16*2*PI)/36000;
	double temRadian=PI-foreArmPitchRadian-bigArmPitchRadian;												//С��ĩ�����˶��켣ֱ��֮��ļн�
	
	double temRadian_1=wristPitchRadian-foreArmPitchRadian+(PI/2-bigArmPitchRadian+YYY_LINE_RADIAN); 

	double LLLCOSW1=BIG_ARM_LEN*cos(bigArmPitchRadian);
	double LLLCOSW2=FORE_ARM_LEN*cos(temRadian);

	checkPos=LLLCOSW1+LLLCOSW2;
	checkPos_1=checkPos-WRIST_ARM_LEN*sin(temRadian_1);
	
	if((checkPos<40000||checkPos_1<40000)&&temSpeed>0)
	{
		temforeArmPitchSpeed=0;
		temBigArmPitchSpeed=0;
	}
	else if(temSpeed<0&&checkPos<31000)
	{
		temforeArmPitchSpeed=0;
		temBigArmPitchSpeed=0;
	}
	else if(temSpeed<0&&((fBforearmPitchA->DATA_16>13000)||(fBwristPitchA->DATA_16>15000)))
	{
		temforeArmPitchSpeed=0;
		temBigArmPitchSpeed=0;
	}
	else
	{
		temforeArmPitchSpeed=temSpeed;
		temBigArmPitchSpeed=(temSpeed*LLLCOSW2)/(LLLCOSW1+LLLCOSW2);
	}
	temWristPitchSpeed=temforeArmPitchSpeed-temBigArmPitchSpeed;
	
	//�Ƚ������ٶȵĴ�С��ϵ
	maxSpeed=MAX(temBigArmPitchSpeed,temforeArmPitchSpeed);
	maxSpeed=MAX(maxSpeed,temWristPitchSpeed);
	
	temSpeed=ABS(temSpeed);
	temBigArmPitchSpeed=(temBigArmPitchSpeed/maxSpeed)*temSpeed;
	temforeArmPitchSpeed=(temforeArmPitchSpeed/maxSpeed)*temSpeed;
	temWristPitchSpeed=(temWristPitchSpeed/maxSpeed)*temSpeed;
	
	setBigArmPitchSpeed(temBigArmPitchSpeed);
	setForearmPitchSpeed(-temforeArmPitchSpeed);
	setWristPitchSpeed(-temWristPitchSpeed);

// 	bigArmPitchM->setSpeed(temBigArmPitchSpeed);
// 	forearmPitchM->setSpeed(-temforeArmPitchSpeed);
// 	wristPitchM->setSpeed(-temWristPitchSpeed);

	if(bigArmPitchM->getSpeed()==0||forearmPitchM->getSpeed()==0||wristPitchM->getSpeed()==0)//��һ���ؽڵ�����λֵ ֹͣ�˶�
	{
		setBigArmPitchSpeed(0);
		setForearmPitchSpeed(0);
		setWristPitchSpeed(0);
		return;
	}
}

/**
  * ��  �ܣ���ץĩ��ת��
  * ��  �����˶��ٶ�
  * ����ֵ����
  * 
  */
void XbotApp::runOnXXXLine(int16_t speed)
{
	int16_t temSpeed=speed;
	int16_t temBigArmRotateAngle=fBbigArmRotateA->DATA_16;			//�����ת�Ƕ�
	
	double bigArmPitchRadian= ((double)(fBbigArmPitchA->DATA_16+18000)*2*PI)/36000;	//��ۻ��Ƚ�
	double foreArmPitchRadian=((double)fBforearmPitchA->DATA_16*2*PI)/36000;				//С�ۻ��Ƚ�
	double temRadian=PI-foreArmPitchRadian-bigArmPitchRadian;												//С��ĩ�����˶��켣ֱ��֮��ļн�
	if((BIG_ARM_LEN*cos(bigArmPitchRadian)+FORE_ARM_LEN*cos(temRadian))>37000)
	{
		if(temSpeed<0)
		{
			if(temBigArmRotateAngle>-12300)
				setBigArmRotateSpeed(-temSpeed);
			else
				setBigArmRotateSpeed(0);
		}
		else
		{
			if(temBigArmRotateAngle<12300)
				setBigArmRotateSpeed(-temSpeed);
			else
				setBigArmRotateSpeed(0);
		}
	}
	else
	{
		setBigArmRotateSpeed(0);
	}
}

/**
  * ��  �ܣ�������ƻ�е�� ��Ҫ�ǵ�����
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotApp::controlArmISO()
{
	int temMode=signalType;
	if(temMode==WIRE_WORK_MODE)
	{
		while(wirePort->readAllow())
		{
			while (!armPort->putChar(wirePort->getChar()));
		}
		while( armPort->readAllow())
		{
			while (!wirePort->putChar(armPort->getChar()));
		}
	}
	else if(temMode==WIRELESS_WORK_MODE)
	{
		while(wireLessPort->readAllow())
		{
			while (!armPort->putChar(wireLessPort->getChar()));
		}
		while( armPort->readAllow())
		{
			while (!wireLessPort->putChar(armPort->getChar()));
		}
	}
	
//GPSPort�����Ĵ��ھ���
	
// 	int temMode=signalType;
// 	if(temMode==WIRE_WORK_MODE)
// 	{
// 		while(wirePort->readAllow())
// 		{
// 			while (!GPSPort->putChar(wirePort->getChar()));
// 		}
// 		while( GPSPort->readAllow())
// 		{
// 			while (!wirePort->putChar(GPSPort->getChar()));
// 		}
// 	}
// 	else if(temMode==WIRELESS_WORK_MODE)
// 	{
// 		while(wireLessPort->readAllow())
// 		{
// 			while (!GPSPort->putChar(wireLessPort->getChar()));
// 		}
// 		while( GPSPort->readAllow())
// 		{
// 			while (!wireLessPort->putChar(GPSPort->getChar()));
// 		}
// 	}
}

double XbotApp::runOnXYZLine(int8_t direction,double *Angle,int16_t speed)				//ƽ���ڵѿ��������X���˶� �ջ�����
{
	static double XXX,YYY,ZZZ;																										//��ʼʱС��ĩ�˵ĵѿ�������ֵ
	static int8_t backDirection=0;
	double TEMXXXYYY,XY2,XYZ2,XY,XYZ;
	double temA0,temA1,temA2;//Ҫ�����Ŀ��Ƕ�
	double distance=0.0;
	if(xyzFlag==false)
	{
		TEMXXXYYY=LL1*cos((double)Angle[1])-LL2*cos((double)(Angle[1]+Angle[2]));
		XXX=TEMXXXYYY*cos(Angle[0]);
		YYY=TEMXXXYYY*sin(Angle[0]);
		ZZZ=LL1*sin(Angle[1])-LL2*sin((double)(Angle[1]+Angle[2]));
		backDirection=0;
		xyzFlag=true;
	}
	if(direction==1)				//y�����˶�
	{
		TEMXXXYYY=LL1*cos((double)Angle[1])-LL2*cos((double)(Angle[1]+Angle[2]));
		if(backDirection==2)//�ϴ���X�����˶�
		{
			XXX=TEMXXXYYY*cos(Angle[0]);
		}
		else if(backDirection==3)//�ϴ���Z�����˶�
		{
			ZZZ=LL1*sin(Angle[1])-LL2*sin(Angle[1]+Angle[2]);
		}
		YYY=TEMXXXYYY*sin(Angle[0])+speed*3;//y�������¸�ֵ
		XY2=XXX*XXX+YYY*YYY;
		XYZ2=XY2+ZZZ*ZZZ;
		XY=sqrt(XY2);
		XYZ=sqrt(XYZ2);
		if(XXX<300)//stop
		{
			bigArmRotateM->resetSpeed();
			bigArmPitchM->resetSpeed();
			forearmPitchM->resetSpeed();
		}
		else
		{
			temA0=(atan(YYY/XXX)+BIGARMSUBANGLE_1)*18000/PI;
			temA1=((atan(ZZZ/XY)+acos((L1L1+XYZ2-L2L2)/(2*LL1*XYZ))-BIGARMSUBANGLE)*18000/PI)-18000;				//��۸����Ƕȸ�ֵ
			temA2=(acos((L1L1+L2L2-(XYZ2))/L1L22))*18000/PI;
			threeArmRunToPos(temA0,temA1,temA2,speed);
		}
		backDirection=direction;
		distance=XXX;
	}
	else if(direction==2)		//x�����˶� ǰ���˶�
	{
		TEMXXXYYY=LL1*cos((double)Angle[1])-LL2*cos((double)(Angle[1]+Angle[2]));
		if(backDirection==1)//�ϴ���Y�����˶�
		{
			YYY=TEMXXXYYY*sin(Angle[0]);
		}
		else if(backDirection==3)//�ϴ���Z�����˶�
		{
			ZZZ=LL1*sin(Angle[1])-LL2*sin(Angle[1]+Angle[2]);
		}
		XXX=TEMXXXYYY*cos(Angle[0])+speed*3/2;//y�������¸�ֵ
		XY2=XXX*XXX+YYY*YYY;
		XYZ2=XY2+ZZZ*ZZZ;
		XY=sqrt(XY2);
		XYZ=sqrt(XYZ2);
		temA0=(atan(YYY/XXX)+BIGARMSUBANGLE_1)*18000/PI;
		temA1=((atan(ZZZ/XY)+acos((L1L1+XYZ2-L2L2)/(2*LL1*XYZ))-BIGARMSUBANGLE)*18000/PI)-18000;				//��۸����Ƕȸ�ֵ
		temA2=(acos((L1L1+L2L2-(XYZ2))/L1L22))*18000/PI;																//С�۸����Ƕȸ�ֵ
		if(XXX<330&&speed<0)//stop
		{
			bigArmRotateM->resetSpeed();
			bigArmPitchM->resetSpeed();
			forearmPitchM->resetSpeed();
		}
		else if(XXX>250)
		{
			threeArmRunToPos(temA0,temA1,temA2,speed*2/3);
		}
		backDirection=direction;
		distance=XXX;
	}
	else if(direction==3)		//z�����˶�
	{
		TEMXXXYYY=LL1*cos((double)Angle[1])-LL2*cos((double)(Angle[1]+Angle[2]));
		if(backDirection==1)//�ϴ���X�����˶�
		{
			YYY=TEMXXXYYY*sin(Angle[0]);
		}
		else if(backDirection==2)//�ϴ���X�����˶�
		{
			XXX=TEMXXXYYY*cos(Angle[0]);
		}
		ZZZ=LL1*sin(Angle[1])-LL2*sin(Angle[1]+Angle[2])+speed;
		XY2=XXX*XXX+YYY*YYY;
		XYZ2=XY2+ZZZ*ZZZ;
		XY=sqrt(XY2);
		XYZ=sqrt(XYZ2);
		temA1=((atan(ZZZ/XY)+acos((L1L1+XYZ2-L2L2)/(2*LL1*XYZ))-BIGARMSUBANGLE)*18000/PI)-18000;				//��۸����Ƕȸ�ֵ
		temA2=(acos((L1L1+L2L2-(XYZ2))/L1L22))*18000/PI;																//С�۸����Ƕȸ�ֵ
		if(XXX<300)//stop
		{
			bigArmRotateM->resetSpeed();
			bigArmPitchM->resetSpeed();
			forearmPitchM->resetSpeed();
		}
		else
			threeArmRunToPos((Angle[0]+BIGARMSUBANGLE_1)*18000/PI,temA1,temA2,speed/3);
		backDirection=direction;
		distance=XXX;
	}
	else if(direction==0)
	{
		//ֹͣ�˶�
		setBigArmRotateSpeed(0);
		setBigArmPitchSpeed(0);
		setForearmPitchSpeed(0);
		distance=0;
	}
	int16_t TempSpeed=0;
	TempSpeed = bigArmPitchM->getSpeed() + forearmPitchM->getSpeed();
	wristPitchM->setSpeed_1(TempSpeed);
	TempSpeed =bigArmRotateM->getSpeed()*1.38545;
	wristRotateM->setSpeed_1(-TempSpeed);
	checkBlockError();
	return distance;
}
/**
  * ��  �ܣ����ؽ��Ƿ��ת����ץ�гֳ���
  * ��  ������
  * ����ֵ��true �ж�ת�ؽ�
  * 				false�޶�ת�ؽ�
  */
bool XbotApp::checkBlockError()
{
	bool error_1=false;
	bool error_2=false;
	bool error_3=false;
	bool error_4=false;
	bool error_5=false;
	bool error_6=false;
	bool error_7=false;
	bool error_8=false;
	if(supportArmM->getErrorFlag()==0x0b||supportArmM->getErrorFlag()==0x0c)
		error_1=true;
	if(bigArmRotateM->getErrorFlag()==0x0b||bigArmRotateM->getErrorFlag()==0x0c)
		error_2=true;
	if(bigArmPitchM->getErrorFlag()==0x0b||bigArmPitchM->getErrorFlag()==0x0c)
		error_3=true;
	if(forearmPitchM->getErrorFlag()==0x0b||forearmPitchM->getErrorFlag()==0x0c)
		error_4=true;
	if(wristPitchM->getErrorFlag()==0x0b||wristPitchM->getErrorFlag()==0x0c)
		error_5=true;
	if(wristRotateM->getErrorFlag()==0x0b||wristRotateM->getErrorFlag()==0x0c)
		error_6=true;
	if(panTiltPitchM->getErrorFlag()==0x0b||panTiltPitchM->getErrorFlag()==0x0c)
		error_7=true;
	if(panTiltRotateM->getErrorFlag()==0x0b||panTiltRotateM->getErrorFlag()==0x0c)
		error_8=true;
	if(error_1||error_2||error_3||error_4||error_5||error_6||error_7||error_8)
	{
		if(!error_1)
			supportArmM->resetSpeed();
		if(!error_2)
			bigArmRotateM->resetSpeed();
		if(!error_3)
			bigArmPitchM->resetSpeed();
		if(!error_4)
			forearmPitchM->resetSpeed();
		if(!error_5)
			wristPitchM->resetSpeed();
		if(!error_6)
			wristRotateM->resetSpeed();
		if(!error_7)
			panTiltPitchM->resetSpeed();
		if(!error_8)
			panTiltRotateM->resetSpeed();
		return true;
	}
	else
		return false;
}

//�޸�˵��������ģʽ ������С�� �����������ʹ��
	
//					����ģʽ(Cģʽ):���Uģʽһ�Σ�������������ʹ�ۣ��������С��















