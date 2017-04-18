/**
  ******************************************************************************
	*�ļ���XbotDisPlayApp.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������Xbot�������ʵ���ļ�
	*��ע��
	*
  ******************************************************************************  
	*/ 

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "XbotDisplayApp.h"
#ifdef __cplusplus
 extern "C" {
#endif
#include <stdlib.h>
// #include <math.h>								//��ѧ������
#ifdef __cplusplus
 }
#endif

/* ���Ͷ��� --------------------------------------------------------------------*/

/* �궨��-----------------------------------------------------------------------*/ 

//����ֵ��
// #define ABS(X)			((X)>0?(X):(-(X)))
// //���߾���ֵ˭��˭С��
// #define MAX(X,Y)		((ABS(X))>(ABS(Y))?(ABS(X)):(ABS(Y)))
// #define MIN(X,Y)		((ABS(X))<(ABS(Y))?(ABS(X)):(ABS(Y)))

#define LCD_PORT_NUM 					2
#define LCD_PORT_BAUD					38400

#define TERMINAL_PORT_NUM     1
#define TERMINAL_PORT_BAUD    19200

#define KM 		0
#define KA 		1
#define KB 		2
#define KC 		3
#define KD 		4
#define KABD 	5
#define KNULL -1

#define KEYINDEX_MAX 3
#define KEYINDEX_ABD_MAX 150

#define MODE_NULL						0x00//��ģʽ
#define MODE_SHOULDER_A 		0X20//֧��̧��
#define MODE_SHOULDER_B			0X40//֧��֧��
#define MODE_SHOULDER_C			0X60//֧������
#define MODE_SHOULDER_D 		0X80//֧��ˮƽ
#define MODE_ARM_CA					0XA4//��е�۰�չ��
#define MODE_ARM_CB					0XA8//��е��ǰץȡ
#define MODE_ARM_CC					0X6C//��е����ȫ����
#define MODE_ARM_DC					0XB0//��е��ǰ�۲�
#define MODE_ARM_DD					0XB4//��е��ȫչ��
#define MODE_ARM_3D					0X18//��е�۽���3D����

#define MODE_CAMERA_A       0X02//����
#define MODE_CAMERA_B				0X01//����

#define DEBUF_NULL					0X00//�޵���
#define DEBUF_CANCEL				0X8A//ȡ����λ
#define DEBUF_RESET					0X8B//������λ

#define STARTPAGENUM 							(1+languagePosition)
#define MAINPAGENUM 							(2+languagePosition)
#define ANGLEPAGENUM							(3+languagePosition)
#define SWINGARMCTRLPAGENUM				(4+languagePosition)
#define ARMCTRLPAGENUM						(5+languagePosition)
#define OTHERCTRLPAGENUM1					(6+languagePosition)
#define DEBUGCTRLPAGENUM					(7+languagePosition)


#define MAINPAGENUM_1							(8+languagePosition)
#define OTHERCTRLPAGENUM					(9+languagePosition)

#define SWINGARMCTRLPAGENUM_1			(10+languagePosition)
#define ARMCTRLPAGENUM_1					(11+languagePosition)
#define OTHERCTRLPAGENUM_1				(12+languagePosition)
#define OTHERCTRLPAGENUM1_1				(13+languagePosition)
#define DEBUGCTRLPAGENUM_1				(14+languagePosition)

#define MAINBACKPAGENUM						(15+languagePosition)
#define BACKPAGENUM								(16+languagePosition)
#define BACKPAGENUM_1							(10+languagePosition)

#define ERRORBACKPAGENUM					(17+languagePosition)
#define ERRORBACKPAGENUM_1				(18+languagePosition)
#define WEAPONCTRLPAGENUM					(19+languagePosition)
#define WEAPONCTRLPAGENUM_1				(20+languagePosition)
#define ERRORSTRAT								(21+languagePosition)

#define MAINBUTTON_M 0
#define MAINBUTTON_A 1
#define MAINBUTTON_B 2
#define MAINBUTTON_C 3
#define MAINBUTTON_D 4

#define BUTTON_M 		 0
#define BUTTON_A 		 1
#define BUTTON_B 		 2
#define BUTTON_C 		 3
#define BUTTON_D 		 4


#define ENGLISH 37
#define CHINESE 0

//�汾���� ���������ABROAD����ʹ�ù���汾��Ĭ������ΪӢ�ģ�����������������;����Ϊ���ڰ汾��Ĭ������Ϊ���ģ����ұ���������
// #define ABROAD

#ifdef ABROAD
#define DEFAULTLANGUGE ENGLISH
#else
#define DEFAULTLANGUGE CHINESE
#endif

//���캯��
XbotDisplayApp::XbotDisplayApp()
{
	workMode=MODE_NULL;
	debugMode=DEBUF_NULL;
	keysValue=-1;
	maskKeysValue=0;
	interfaceIndex=-1;
	error = new uint8_t[4];
	error[0]=0;
	error[1]=0;
	error[2]=0;
	error[3]=0;
	errorStatus=0;																															//����״̬
	pageID=0;
	enabledShowError=true;																											//Ĭ����ʾ��Ϣ����
	languagePosition=DEFAULTLANGUGE;
	led_1=new LEDLighter(GPIOB,GPIO_Pin_13);
	terminalPort=new SerialPort(TERMINAL_PORT_NUM,TERMINAL_PORT_BAUD);					//���նˣ�XBOT�����䣩ͨ�ŵĴ���
	lcdPort=new SerialPort(LCD_PORT_NUM,LCD_PORT_BAUD);													//��LCDҺ����ͨ�ŵĴ���
	
	key_M=new Key(GPIOB,GPIO_Pin_0);
	key_A=new Key(GPIOA,GPIO_Pin_7);
	key_B=new Key(GPIOA,GPIO_Pin_6);
	key_C=new Key(GPIOA,GPIO_Pin_5);
	key_D=new Key(GPIOA,GPIO_Pin_4);

	LCDManager=new LCDdisplay(lcdPort);															//����Һ����
	terminalManager=new TerminalControl(terminalPort);							//��XBOT�����佻��

	led_1->setLightOn();
	t1=new Timer(TIM2);
	t2=new Timer(TIM3);
	t3=new Timer(TIM4);
	
	
	t1->setTimeOut(20);
	t1->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM2_SubPriority);

	t2->setTimeOut(2);
	t2->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM3_SubPriority);
	

	t3->setTimeOut(10);
	t3->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM4_SubPriority);
}

XbotDisplayApp::~XbotDisplayApp()
{
	t1->stop();
	t2->stop();
	t3->stop();
	terminalPort->close();
	lcdPort->close();
	delete terminalPort;					//���նˣ�XBOT�����䣩ͨ�ŵĴ���
	delete lcdPort;							//��LCDҺ����ͨ�ŵĴ���
	delete t1;												//��ʱ��1
	delete t2;												//��ʱ��2
	delete t3;												//��ʱ��3
	delete led_1;
// 	delete led_2;
	delete key_M;
	delete key_A;
	delete key_B;
	delete key_C;
	delete key_D;
}
void XbotDisplayApp::initLCD()
{
	lcdPort->open();
	LCDManager-> SetColor(0x07E0,0x00);
	SysTick_DelayMs(80);
	LCDManager->ShowPic(0);
// 	disPageStart();											//��ʾ��������
	SysTick_DelayMs(80);
	terminalPort->open();
//�򿪶�ʱ��	
#ifndef ABROAD	
	t3->start();
	LCDManager->readLanguageBuf();//��ȡ����
#endif	
	SysTick_DelayMs(1500);
	t1->start();
	t2->start();
#ifndef ABROAD
	t3->stop();
#endif	
}
void XbotDisplayApp::setWorkMode(uint8_t value)
{
	if(workMode==value)
		workMode=MODE_NULL;
	else
		workMode=value;
}

void XbotDisplayApp::setMainButtonPress(uint8_t button)		//���������水������
{
	int position=34+button*38;
	LCDManager->CutPicAndShow(MAINBACKPAGENUM,4,position,30,25,4,position);
}
void XbotDisplayApp::setMainButtonNormal(uint8_t button)	//���������水������������״̬��
{
	int position=34+button*38;
	LCDManager->CutPicAndShow(MAINPAGENUM,4,position,30,25,4,position);
}


void XbotDisplayApp::setButtonPress(uint8_t button)				//������ͨ���水������
{
	int position=31+button*38;
	LCDManager->CutPicAndShow(BACKPAGENUM,1,position,46,31,1,position);
}
void XbotDisplayApp::setButtonChecked(uint8_t button)			//������ͨ���水��ѡ��
{
	int position=33+button*38;
	LCDManager->CutPicAndShow(BACKPAGENUM_1,1,position,46,31,1,position);
}
void XbotDisplayApp::setButtonNormal(uint8_t button)			//������ͨ���水������������״̬��
{
	int position=33+button*38;
	LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,1,position,46,31,1,position);
}

