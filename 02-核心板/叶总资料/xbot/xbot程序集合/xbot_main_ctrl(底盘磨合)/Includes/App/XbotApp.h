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
#ifndef _XBOT_APP_H
#define _XBOT_APP_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "CodedDiscControl.h"
#include "MotorControl.h"
#include "PowerControl.h"
#include "TerminalControl.h"
#include "OtherDeviceControl.h"
#include "GpsImuControl.h"
#include "Timer.h"
#include "LEDLighter.h"
#include "OpticalBobbin.h"

/* ���Ͷ��� --------------------------------------------------------------------*/
//ö��ģʽID
typedef enum
{
	TTTModel,		//Tģʽ �������������ؽڿ���
	AAAModel,		//Aģʽ �ֱ۰�չ
	BBBModel,		//Bģʽ �ֱ�ǰץȡ
	CCCModel,		//Cģʽ �ֱ�����
	DDDModel,		//Dģʽ �ֱ�ǰ�۲�
	EEEModel,		//Eģʽ �ֱ�ȫչ��
	HHHModel,		//Hģʽ ֧��̧��
	IIIModel,		//Iģʽ ֧��֧��
	JJJModel,		//Jģʽ ֧������
	KKKModel,		//Kģʽ ֧��ˮƽ
	LLLModel,		//Lģʽ ֧��΢֧
	
	MMMModel,		//Mģʽ �����̷��߻�����̨��λ
	NNNModel,		//Nģʽ ���������߻�����ץ��λ
	
	SSSModel,		//Sģʽ �����˾�ֹ�����ٶ�Ϊ0 �����������豸���磺�ƣ����ܿ��� 
	XLLModel,		//��άģʽ X����
	XRRModel, 	//��άģʽ X����
	YFFModel,		//��άģʽ Y��ǰ
	YBBModel,		//��άģʽ Y���
	ZUUModel,		//��άģʽ Z����
	ZDDModel,		//��άģʽ Z����
	XYZModel		//�ѿ�������ϵ����άģʽ
}workIdType;

//ö�ٹ���ģʽ ����ģʽ�;���ģʽ
typedef enum
{
	NORMAL,
	MIRROR,
}workModelType;


/* �궨��-----------------------------------------------------------------------*/ 

class XbotApp
{
public:
	XbotApp();
	~XbotApp();

	void runOnTime2();								//�����ڶ�ʱ��TIM2�еĺ���
	void runOnTime3();								//�����ڶ�ʱ��TIM3�еĺ���
	void runOnTime4();								//�����ڶ�ʱ��TIM4�еĺ���
	void openUserInterrupt();					//���û��ж�
	SerialPort *GPSPort;							//GPS��IMUͨ�ŵĴ���
private:
	
	Timer *t1;												//��ʱ��1
	Timer *t2;												//��ʱ��2
	Timer *t3;												//��ʱ��3

	LEDLighter *led_1;// = new LEDLighter(GPIOC,GPIO_Pin_0);//Ĭ�ϵ���
	LEDLighter *led_2;
	LEDLighter *led_3;
	volatile int8_t signalType;								//�ź�����	
	volatile int8_t ectQuantity;							//�����ѹ����ѹ����24�����Զ��ػ�
	volatile int8_t *checkTime;								//���ڼ����ⳬʱ������

	volatile workModelType workModel;					//����ģʽ
	volatile bool riciveCboxFlag;
	static workIdType workId;									//����ID
	static bool limitFlag;										//��λ��־ Ĭ����λ Ϊtrue ʧ����λ����Ϊfalse
	static bool zoreCtrFlag;									//У����Ʊ�־λ��Ĭ��Ϊfalse�������󣬴�ۡ�С�ۡ��������ؽ��ٶ�����ģʽ��ΪUģʽ
	
	bool xyzFlag;														//��άģʽ���ؽڵ��˶�����־ 0:��XYZģʽ 1:y�����˶� 2:x�����˶� 3:z�����˶�
	int8_t wireLength;												//�������߳�

	volatile bool sendEnaSpeedOk;							//�豸ָ�����ɱ�־ Ĭ��δ��� Ϊfalse �����Զ�����ؽ��˶�ָ��
	volatile bool saveSendOk;									//����ָ�����ɱ�־ Ĭ����� Ϊtrue 
	volatile bool offLimitSendOk;							//ȡ����λ������ɱ�־ Ĭ����� Ϊtrue 
	volatile bool reInitPosSendOk;						//��λ���跢����ɱ�־ Ĭ����� Ϊtrue 
	volatile bool reWeaponSendOk;							//�������䷢����ɱ�־ Ĭ����� Ϊtrue 
	uint8_t *fBTerminalData;									//�������ն������ݴ�
	
//static ctrData *fBsupportArmA;						//������֧�۵���Ƕ��ݴ�
	static ctrData *fBbigArmRotateA;					//�����Ĵ����ת����Ƕ��ݴ�
	static ctrData *fBbigArmPitchA; 					//�����Ĵ�۸�������Ƕ��ݴ�
	static ctrData *fBforearmPitchA;					//������С�۸�������Ƕ��ݴ�
	static ctrData *fBwristPitchA;						//����������������Ƕ��ݴ�
	static ctrData *fBwristRotateA;						//������������ת����Ƕ��ݴ�
	static ctrData *fBpanTiltPitchA;					//��������̨��������Ƕ��ݴ�
	static ctrData *fBpanTiltRotateA;					//��������̨��ת����Ƕ��ݴ�
	static ctrData *fBfingerMediateA;					//��������צ��ϵ���Ƕ��ݴ�
	static ctrData *fBcameraPitchA;						//�����������������Ƕ��ݴ�
	static 	CodeDiscData *fBDiscA;						//�����ľ������������ݴ�
	
	ctrData	*fBLeftSpeed;											//�����������ٶ��ݴ�
	ctrData	*fBRightSpeed;										//�������ҵ���ٶ��ݴ�
	
	ctrData *fBEctQuantity_1;									//�����ĵ�Դ����1�ݴ�
	ctrData *fBEctQuantity_2;									//�����ĵ�Դ����2�ݴ�
	ctrData *fBEctQuantity_3;									//�����ĵ�Դ����3�ݴ�
	ctrData *fBEctQuantity_4;									//�����ĵ�Դ����4�ݴ�
	int8_t FBTemperature_1;										//�������¶�
	int8_t FBTemperature_2;										//�������¶�
	int8_t FBTemperature_3;										//�������¶�
	static SerialPort *wireLessPort;					//���ն�����ͨ�ŵĴ���
	static SerialPort *wirePort;							//���ն�����ͨ�ŵĴ���
	static SerialPort *codedDiscPort;					//������ͨ�ŵĴ���
	static SerialPort *armPort;								//�ͻ�е��ͨ�ŵĴ���
	static SerialPort *underpanPort;					//�͵���������Լ���Դ���ư�ͨ�ŵĴ���
// 	SerialPort *GPSPort;										//GPS��IMUͨ�ŵĴ���

	TerminalControl *Terminal;								//�ն�ͨ�ŵ�Э�������

	MotorControl *leftRunM;										//�н�����
	MotorControl *rightRunM;									//�н��ҵ��
	static MotorControl *supportArmM;					//֧�۵��
	
	static MotorControl *bigArmRotateM;				//�����ת���
	static MotorControl *bigArmPitchM; 				//��۸������
	static MotorControl *forearmPitchM;				//С�۸������
	static MotorControl *wristPitchM;					//���������
	static MotorControl *wristRotateM;				//������ת���
	static MotorControl *panTiltPitchM;				//��̨�������
	static MotorControl *panTiltRotateM;			//��̨��ת���
	static MotorControl *fingerMediateM;			//��צ��ϵ��
	static MotorControl *cameraPitchM;				//����������

	PowerControl *power;											//��Դ����ͨ��Э�������
	OtherDeviceControl *OtherDevice;					//�����豸��ͨ��Э�����
	CodedDiscControl *CodedDisc;							//�������̵�ͨ��Э�������
	GpsImuControl *gpsDevice;									//GPS�豸��ͨ��Э�������
	OpticalBobbin *opticalBobbinDevice;				//�Զ������̵�ͨ��Э�������
	
	
	
private:
	
//������������
	void resetOffLimit();							//����ȡ����λ������
	void resetReInit();								//����������λ������
	void resetSave();									//������������
	void resetWeapon();								//������������
	void resetEnaSpeed();							//����ʹ���ٶ�ָ��
//������������
	void sendOffLimitCommand();				//����ȡ����λָ��
	void sendReInitCommand();					//������λ��������
	void sendSaveCommand();						//���ͱ�����������
	void sendWeaponCommand();					//����������������
	void sendEnaSpeedCommand();				//����ʹ���ٶ�ָ��
//������������Ƿ������
	void checkOffLimit();							//���ȡ����λָ���Ƿ������
	void checkReInit();								//�����λ���������Ƿ������
	void checkSave();									//���Ƕȱ��������Ƿ������
// 	void checkWeapon();							//����������������Ƿ������
	void checkEnaSpeed();							//���ʹ���ٶ�ָ���Ƿ������
//��������
	void updateSendTerminalData();		//���·��͵��ն˵�����
	void updateSendDriverData();			//���·��͵��豸������

//���ղ���������
	void disposeTerminalData();				//���ղ������ն����÷���������
	void disposeArmsData();						//���ղ������е���豸����������
	void disposUnderpanData();				//���ղ���������豸�ķ���������
	void disposCodedDiscData();				//���ղ�������Ա����̷���������

//֧�����е�ָ���Ƕ�
	void suppArmRunToPos(int,bool showError=true);
	
//��̨���е���λ״̬
	void panTiltRunToMMMModel();
	
//��ץ���е���λ״̬
	void fingerRunToNNNModel();
	
//������ȡ֧�۵ĽǶȲ�
	int16_t getSuppArmSubAngle(int);
	
//�������ݽǶȲ��ʱ�������֧�۵��ٶȣ�֧�۱Ƚ����⣬�˶�������趨Ҫ�����ٽ�Ƕ�
	void setSuppArmspeed(int,int,int);

//���йؽ����е�ָ���Ƕȣ���ǰ���������ץץ�ֹؽ�
	void allArmRunToPos(int,int,int,int,int,int,int,int);
	
//�����ת����۸�����С�۸��������ؽ����е�ָ��λ��
	void threeArmRunToPos(int,int,int,int);
//��ʱ������ʱ��
	inline int maxTime(int32_t *);

	//ֹͣ���еĵ��
	void stopAllMoter();

	//������̨�������ٶ�
	static uint8_t setPanTiltPitchSpeed(int16_t);

	//�������������ٶ�
	static uint8_t setWristPitchSpeed(int16_t);

	//������ץ�г��ٶ�
	static uint8_t setFingerMediateSpeed(int16_t);

	//����С�۸����ٶ�
	static uint8_t setForearmPitchSpeed(int16_t);

	//���ô�۸����ٶ�
	static uint8_t setBigArmPitchSpeed(int16_t);

	//���ô����ת�ٶ�
	static uint8_t setBigArmRotateSpeed(int16_t);

	//����֧����ת�ٶ�
	static uint8_t setSupportArmSpeed(int16_t);

	//�����е�������ĽǶ�����
	bool unlockArms(int16_t);

	bool unlockForZup();
	//�������
	uint8_t subEctQuantity(); 

	//Z ģʽ���˶� ������
	void runOnZZZLine(int16_t);

	//Y ģʽ���˶� ������
	void runOnYYYLine(int16_t);

	//X ģʽ���˶� ������
	void runOnXXXLine(int16_t);
	
	//ƽ���ڵѿ��������XYZ���˶�
	double runOnXYZLine(int8_t,double *,int16_t speed);		
	
	//������ƻ�е��
	void controlArmISO();

	//xyz �ѿ�������ϵ
	void XbotArmSetXyzCtrlMode();
	
	//������޶�ת����
	bool checkBlockError();
	
};
#endif /* _XBOT_APP_H */