// 		case 2:

// 			break;
// 		case 3:
// 			if(workMode==MODE_ARM_CA)
// 			{
// 					LCDManager->updateKeyPic(1);
// 			}
// 			else if(workMode==MODE_ARM_CB)
// 			{
// 					LCDManager->updateKeyPic(2);
// 			}
// 			else if(workMode==MODE_ARM_CC)
// 			{
// 					LCDManager->updateKeyPic(3);
// 			}
// 			else if(workMode==MODE_ARM_3D)
// 			{
// 					LCDManager->updateKeyPic(4);
// 			}
// 			else
// 			{
// 					LCDManager->updateKeyPic(0);
// 			}
// 			break;
// 		case 4:
// 			if(workMode==MODE_CAMERA_A)
// 			{
// 					LCDManager->updateKeyPic(1);
// 			}
// 			else if(workMode==MODE_CAMERA_B)
// 			{
// 					LCDManager->updateKeyPic(2);
// 			}
// 			else if(workMode==MODE_ARM_DC)
// 			{
// 					LCDManager->updateKeyPic(3);
// 			}
// 			else if(workMode==MODE_ARM_DD)
// 			{
// 					LCDManager->updateKeyPic(4);
// 			}
// 			else
// 			{
// 					LCDManager->updateKeyPic(0);
// 			}
// 			break;


void XbotDisplayApp::disSwingArmWorkMode(bool staflag)															//���ðڱ�ģʽ��ͼƬ
{
	static uint8_t backWorkMode=0;
	if(staflag)//ǿ����ʾ
	{
		if(workMode==MODE_SHOULDER_A)
		{
			LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,62,33,116,38,62,33);
		}
		else if(workMode==MODE_SHOULDER_B)
		{
			LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,191,33,116,38,191,33);
		}
		else if(workMode==MODE_SHOULDER_C)
		{
			LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,62,130,116,38,62,130);
		}
		else if(workMode==MODE_SHOULDER_D)
		{
			LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,191,130,116,38,191,130);
		}
		backWorkMode=workMode;
	}
	else
	{
		if(backWorkMode!=workMode)//ģʽ�б仯
		{
			//
			if(backWorkMode==MODE_SHOULDER_A)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,62,33,116,38,62,33);
			}
			else if(backWorkMode==MODE_SHOULDER_B)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,191,33,116,38,191,33);
			}
			else if(backWorkMode==MODE_SHOULDER_C)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,62,130,116,38,62,130);
			}
			else if(backWorkMode==MODE_SHOULDER_D)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,191,130,116,38,191,130);
			}
			if(workMode==MODE_SHOULDER_A)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,62,33,116,38,62,33);
			}
			else if(workMode==MODE_SHOULDER_B)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,191,33,116,38,191,33);
			}
			else if(workMode==MODE_SHOULDER_C)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,62,130,116,38,62,130);
			}
			else if(workMode==MODE_SHOULDER_D)
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM_1,191,130,116,38,191,130);
			}
			backWorkMode=workMode;
		}
	}
}

void XbotDisplayApp::disArmWorkMode(bool staflag)								//�����ֱ�ģʽ��ͼƬ
{
	static uint8_t backWorkMode=0;
	if(staflag)//ǿ����ʾ
	{
		if(workMode==MODE_ARM_CA)
		{
			LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,56,32,127,21,56,32);
		}
		else if(workMode==MODE_ARM_CB)
		{
			LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,185,32,127,21,185,32);
		}
		else if(workMode==MODE_ARM_CC)
		{
			LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,56,131,127,21,56,131);
		}
		else if(workMode==MODE_ARM_3D)
		{
			LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,185,131,127,21,185,131);
		}
		backWorkMode=workMode;
	}
	else
	{
		if(backWorkMode!=workMode)//ģʽ�б仯
		{
			//
			if(backWorkMode==MODE_ARM_CA)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,56,32,127,21,56,32);
			}
			else if(backWorkMode==MODE_ARM_CB)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,185,32,127,21,185,32);
			}
			else if(backWorkMode==MODE_ARM_CC)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,56,131,127,21,56,131);
			}
			else if(backWorkMode==MODE_ARM_3D)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,185,131,127,21,185,131);
			}
			
			if(workMode==MODE_ARM_CA)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,56,32,127,21,56,32);
			}
			else if(workMode==MODE_ARM_CB)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,185,32,127,21,185,32);
			}
			else if(workMode==MODE_ARM_CC)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,56,131,127,21,56,131);
			}
			else if(workMode==MODE_ARM_3D)
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM_1,185,131,127,21,185,131);
			}
			backWorkMode=workMode;
		}
	}
}

void XbotDisplayApp::disOtherWorkMode(bool staflag)							//��������ģʽ��ͼƬ
{
	static uint8_t backWorkMode=0;
	if(staflag)//ǿ����ʾ
	{
		if(workMode==MODE_CAMERA_A)
		{
			if(LCDManager->WireLength==0)
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,56,32,127,21,56,32);
			else
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1_1,56,32,127,21,56,32);
		}
		else if(workMode==MODE_CAMERA_B)
		{
			if(LCDManager->WireLength==0)
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,185,32,127,21,185,32);
			else
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1_1,185,32,127,21,185,32);
		}
		else if(workMode==MODE_ARM_DC)
		{
			LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,57,108,143,23,57,108);
		}
		else if(workMode==MODE_ARM_DD)
		{
			LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,207,108,102,23,207,108);
		}
		backWorkMode=workMode;
	}
	else
	{
		if(backWorkMode!=workMode)//ģʽ�б仯
		{
			//
			if(backWorkMode==MODE_CAMERA_A)
			{
				if(LCDManager->WireLength==0)
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM,56,32,127,21,56,32);
				else
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1,56,32,127,21,56,32);
			}
			else if(backWorkMode==MODE_CAMERA_B)
			{
				if(LCDManager->WireLength==0)
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM,185,32,127,21,185,32);
				else
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1,185,32,127,21,185,32);
			}
			else if(backWorkMode==MODE_ARM_DC)
			{
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM,57,108,143,23,57,108);
			}
			else if(backWorkMode==MODE_ARM_DD)
			{
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM,207,108,102,23,207,108);
			}
			///////////////////////////
			if(workMode==MODE_CAMERA_A)
			{
				if(LCDManager->WireLength==0)
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,56,32,127,21,56,32);
				else
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1_1,56,32,127,21,56,32);
			}
			else if(workMode==MODE_CAMERA_B)
			{
				if(LCDManager->WireLength==0)
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,185,32,127,21,185,32);
				else
					LCDManager->CutPicAndShow(OTHERCTRLPAGENUM1_1,185,32,127,21,185,32);
			}
			else if(workMode==MODE_ARM_DC)
			{
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,57,108,143,23,57,108);
			}
			else if(workMode==MODE_ARM_DD)
			{
				LCDManager->CutPicAndShow(OTHERCTRLPAGENUM_1,207,108,102,23,207,108);
			}
			backWorkMode=workMode;
		}
	}
}

/**
  * ��  �ܣ�����LCD��ʾ������
  * ��  ������
  * ����ֵ����
  * ��  ע��	����״̬ע��
	*				XBOT_LcdData[16] ��Դ���ư� 20
	*				XBOT_LcdData[17] ������ͷ�� 21
	*				XBOT_LcdData[18]	�����ת  22
	*				XBOT_LcdData[19] ��۸���		23
	*				XBOT_LcdData[20] ������			24
	*				XBOT_LcdData[21] ֧������		25
	*				XBOT_LcdData[22] С�۸���		26
	*				XBOT_LcdData[23] ������		27
	*				XBOT_LcdData[24] ����			28
	*				XBOT_LcdData[25] �ҵ��			29
	*				XBOT_LcdData[26] ������ת		30
	*				XBOT_LcdData[27] ��̨����		31
	*				XBOT_LcdData[28] ֧�۵��		32
	*				XBOT_LcdData[29] �������		33
	*				XBOT_LcdData[30] ��̨��ת		34
	*				XBOT_LcdData[31] ��ץ�г�		35
	*/
bool XbotDisplayApp::updateLCDdata()
{
	uint8_t *temReciveData=terminalManager->getReciveData();
	uint8_t index=temReciveData[1]&0x03;
	
	LCDManager->LeftCtrlSpeed =(int)((signed char)temReciveData[2]);
	LCDManager->RightCtrlSpeed=(int)((signed char)temReciveData[3]);
	LCDManager->XBOT_LcdData[index*4]=temReciveData[4];
	LCDManager->XBOT_LcdData[index*4+1]=temReciveData[5];
	LCDManager->XBOT_LcdData[index*4+2]=temReciveData[6];
	LCDManager->XBOT_LcdData[index*4+3]=temReciveData[7];//��ص�ѹ 3 7 11 15
	LCDManager->XBOT_LcdData[16+index*4]=(temReciveData[8]>>4)&0x0f;
	LCDManager->XBOT_LcdData[17+index*4]=temReciveData[8]&0x0f;
	LCDManager->XBOT_LcdData[18+index*4]=(temReciveData[9]>>4)&0x0f;
	LCDManager->XBOT_LcdData[19+index*4]=temReciveData[9]&0x0f;
	
	
	if(LCDManager->XBOT_LcdData[3]>125)//��ص�����
		LCDManager->battery_1=15;
	else if(LCDManager->XBOT_LcdData[3]>110)//��ص�ѹ��22������
		LCDManager->battery_1=LCDManager->XBOT_LcdData[3]-110;
	else
		LCDManager->battery_1=0;
	
	if(LCDManager->XBOT_LcdData[7]>125)//��ص�����
		LCDManager->battery_2=15;
	else if(LCDManager->XBOT_LcdData[7]>110)//��ص�ѹ��22������
		LCDManager->battery_2=LCDManager->XBOT_LcdData[7]-110;
	else
		LCDManager->battery_2=0;
	
	if(LCDManager->XBOT_LcdData[11]>125)//��ص�����
		LCDManager->battery_3=15;
	else if(LCDManager->XBOT_LcdData[11]>110)//��ص�ѹ��22������
		LCDManager->battery_3=LCDManager->XBOT_LcdData[11]-110;
	else
		LCDManager->battery_3=0;
	
	if(LCDManager->XBOT_LcdData[15]>125)//��ص�����
		LCDManager->battery_4=15;
	else if(LCDManager->XBOT_LcdData[15]>110)//��ص�ѹ��22������
		LCDManager->battery_4=LCDManager->XBOT_LcdData[15]-110;
	else
		LCDManager->battery_4=0;
	
	if(index==0x00)	
		LCDManager->WireLength=temReciveData[10];			  			//������ʣ���߳�
	else if(index==0x01)	
		LCDManager->signal=(temReciveData[10]&0x07);			  					//�ź�ǿ��
	else if(index==0x02)	
		LCDManager->LeftMotorSpeed=(int)((signed char)temReciveData[10]);				//��ʵ���ٶ�
	else if(index==0x03)	
		LCDManager->RightMotorSpeed=-(int)((signed char)temReciveData[10]);				//��ʵ���ٶ�
	
	LCDManager->fireFlag=temReciveData[11];									//ˮ��״̬
	if(index==3)//��⵽һ������������400MS
		return true;
	else
		return false;
}

/**
  * ��  �ܣ���������Ϣ
  * ��  ������
  * ����ֵ��
  * 		0���ϴ��ޣ�������
  *  		1���ϴ��У�������
  *  		bit0-bit1=2���ϴ��ޣ������� bit6-bit7:��Ϣ����
  *  		bit0-bit1=3���ϴ��У������� bit6-bit7:��Ϣ���� bit5-bit2���仯��λ��
  */
uint8_t XbotDisplayApp::checkError()											//��������Ϣ
{
	static bool backErrorFlag=false;
	static uint8_t backError[4]={0,0,0,0};
	bool errorFlag=false;	
	uint8_t index=0;	
	uint8_t backErrorStatus=0;																					//����״̬
	error[0]=0;
	error[1]=0;
	error[2]=0;
	error[3]=0;
	if(!enabledShowError)//����ʾ��Ϣ����
	{
		errorFlag=false;
	}
	else
	{
		for(int i=16;i<32;i++)//���������Ϣ
		{
			if(LCDManager->XBOT_LcdData[i]!=0)
			{
				errorFlag=true;
				break;
			}
		}
	}
	if(errorFlag)//�������
	{
		for(int i=16;i<32;i++)//��������Ϣ 0x05 0x06 0x07 //��ת���¶ȹ���
		{
			if(index>3)
				break;
			if(LCDManager->XBOT_LcdData[i]>0x0a)
			{
				error[index]=((i-16)<<4)|((LCDManager->XBOT_LcdData[i]-0x06)&0x0f);
				index++;
			}
		}
		for(int i=16;i<32;i++)//��⾯����Ϣ 0X02 0x03 0x04
		{
			if(index>3)
				break;
			if(LCDManager->XBOT_LcdData[i]==0x08||LCDManager->XBOT_LcdData[i]==0x09||LCDManager->XBOT_LcdData[i]==0x0a)
			{
				error[index]=((i-16)<<4)|((LCDManager->XBOT_LcdData[i]-0x06)&0x0f);
				index++;
			}
		}
		for(int i=16;i<32;i++)//�����ʾ��Ϣ �ؽڸ��� 0X01 
		{
			if(index>3)
				break;
			if(LCDManager->XBOT_LcdData[i]>0x00&&LCDManager->XBOT_LcdData[i]<0x08)
			{
				error[index]=((i-16)<<4)|0x01;
				index++;
			}
		}
	}
	if(backErrorFlag==false&&errorFlag==false)				//�ϴ��ޣ�������
	{
		backError[0]=0;
		backError[1]=0;
		backError[2]=0;
		backError[3]=0;
		backErrorStatus=0;
	}
	else if(backErrorFlag==true&&errorFlag==false)		//�ϴ��У�������
	{
		backErrorFlag=false;
		backError[0]=0;
		backError[1]=0;
		backError[2]=0;
		backError[3]=0;
		backErrorStatus=1;
	}
	else if(backErrorFlag==false&&errorFlag==true)		//�ϴ��ޣ�������
	{
		backErrorFlag=true;
		backError[0]=error[0];
		backError[1]=error[1];
		backError[2]=error[2];
		backError[3]=error[3];
		backErrorStatus=2;
		backErrorStatus|=((index-1)<<6);								//��ʾ�ĸ���
	}
	else if(backErrorFlag==true&&errorFlag==true)			//�ϴ��У�������
	{
		if(backError[0]!=error[0])
			backErrorStatus|=(0x20);
		if(backError[1]!=error[1])
			backErrorStatus|=(0x10);
		if(backError[2]!=error[2])
			backErrorStatus|=(0x08);
		if(backError[3]!=error[3])
			backErrorStatus|=(0x04);
		
		backErrorStatus|=0x03;
		backErrorStatus|=((index-1)<<6); 								//��ʾ�ĸ���
		backError[0]=error[0];
		backError[1]=error[1];
		backError[2]=error[2];
		backError[3]=error[3];
	}
	return backErrorStatus;
}
/**
  * ��  �ܣ���ʾ����������Ϣ
  * ��  ����
  * 	amount:		��������
  * 	position:	��ʾ��λ��
  * 	error:		������Ϣ
  * ����ֵ����
  */

void XbotDisplayApp::disOneError(uint8_t amount,uint8_t position,uint8_t error)						//��ʾ�������Ϣ
{
	if(error==0)
	{
		return;
	}
	int8_t errorID=((error&0xf0)>>4)+ERRORSTRAT; 				//�������ڵ��豸ͼƬID 20-35 

	int8_t errorType=error&0x0f;												//�������ڵ�λ�� 1 2 3 4 5 6 7����������
	if(errorType>7)																			//����ı�� ���Ͳ��Ϸ�
	{
		errorID=36;
		errorType=1;
	}
	if(amount==1)
		LCDManager->CutPicAndShow(errorID,71,19+27*errorType,234,22,71,105);
	else if(amount==2)
		LCDManager->CutPicAndShow(errorID,71,19+27*errorType,234,22,71,88+53*position);
	else if(amount==3)
		LCDManager->CutPicAndShow(errorID,71,19+27*errorType,234,22,71,73+41*position);
	else if(amount==4)
		LCDManager->CutPicAndShow(errorID,71,19+27*errorType,234,22,71,73+27*position);
}
/**
  * ��  �ܣ���˸��ʾ����ͼ��
  * ��  ������
  * ����ֵ����
  */
void XbotDisplayApp::disErrorIcon()											//��ʾ����ͼ��
{
	static uint16_t Timer=0;
	if(Timer==0)
	{
		LCDManager->CutPicAndShow(ERRORBACKPAGENUM,112,33,158,28,112,33);
		LCDManager->CutPicAndShow(ERRORBACKPAGENUM,171,193,136,25,171,193);
	}
	else if(Timer==0xff)
	{
		LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,112,33,158,28,112,33);
		LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,171,193,136,25,171,193);
	}
	Timer++;
	Timer&=0x01ff;
}


/**
  * ��  �ܣ���ʾ������Ϣ
  * ��  ����
  * 	true:ǿ����ʾ
  * 	false:��ǿ����ʾ
  * ����ֵ��
  * 	true:		����ʾ
  * 	false:	����ʾ
  */
bool XbotDisplayApp::disError(bool staflag)							//��ʾ������Ϣ
{
	static uint8_t backErrorStatus=0;
	errorStatus=checkError();
	//�Ȳ鿴������Ϣ��ʾ
	int8_t errorNum=0;	//�������
	if(errorStatus==0)	//�ϴ��ޣ�������
	{
		backErrorStatus=errorStatus;
		return false;
	}
	if(staflag)//ǿ����ʾ
	{
		//���и���ʾ����
		backErrorStatus=errorStatus;
		if(errorStatus>1)//������
		{
			if(interfaceIndex==1)			//�Ƕ���ʾ������
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,252,195,62,27); //��ʾ����
			else if(interfaceIndex==0)//���˵���
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,257,195,62,27); //��ʾ����
			else 											//����������
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,50,27,268,195,50,27); //��ʾ����
			errorNum=((errorStatus&0xc0)>>6)+1;//�������  1 2 3 4 
			for(int i=0;i<errorNum;i++)
			{
				disOneError(errorNum,i,error[i]);//��ʾ�������Ϣ
			}
			return true;
		}
		else
			return false;
	}
	else //��ǿ��ˢ�£������ϴεĽ����ʾ���ε�����
	{
		if(errorStatus==1)//�ϴ��У������� ,��ԭͼ��
		{
			backErrorStatus=errorStatus;
			if(interfaceIndex==1)			//�Ƕ���ʾ������
				LCDManager->CutPicAndShow(pageID,62,27,252,195,62,27); //��ʾ����
			else if(interfaceIndex==0)//���˵���
				LCDManager->CutPicAndShow(pageID,62,27,257,195,62,27); //��ʾ����
			else 											//����������
				LCDManager->CutPicAndShow(pageID,50,27,268,195,50,27); //��ʾ����
			return false;
		}
		else if((errorStatus&0x03)==2)//�ϴ��ޣ�������
		{
			backErrorStatus=errorStatus;
			if(interfaceIndex==1)			//�Ƕ���ʾ������
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,252,195,62,27); //��ʾ����
			else if(interfaceIndex==0)//���˵���
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,257,195,62,27); //��ʾ����
			else 											//����������
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,50,27,268,195,50,27); //��ʾ����
			errorNum=((errorStatus&0xc0)>>6)+1;//�������
			for(int i=0;i<errorNum;i++)
			{
				disOneError(errorNum,i,error[i]);//��ʾ�������Ϣ
			}
			disErrorIcon();//��˸ͼ��
			return true;
		}
		else //�ϴ��У�������
		{
// 			if(((errorStatus&0x10)&&(error[1]==0))||((errorStatus&0x08)&&(error[2]==0))||((errorStatus&0x04)&&(error[3]==0)))//��⵽��ʾ�����б仯,ֻ�ܼ�⵽�ɶ����
			if((errorStatus&0xc0)!=(backErrorStatus&0xc0))	//�������б仯
			{
			if(interfaceIndex==1)			//�Ƕ���ʾ������
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,252,195,62,27); //��ʾ����
			else if(interfaceIndex==0)//���˵���
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,62,27,257,195,62,27); //��ʾ����
			else 											//����������
				LCDManager->CutPicAndShow(ERRORBACKPAGENUM_1,50,27,268,195,50,27); //��ʾ����
				errorNum=((errorStatus&0xc0)>>6)+1;//�������
				for(int i=0;i<errorNum;i++)
				{
					disOneError(errorNum,i,error[i]);//��ʾ�������Ϣ
				}
				disErrorIcon();//��˸ͼ��
				backErrorStatus=errorStatus;
				return true;
			}
			else//����û�б仯
			{
				if(errorStatus!=backErrorStatus)
				{
					errorNum=((errorStatus&0xc0)>>6)+1;//�������
					for(int i=0;i<errorNum;i++)
					{
						if((errorStatus&(0x20>>i))!=0)					 //�������������ޱ仯
							disOneError(errorNum,i,error[i]);//��ʾ�������Ϣ
					}
				}
// 				errorNum=((errorStatus&0xc0)>>6)+1;//�������
// 				for(int i=0;i<errorNum;i++)
// 				{
// 					if((errorStatus&(0x20>>i))!=0)					 //�������������ޱ仯
// 						disOneError(errorNum,i,error[i]);//��ʾ�������Ϣ
// 				}
				disErrorIcon();//��˸ͼ��
				backErrorStatus=errorStatus;
				return true;
			}
		}
	}
}
/**
  * ��  �ܣ���ʾ��������
  * ��  ������
  * ����ֵ����
  */
void XbotDisplayApp::disPageStart()											//��ʾ��������
{
	static uint16_t timer=0;
	//�������
	
	if(LCDManager->fireFlag!=0x00&&timer<800)
	{
		timer++;
		return;
	}
	if(timer==0)
	{
		LCDManager->ShowPic(STARTPAGENUM);									
		timer++;
	}
	else if(timer<500)																		//��ʱ1.5�� �ȴ���Ϣ�ռ����
	{
		timer++;
		LCDManager->movePic(0x61,38,144,279,148,1);
	}
	else if(timer<800)
	{
		timer++;
	}		
	else if(timer==800)
	{
		interfaceIndex=0;																		//��ʾ���˵�����
		timer++;
	}
}

/**
  * ��  �ܣ���ʾ���˵�����
  * ��  ����
	* key:			���ΰ�����ֵ
	* backKey:	�ϴΰ�����ֵ
  * ����ֵ����
  */
void XbotDisplayApp::disPageMain(int8_t key,int8_t backKey,bool updateFlag)					//��ʾ���˵�����
{
	static bool firstDis=false;
	static uint8_t backWireLength=0;
	if(interfaceIndex!=0)
		return;
	//��Ϣ���洦��
	if(!firstDis)//��һ����ʾ
	{
		firstDis=true;
		if(LCDManager->WireLength==0)//���߻�����ͨ���¿���
		{
			pageID=MAINPAGENUM;
			LCDManager->ShowPic(pageID);
			if(!disError(true))//ǿ����ʾ������Ϣ������fasle�������������
			{
				LCDManager->showVoltageAndSpeed();
				LCDManager->ShowCtrlSpeed(true);
			}
		}
		else 
		{
			pageID=MAINPAGENUM_1;
			LCDManager->ShowPic(pageID);
			if(!disError(true))//ǿ����ʾ������Ϣ������fasle�������������
			{
				LCDManager->ShowCtrlSpeed_1(true);
				LCDManager->showVoltageAndSpeed_1();
			}
		}
		LCDManager->ShowBattery(true);				//��ʾ��ص���
		LCDManager->ShowSignal(true);					//��ʾ�ź�ǿ��
		backWireLength=LCDManager->WireLength;
// 		return;
	}
	switch(keysValue) //��ⰴ��
	{
		case -1://������λ
			if(backKey==0)//M������
			{
				workMode=MODE_NULL;	//ȡ��״̬
				setMainButtonNormal(MAINBUTTON_M);
			}
			else if(backKey==1)//A������
			{
				interfaceIndex=1;//����Ƕ���ʾ����
				firstDis=false;
				return;
			}
			else if(backKey==2)
			{
				interfaceIndex=2;//����ڱۿ��ƽ���
				firstDis=false;
				return;
			}
			else if(backKey==3)
			{
				interfaceIndex=3;//�����ֱۿ��ƽ���
				firstDis=false;
				return;
			}
			else if(backKey==4)
			{
				interfaceIndex=4;//�����������ƽ���
				firstDis=false;
				return;
			}
			else if(backKey==5)
			{
				interfaceIndex=5;//����Ӧ�����ƽ���
				firstDis=false;
				return;
			}
			break;
		case 0:	//M������
			if(backKey!=0)
			setMainButtonPress(MAINBUTTON_M);//M������ɰ���״̬
			break;
		case 1:	//A������
			if(backKey!=1)
			setMainButtonPress(MAINBUTTON_A);//A������ɰ���״̬
			break;
		case 2:	//B������
			if(backKey!=2)
			setMainButtonPress(MAINBUTTON_B);//B������ɰ���״̬
			break;
		case 3://C������
			if(backKey!=3)
			setMainButtonPress(MAINBUTTON_C);//C������ɰ���״̬
			break;	
		case 4://D������
			if(backKey!=4)
			setMainButtonPress(MAINBUTTON_D);//D������ɰ���״̬
			break;
		case 5://ABD��ͬʱ���� �������ؽ���
			if(backKey!=5)
			{
				setMainButtonPress(MAINBUTTON_A);//ABD������ɰ���״̬
				setMainButtonPress(MAINBUTTON_B);
				setMainButtonPress(MAINBUTTON_D);
			}
			break;
	}
	if(LCDManager->WireLength==0&&backWireLength!=0)//������ʾ
	{
		pageID=MAINPAGENUM;
		LCDManager->ShowPic(pageID);
		if(!disError(true))//ǿ����ʾ������Ϣ������fasle�������������
		{
			LCDManager->showVoltageAndSpeed();
			LCDManager->ShowCtrlSpeed(true);
		}

		LCDManager->ShowBattery(true);				//��ʾ��ص���
		LCDManager->ShowSignal(true);					//��ʾ�ź�ǿ��
		backWireLength=LCDManager->WireLength;
	}
	else if(LCDManager->WireLength!=0&&backWireLength==0)//������ʾ
	{
		pageID=MAINPAGENUM_1;
		LCDManager->ShowPic(pageID);
		if(!disError(true))//ǿ����ʾ������Ϣ������fasle�����޴�������
		{
			LCDManager->showVoltageAndSpeed_1();
			LCDManager->ShowCtrlSpeed_1(true);
		}
		LCDManager->ShowBattery(true);				//��ʾ��ص���
		LCDManager->ShowSignal(true);					//��ʾ�ź�ǿ��
		backWireLength=LCDManager->WireLength;	
	}
	else
	{
		if(LCDManager->WireLength==0)
		{
			if(!disError(false)) //�޴���
			{
				LCDManager->ShowCtrlSpeed(false);
				if(updateFlag)
					LCDManager->showVoltageAndSpeed();//���µ�һ֡����
			}
		}
		else
		{
			if(!disError(false)) //�޴���
			{
				LCDManager->ShowCtrlSpeed_1(false);
				if(updateFlag)
					LCDManager->showVoltageAndSpeed_1();//���µ�һ֡����
			}
		}
		LCDManager->ShowBattery(false);				//��ʾ��ص���
		LCDManager->ShowSignal(false);				//��ʾ�ź�ǿ��
	}
}

/**
  * ��  �ܣ���ʾ�Ƕ���Ϣ����
  * ��  ����
	* key:			���ΰ�����ֵ
	* backKey:	�ϴΰ�����ֵ
  * ����ֵ����
  */
void XbotDisplayApp::disPageAngle(int8_t key,int8_t backKey,bool updateFlag)					//��ʾ�ǶȽ���
{
	static bool firstDis=false;
	static bool haveError=false;//�Ƿ��д�����Ϣ
	bool haveError_1=false;			//�Ƿ��д�����Ϣ
	if(interfaceIndex!=1)
		return;
	//��Ϣ���洦��
	if(!firstDis)//��һ����ʾ
	{
		firstDis=true;
		pageID=ANGLEPAGENUM;
		LCDManager->ShowPic(pageID);
		LCDManager->ShowBattery(true);				//��ʾ��ص���
		LCDManager->ShowSignal(true);					//��ʾ�ź�ǿ��
		haveError=disError(true);
		if(!haveError)//ǿ����ʾ������Ϣ������fasle�������������
			LCDManager->showAngle(195,208,true);//ǿ��ˢ�½Ƕ�

// 		return;
	}
	if(keysValue==-1) //��ⰴ��
	{
		if(backKey==0)//M������
		{
			interfaceIndex=0;//�������˵���ʾ����
			firstDis=false;
			return;
		}
	}
	LCDManager->ShowBattery(false);				//��ʾ��ص���
	LCDManager->ShowSignal(false);					//��ʾ�ź�ǿ��
	haveError_1=disError(false);
	if(!haveError_1)//����û�д�����Ϣ�������µ�һ֡����
	{
		if(haveError)//�ϴ��У������ޣ�ǿ��ˢ��
			LCDManager->showAngle(195,208,haveError);
		else if(updateFlag)//�ϴ��ޣ������ޣ��������µ�һ֡����
			LCDManager->showAngle(195,208,haveError);
	}
	haveError=haveError_1;

}
/**
  * ��  �ܣ���ʾ�ڱۿ��ƽ���
  * ��  ����
	* key:			���ΰ�����ֵ
	* backKey:	�ϴΰ�����ֵ
  * ����ֵ����
  */

void XbotDisplayApp::disPageSwingArmCtrl(int8_t key,int8_t backKey)	//��ʾ�ڱۿ��ƽ���
{
	static bool firstDis=false;
	static bool haveError=false;//�Ƿ��д�����Ϣ
	bool haveError_1=false;			//�Ƿ��д�����Ϣ
	if(interfaceIndex!=2)
		return;
	//��Ϣ���洦��
	if(!firstDis)//��һ����ʾ
	{
		firstDis=true;
		pageID=SWINGARMCTRLPAGENUM;
		LCDManager->ShowPic(pageID);
		if(workMode==MODE_SHOULDER_A)//ǿ����ʾ��ť
		{
			setButtonChecked(BUTTON_A);
		}
		else if(workMode==MODE_SHOULDER_B)
		{
			setButtonChecked(BUTTON_B);
		}
		else if(workMode==MODE_SHOULDER_C)
		{
			setButtonChecked(BUTTON_C);
		}
		else if(workMode==MODE_SHOULDER_D)
		{
			setButtonChecked(BUTTON_D);
		}
		haveError=disError(true);
		if(!haveError)//ǿ����ʾ������Ϣ������fasle�������������
		{
			disSwingArmWorkMode(true);
		}
		LCDManager->ShowBattery(true);				//��ʾ��ص���
		LCDManager->ShowSignal(true);					//��ʾ�ź�ǿ��
		return;
	}
	switch(keysValue) //��ⰴ��
	{
		case -1://������λ
			if(backKey==0)//M������
			{
				interfaceIndex=0;//�������˵���ʾ����
				firstDis=false;
				return;
			}
			else if(backKey==1)//A������
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,1,69,46,145,1,69);//�����еİ���������
				setWorkMode(MODE_SHOULDER_A);
				if(workMode==MODE_SHOULDER_A)
					setButtonChecked(BUTTON_A);
			}
			else if(backKey==2)//B������
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,1,69,46,145,1,69);//�����еİ���������
				setWorkMode(MODE_SHOULDER_B);
				if(workMode==MODE_SHOULDER_B)
					setButtonChecked(BUTTON_B);
			}
			else if(backKey==3)//C������
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,1,69,46,145,1,69);//�����еİ���������
				setWorkMode(MODE_SHOULDER_C);
				if(workMode==MODE_SHOULDER_C)
					setButtonChecked(BUTTON_C);
			}
			else if(backKey==4)//D������
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,1,69,46,145,1,69);//�����еİ���������
				setWorkMode(MODE_SHOULDER_D);
				if(workMode==MODE_SHOULDER_D)
					setButtonChecked(BUTTON_D);
			}
			break;
		case 0:	//M������
			if(backKey!=0)
			setButtonPress(BUTTON_M);//M������ɰ���״̬
			break;
		case 1:	//A������
			if(backKey!=1)
			
			setButtonPress(BUTTON_A);//A������ɰ���״̬
			break;
		case 2:	//B������
			if(backKey!=2)

			setButtonPress(BUTTON_B);//B������ɰ���״̬
			break;
		case 3://C������
			if(backKey!=3)

			setButtonPress(BUTTON_C);//C������ɰ���״̬
			break;	
		case 4://D������
			if(backKey!=4)

			setButtonPress(BUTTON_D);//D������ɰ���״̬
			break;
	}
	haveError_1=disError(false);
	if(!haveError_1)//����û�д�����Ϣ
	{
		disSwingArmWorkMode(haveError);
	}
	haveError=haveError_1;
	LCDManager->ShowBattery(false);				//��ʾ��ص���
	LCDManager->ShowSignal(false);					//��ʾ�ź�ǿ��
}

/**
  * ��  �ܣ���ʾ�ֱۿ��ƽ���
  * ��  ����
	* key:			���ΰ�����ֵ
	* backKey:	�ϴΰ�����ֵ
  * ����ֵ����
  */
void XbotDisplayApp::disPageArmCtrl(int8_t key,int8_t backKey)				//��ʾ�ֱۿ��ƽ���
{
	static bool firstDis=false;
	static bool haveError=false;//�Ƿ��д�����Ϣ
	bool haveError_1=false;			//�Ƿ��д�����Ϣ
	if(interfaceIndex!=3)
		return;
	//��Ϣ���洦��
	if(!firstDis)//��һ����ʾ
	{
		firstDis=true;
		pageID=ARMCTRLPAGENUM;
		LCDManager->ShowPic(pageID);
		if(workMode==MODE_ARM_CA)//ǿ����ʾ��ť
		{
			setButtonChecked(BUTTON_A);
		}
		else if(workMode==MODE_ARM_CB)
		{
			setButtonChecked(BUTTON_B);
		}
		else if(workMode==MODE_ARM_CC)
		{
			setButtonChecked(BUTTON_C);
		}
		else if(workMode==MODE_ARM_3D)
		{
			setButtonChecked(BUTTON_D);
		}
		haveError=disError(true);
		if(!haveError)//ǿ����ʾ������Ϣ������fasle�������������
		{
			disArmWorkMode(true);
		}
		LCDManager->ShowBattery(true);				//��ʾ��ص���
		LCDManager->ShowSignal(true);					//��ʾ�ź�ǿ��
		return;
	}
	switch(keysValue) //��ⰴ��
	{
		case -1://������λ
			if(backKey==0)//M������
			{
				interfaceIndex=0;//�������˵���ʾ����
				firstDis=false;
				return;
			}
			else if(backKey==1)//A������
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,3,71,42,141,3,71);//�����еİ���������
				setWorkMode(MODE_ARM_CA);
				if(workMode==MODE_ARM_CA)
					setButtonChecked(BUTTON_A);
			}
			else if(backKey==2)//B������
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,3,71,42,141,3,71);//�����еİ���������
				setWorkMode(MODE_ARM_CB);
				if(workMode==MODE_ARM_CB)
					setButtonChecked(BUTTON_B);
			}
			else if(backKey==3)//C������
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,3,71,42,141,3,71);//�����еİ���������
				setWorkMode(MODE_ARM_CC);
				if(workMode==MODE_ARM_CC)
					setButtonChecked(BUTTON_C);
			}
			else if(backKey==4)//D������
			{
				LCDManager->CutPicAndShow(ARMCTRLPAGENUM,3,71,42,141,3,71);//�����еİ���������
				setWorkMode(MODE_ARM_3D);
				if(workMode==MODE_ARM_3D)
					setButtonChecked(BUTTON_D);
			}
			break;
		case 0:	//M������
			if(backKey!=0)
			setButtonPress(BUTTON_M);//M������ɰ���״̬
			break;
		case 1:	//A������
			if(backKey!=1)
			
			setButtonPress(BUTTON_A);//A������ɰ���״̬
			break;
		case 2:	//B������
			if(backKey!=2)

			setButtonPress(BUTTON_B);//B������ɰ���״̬
			break;
		case 3://C������
			if(backKey!=3)

			setButtonPress(BUTTON_C);//C������ɰ���״̬
			break;	
		case 4://D������
			if(backKey!=4)

			setButtonPress(BUTTON_D);//D������ɰ���״̬
			break;
	}
	haveError_1=disError(false);
	if(!haveError_1)//����û�д�����Ϣ
	{
		disArmWorkMode(haveError);
	}
	haveError=haveError_1;
	LCDManager->ShowBattery(false);				//��ʾ��ص���
	LCDManager->ShowSignal(false);					//��ʾ�ź�ǿ��
}

/**
  * ��  �ܣ���ʾ�������ƽ���
  * ��  ����
	* key:			���ΰ�����ֵ
	* backKey:	�ϴΰ�����ֵ
  * ����ֵ����
  */
void XbotDisplayApp::disPageOtherCtrl(int8_t key,int8_t backKey)			//��ʾ�������ƽ���
{
	static bool firstDis=false;
	static bool haveError=false;//�Ƿ��д�����Ϣ
	static uint8_t backWireLength=0;
	bool haveError_1=false;			//�Ƿ��д�����Ϣ
	if(interfaceIndex!=4)
		return;
	//��Ϣ���洦��
	if(!firstDis)//��һ����ʾ
	{
		firstDis=true;
		if(LCDManager->WireLength==0)
			pageID=OTHERCTRLPAGENUM;
		else
			pageID=OTHERCTRLPAGENUM1;
		LCDManager->ShowPic(pageID);
		if(workMode==MODE_CAMERA_A)//ǿ����ʾ��ť
		{
			setButtonChecked(BUTTON_A);
		}
		else if(workMode==MODE_CAMERA_B)
		{
			setButtonChecked(BUTTON_B);
		}
		else if(workMode==MODE_ARM_DC)
		{
			setButtonChecked(BUTTON_C);
		}
		else if(workMode==MODE_ARM_DD)
		{
			setButtonChecked(BUTTON_D);
		}
		haveError=disError(true);
		if(!haveError)//ǿ����ʾ������Ϣ������fasle�������������
		{
			disOtherWorkMode(true);
		}
		LCDManager->ShowBattery(true);				//��ʾ��ص���
		LCDManager->ShowSignal(true);					//��ʾ�ź�ǿ��
		backWireLength=LCDManager->WireLength;
		return;
	}
	switch(keysValue) //��ⰴ��
	{
		case -1://������λ
			if(backKey==0)//M������
			{
				interfaceIndex=0;//�������˵���ʾ����
				firstDis=false;
				return;
			}
			else if(backKey==1)//A������
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,3,71,42,141,3,71);//�����еİ���������
				if(LCDManager->WireLength==0)//����״̬
				{
					setWorkMode(MODE_CAMERA_A);
					if(workMode==MODE_CAMERA_A)
						setButtonChecked(BUTTON_A);
				}
				else
				{
					workMode=MODE_NULL;
				}
			}
			else if(backKey==2)//B������
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,3,71,42,141,3,71);//�����еİ���������
				if(LCDManager->WireLength==0)//����״̬
				{
					setWorkMode(MODE_CAMERA_B);
					if(workMode==MODE_CAMERA_B)
						setButtonChecked(BUTTON_B);
				}
				else
				{
					workMode=MODE_NULL;
				}
			}
			else if(backKey==3)//C������
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,3,71,42,141,3,71);//�����еİ���������
				setWorkMode(MODE_ARM_DC);
				if(workMode==MODE_ARM_DC)
					setButtonChecked(BUTTON_C);
			}
			else if(backKey==4)//D������
			{
				LCDManager->CutPicAndShow(SWINGARMCTRLPAGENUM,3,71,42,141,3,71);//�����еİ���������
				setWorkMode(MODE_ARM_DD);
				if(workMode==MODE_ARM_DD)
					setButtonChecked(BUTTON_D);
			}
			break;
		case 0:	//M������
			if(backKey!=0)
			setButtonPress(BUTTON_M);//M������ɰ���״̬
			break;
		case 1:	//A������
			if(backKey!=1)
			{
				if(LCDManager->WireLength==0)
					setButtonPress(BUTTON_A);//A������ɰ���״̬
				else
				{
					setButtonChecked(BUTTON_A);
					workMode=MODE_CAMERA_A;
				}
			}

			break;
		case 2:	//B������
			if(backKey!=2)
			{
				if(LCDManager->WireLength==0)
					setButtonPress(BUTTON_B);//A������ɰ���״̬
				else
				{
					setButtonChecked(BUTTON_B);
					workMode=MODE_CAMERA_B;
				}
			}
			break;
		case 3://C������
			if(backKey!=3)

			setButtonPress(BUTTON_C);//C������ɰ���״̬
			break;	
		case 4://D������
			if(backKey!=4)

			setButtonPress(BUTTON_D);//D������ɰ���״̬
			break;
	}
	if(LCDManager->WireLength==0&&backWireLength!=0)//������ʾ
	{
		pageID=OTHERCTRLPAGENUM;
		LCDManager->ShowPic(pageID);
		haveError=disError(true);
		if(!haveError)//����û�д�����Ϣ
		{
			disOtherWorkMode(true);
		}
		if(workMode==MODE_CAMERA_A)//ǿ����ʾ��ť
		{
			setButtonChecked(BUTTON_A);
		}
		else if(workMode==MODE_CAMERA_B)
		{
			setButtonChecked(BUTTON_B);
		}
		else if(workMode==MODE_ARM_DC)
		{
			setButtonChecked(BUTTON_C);
		}
		else if(workMode==MODE_ARM_DD)
		{
			setButtonChecked(BUTTON_D);
		}
		LCDManager->ShowBattery(true);				//��ʾ��ص���
		LCDManager->ShowSignal(true);					//��ʾ�ź�ǿ��
		backWireLength=LCDManager->WireLength;
	}
	else if(LCDManager->WireLength!=0&&backWireLength==0)//������ʾ
	{
		pageID=OTHERCTRLPAGENUM1;
		LCDManager->ShowPic(pageID);
		haveError=disError(true);
		if(!haveError)//����û�д�����Ϣ
		{
			disOtherWorkMode(true);
		}
		if(workMode==MODE_CAMERA_A)//ǿ����ʾ��ť
		{
			setButtonChecked(BUTTON_A);
		}
		else if(workMode==MODE_CAMERA_B)
		{
			setButtonChecked(BUTTON_B);
		}
		else if(workMode==MODE_ARM_DC)
		{
			setButtonChecked(BUTTON_C);
		}
		else if(workMode==MODE_ARM_DD)
		{
			setButtonChecked(BUTTON_D);
		}
		LCDManager->ShowBattery(true);				//��ʾ��ص���
		LCDManager->ShowSignal(true);					//��ʾ�ź�ǿ��
		backWireLength=LCDManager->WireLength;
	}
	else
	{		
		haveError_1=disError(false);
		if(!haveError_1)//����û�д�����Ϣ
		{
			disOtherWorkMode(haveError);
		}
		haveError=haveError_1;
		LCDManager->ShowBattery(false);				//��ʾ��ص���
		LCDManager->ShowSignal(false);					//��ʾ�ź�ǿ��
	}
}



/**
  * ��  �ܣ���ʾӦ�����ƽ���
  * ��  ����
	* key:			���ΰ�����ֵ
	* backKey:	�ϴΰ�����ֵ
  * ����ֵ����
  */
void XbotDisplayApp::disPageDubugCtrl(int8_t key,int8_t backKey)			//��ʾӦ�����ƽ���
{
	static bool firstDis=false;
	if(interfaceIndex!=5)
		return;
	//��Ϣ���洦��
	if(!firstDis)//��һ����ʾ
	{
		firstDis=true;
		pageID=DEBUGCTRLPAGENUM;
		LCDManager->ShowPic(pageID);
// 		disError(true);											//�ý��治��ʾ����
		LCDManager->ShowBattery(true);				//��ʾ��ص���
		LCDManager->ShowSignal(true);					//��ʾ�ź�ǿ��
		if(enabledShowError==false)						//��ֹ������ʾ����
		{
			LCDManager->CutPicAndShow(DEBUGCTRLPAGENUM_1,206,133,107,29,206,133);
		}
		return;
	}
	switch(keysValue) //��ⰴ��
	{
		case -1://������λ
			if(backKey==0)//M������
			{
				interfaceIndex=0;//�������˵���ʾ����
				firstDis=false;
				return;
			}
			else if(backKey==1)//A������
			{
				setButtonNormal(BUTTON_A);
			}
			else if(backKey==2)//B������
			{
				setButtonNormal(BUTTON_B);
			}
			else if(backKey==3)//C������
			{
				setButtonNormal(BUTTON_C);
				if(enabledShowError==true)
				{
					enabledShowError=false;
					LCDManager->CutPicAndShow(DEBUGCTRLPAGENUM_1,206,133,107,29,206,133);
				}
				else
				{
					LCDManager->CutPicAndShow(DEBUGCTRLPAGENUM,206,133,107,29,206,133);
					enabledShowError=true;
				}
			}
			else if(backKey==4)//D������ ��Ӣ���л�
			{
				setButtonNormal(BUTTON_D);
				if(languagePosition==CHINESE)
				{
					languagePosition=ENGLISH;
#ifndef ABROAD	
					LCDManager->setLanguageBuf(0xEE);//����������BUF
#endif
				}
				else
				{
					languagePosition=CHINESE;
#ifndef ABROAD
					LCDManager->setLanguageBuf(0x00);//����������BUF
#endif
				}
				//������ʾ��ǰ����
				LCDManager->setAnglePic(ANGLEPAGENUM);
				pageID=DEBUGCTRLPAGENUM;
				LCDManager->ShowPic(pageID);
				LCDManager->ShowBattery(true);				//��ʾ��ص���
				LCDManager->ShowSignal(true);					//��ʾ�ź�ǿ��
				if(enabledShowError==false)						//��ֹ������ʾ����
				{
					LCDManager->CutPicAndShow(DEBUGCTRLPAGENUM_1,206,133,107,29,206,133);
				}
			}
			break;
		case 0:	//M������
			if(backKey!=0)
			setButtonPress(BUTTON_M);//M������ɰ���״̬
			break;
		case 1:	//A������
			if(backKey!=1)
			setButtonPress(BUTTON_A);//A������ɰ���״̬
			workMode=MODE_NULL;
			debugMode=DEBUF_CANCEL;//ȡ����λ
			break;
		case 2:	//B������
			if(backKey!=2)
			setButtonPress(BUTTON_B);//B������ɰ���״̬
			workMode=MODE_NULL;
			debugMode=DEBUF_RESET;//������λ
			break;
		case 3://C������
			if(backKey!=3)
			setButtonPress(BUTTON_C);//C������ɰ���״̬
			break;	
		case 4://D������
			if(backKey!=4)
			setButtonPress(BUTTON_D);//D������ɰ���״̬
			break;
	}
// 	disError(false);//�ý��治��ʾ����
	LCDManager->ShowBattery(false);				//��ʾ��ص���
	LCDManager->ShowSignal(false);					//��ʾ�ź�ǿ��
}

/**
  * ��  �ܣ���ʾ�������ƽ���
  * ��  ����
	* key:			���ΰ�����ֵ
	* backKey:	�ϴΰ�����ֵ
  * ����ֵ��ˮ�ڴ�
  */
bool XbotDisplayApp::disPageWeaponCtrl()		//��ʾ�������ƽ��棬�ý��治��ʾ������Ϣ
{
	static bool fireOpen=false;
	static bool lightFlag=true;
	static bool shootSucceed=false;
	static int8_t lightTimer=0;
	if(LCDManager->fireFlag==0x01&&(!shootSucceed)) //ˮ��Կ�׿��� 
	{
		if(!fireOpen)
		{
			fireOpen=true;
			workMode=MODE_NULL;
			LCDManager->ShowPic(WEAPONCTRLPAGENUM);//
			LCDManager->DisRecentage(0x5a,103,199,305,214);//��ս�����
			LCDManager->ShowBattery(true);				//ǿ����ʾ��ص���
			LCDManager->ShowSignal(true);					//ǿ����ʾ�ź�ǿ��
			return fireOpen;
		}
		else
		{
			lightTimer++;
			lightTimer&=0x07;
			if(lightTimer==0)
			{
				LCDManager->backlightOn();
				lightFlag=true;
			}
			else if(lightTimer==5)
			{
				LCDManager->backlightOff();
				lightFlag=false;
			}
			LCDManager->DisRecentage(0x5a,103,199,305,214);//��ս�����
			LCDManager->ShowBattery(false);					//ǿ����ʾ��ص���
			LCDManager->ShowSignal(false);					//ǿ����ʾ�ź�ǿ��
			return fireOpen;
		}
	}
	else if(LCDManager->fireFlag==0x02&&fireOpen) //ˮ�ڷ���ɹ�
	{
		//��ʾ����ɹ����� OK
		if(!lightFlag)
		{
			lightFlag=true;
			LCDManager->backlightOn();
		}
		if(!shootSucceed)
		{
			//��ʾ3
			LCDManager->ClearScreen();
			LCDManager->DisRecentage(0x5b,117,51,203,69); //
			LCDManager->DisRecentage(0x5b,187,69,203,189); //
			LCDManager->DisRecentage(0x5b,117,111,203,129); //
			LCDManager->DisRecentage(0x5b,117,171,203,189); //
			SysTick_DelayMs(400);//��ʱ
			//��ʾ2
			LCDManager->ClearScreen();
			LCDManager->DisRecentage(0x5b,117,51,203,69); //
			LCDManager->DisRecentage(0x5b,187,69,203,129); //
			LCDManager->DisRecentage(0x5b,117,111,203,129); //
			LCDManager->DisRecentage(0x5b,117,111,133,171); //
			LCDManager->DisRecentage(0x5b,117,171,203,189); //
			SysTick_DelayMs(400);//��ʱ
			//��ʾ1
			LCDManager->ClearScreen();
			LCDManager->DisRecentage(0x5b,152,51,168,189); //
			SysTick_DelayMs(300);//��ʱ
			shootSucceed=true;
// 			LCDManager->DisRecentage(0x5a,103,199,305,215); //��ս�����
			LCDManager->ShowPic(WEAPONCTRLPAGENUM_1);				//��ʾ����ɹ��Ľ���
			LCDManager->ShowBattery(true);									//ǿ����ʾ��ص���
			LCDManager->ShowSignal(true);										//ǿ����ʾ�ź�ǿ��
		}
		else
		{
			LCDManager->ShowBattery(false);									//ǿ����ʾ��ص���
			LCDManager->ShowSignal(false);									//ǿ����ʾ�ź�ǿ��
		}
		return fireOpen;
	}
	else if(LCDManager->fireFlag>0x04&&fireOpen)//��ʾ���������
	{
		//��������
		if(!lightFlag)
		{
			lightFlag=true;
			LCDManager->backlightOn();
		}
		if(!shootSucceed)
			LCDManager->DisRecentage(0x5b,103,199,103+(LCDManager->fireFlag-0x04)*8,214);
		LCDManager->ShowBattery(false);				//ǿ����ʾ��ص���
		LCDManager->ShowSignal(false);					//ǿ����ʾ�ź�ǿ��
		return fireOpen;
	}
	else if(LCDManager->fireFlag>0x01&&(!fireOpen))
	{
		LCDManager->fireFlag=0x00;
		return fireOpen;
	}
	else if(LCDManager->fireFlag==0x00)
	{
		shootSucceed=false;
		if(!lightFlag)
		{
			lightFlag=true;
			LCDManager->backlightOn();
		}
		if(fireOpen)
		{
			fireOpen=false;
// 			if(interfaceIndex>-1)
			{
				LCDManager->ShowPic(pageID);//
				if(interfaceIndex==1)//�Ƕ���Ϣ��ʾ����
				{
					LCDManager->showAngle(195,208,true);//ǿ��ˢ��
				}
			}
			LCDManager->ShowBattery(true);				//ǿ����ʾ��ص���
			LCDManager->ShowSignal(true);					//ǿ����ʾ�ź�ǿ��
		}
		return fireOpen;
	}
	return false;
}

/**
  * ��  �ܣ���ʾ��Ϣ�������
  * ��  ����
	* key:			���ΰ�����ֵ
	* backKey:	�ϴΰ�����ֵ
  * ����ֵ����
  */
// void XbotDisplayApp::disPageWarning()										//��ʾ��Ϣ�������
// {

// }

/**
  * ��  �ܣ������ڶ�ʱ��2�еĺ�������Ҫ���û�ȡ�����ļ�ֵ
  * ��  ������
  * ����ֵ����
  * ��  ע����ʱʱ��20MS ������Ӧʱ����0.2S,ABD������Ӧʱ����5S
  */

void XbotDisplayApp::runOnTime2()
{
	static uint16_t keyIndex = 0;
	
	static bool backKaym=0;
	static bool backKaya=0;
	static bool backKayb=0;
	static bool backKayc=0;
	static bool bacdKayd=0;
// 	static int8_t bacdKeysValue=-1;

	bool kaym=key_M->getValue();
	bool kaya=key_A->getValue();
	bool kayb=key_B->getValue();
	bool kayc=key_C->getValue();
	bool kayd=key_D->getValue();
	maskKeysValue=(kaym<<4)|(kaya<<3)|(kayb<<2)|(kayc<<1)|kayd;
	if(kaym!=backKaym)
	{
		keyIndex=0;
		backKaym=kaym;
	}
	if(kaya!=backKaya)
	{
		keyIndex=0;
		backKaya=kaya;
	}
	if(kayb!=backKayb)
	{
		keyIndex=0;
		backKayb=kayb;
	}
	if(kayc!=backKayc)
	{
		keyIndex=0;
		backKayc=kayc;
	}
	if(kayd!=bacdKayd)
	{
		keyIndex=0;
		bacdKayd=kayd;
	}
	
	if(kaym&&!kaya&&!kayb&&!kayc&&!kayd)
	{
		if(keyIndex>KEYINDEX_MAX)
		{
			keysValue=KM;
		}
		else
			keyIndex++;
	}
	else 	if(!kaym&&kaya&&!kayb&&!kayc&&!kayd)
	{
		if(keyIndex>KEYINDEX_MAX)
		{
			keysValue=KA;
		}
		else
			keyIndex++;
	}
	else 	if(!kaym&&!kaya&&kayb&&!kayc&&!kayd)
	{
		if(keyIndex>KEYINDEX_MAX)
		{
			keysValue=KB;
		}
		else
			keyIndex++;
	}
	else 	if(!kaym&&!kaya&&!kayb&&kayc&&!kayd)
	{
		if(keyIndex>KEYINDEX_MAX)
		{
			keysValue=KC;
		}
		else
			keyIndex++;
	}
	else 	if(!kaym&&!kaya&&!kayb&&!kayc&&kayd)
	{
		if(keyIndex>KEYINDEX_MAX)
		{
			keysValue=KD;
		}
		else
			keyIndex++;
	}
	else 	if(!kaym&&kaya&&kayb&&!kayc&&kayd)
	{
		if(keyIndex>KEYINDEX_ABD_MAX)
		{
			keysValue=KABD;
		}
		else
			keyIndex++;
	}
	else
	{
		keyIndex=0;
		keysValue=-1;
	}
		
	
// 	if(keysValue!=bacdKeysValue)
// 	{
// 		bacdKeysValue=keysValue;
// 		if(keysValue==-1)
// 			terminalPort->writeLine("the key is NULL\r\n");
// 		else 	if(keysValue==0)
// 			terminalPort->writeLine("the key is M\r\n");
// 		else 	if(keysValue==1)
// 			terminalPort->writeLine("the key is A\r\n");
// 		else 	if(keysValue==2)
// 			terminalPort->writeLine("the key is B\r\n");
// 		else 	if(keysValue==3)
// 			terminalPort->writeLine("the key is C\r\n");
// 		else 	if(keysValue==4)
// 			terminalPort->writeLine("the key is D\r\n");
// 		else 	if(keysValue==5)
// 			terminalPort->writeLine("the key is ABD\r\n");
// 		else 
// 			terminalPort->writeLine("the key is error!\r\n");
// 	}
}





/**
  * ��  �ܣ������ڶ�ʱ��3�еĺ���,��Ҫ�����Ǽ������
  * ��  ������
  * ����ֵ����
  * 
  */

void XbotDisplayApp::runOnTime3()
{
	static int8_t backKeysValue=-1;
	static int8_t backWireLength=0;
	bool lcdUpdateFlag=false;
	if(terminalManager->reciveData())								//�µ�һ֡����
	{
		led_1->reverseLight();
		lcdUpdateFlag=updateLCDdata();
		terminalManager->updateSendBuf(workMode,debugMode,maskKeysValue);
		terminalManager->sendcommand();
		if(debugMode!=DEBUF_NULL)
		{
			debugMode=DEBUF_NULL;
		}
		if(disPageWeaponCtrl())
			return;
	}
	disPageStart();
	if(LCDManager->fireFlag!=0x00)
		return;
	if(keysValue>-2&&keysValue<6)//�Ϸ���keyֵ-1 0 1 2 3 4 5 //ˮ��Կ��û�п��� 
	{
		if((backWireLength==0&&LCDManager->WireLength!=0)||(backWireLength!=0&&LCDManager->WireLength==0))//���ߺ��������л�
		{
			if(workMode==MODE_CAMERA_A||workMode==MODE_CAMERA_B)
			{
				workMode=MODE_NULL;
			}
			backWireLength=LCDManager->WireLength;
		}
		disPageMain(keysValue,backKeysValue,lcdUpdateFlag);			//��ʾ���˵�����
		disPageAngle(keysValue,backKeysValue,lcdUpdateFlag);		//��ʾ�ǶȽ���
		disPageSwingArmCtrl(keysValue,backKeysValue);						//��ʾ�ڱۿ��ƽ���
		disPageArmCtrl(keysValue,backKeysValue);								//��ʾ�ֱۿ��ƽ���
		disPageOtherCtrl(keysValue,backKeysValue);							//��ʾ�������ƽ���
		disPageDubugCtrl(keysValue,backKeysValue);							//��ʾӦ�����ƽ���
		if(keysValue!=backKeysValue)
		{
			backKeysValue=keysValue;
		}
	}
}

/**
  * ��  �ܣ������ڶ�ʱ��4�еĺ���
  * ��  ������
  * ����ֵ����
  * 
  */
void XbotDisplayApp::runOnTime4()
{
	uint8_t temLanguge;
	temLanguge=LCDManager->riceveData();
	if(temLanguge==2)
	{
		languagePosition=CHINESE;
		LCDManager->setAnglePic(ANGLEPAGENUM);
	}
	else if(temLanguge==1)//Ӣ��
	{
		languagePosition=ENGLISH;
		LCDManager->setAnglePic(ANGLEPAGENUM);
	}
}





