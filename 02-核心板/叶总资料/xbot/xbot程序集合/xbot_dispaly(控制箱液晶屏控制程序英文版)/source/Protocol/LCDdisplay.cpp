/**
  ******************************************************************************
	*�ļ���LCDdisplay.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ����СҺ����������Э�飬ʵ��СҺ��������ʾ
	*��ע��
  ******************************************************************************  
	*/ 
	/* ͷ�ļ����� ------------------------------------------------------------------*/
	
#include "LCDdisplay.h"

const uint16_t ReviseAngle[10]={6,90,22,3,27,4,40,36,31,11};//�����Ƕ�

const float sinf[360]=
{
0,		    0.01745,	0.03489,	0.05233,	0.06975,	0.08715,	0.10452,	0.12186,	0.13917,	0.15643,	
0.17364,	0.1908,		0.20791,	0.22495,	0.24192,	0.25881,	0.27563,	0.29237,	0.30901,	0.32556,	
0.34202,	0.35836,	0.3746,		0.39073,	0.40673,	0.42261,	0.43837,	0.45399,	0.46947,	0.4848,	
0.49999,	0.51503,	0.52991,	0.54463,	0.55919,	0.57357,	0.58778,	0.60181,	0.61566,	0.62932,	
0.64278,	0.65605,	0.66913,	0.68199,	0.69465,	0.7071,		0.71933,	0.73135,	0.74314,	0.7547,	
0.76604,	0.77714,	0.78801,	0.79863,	0.80901,	0.81915,	0.82903,	0.83867,	0.84804,	0.85716,	
0.86602,	0.87461,	0.88294,	0.891,		0.89879,	0.9063,		0.91354,	0.9205,		0.92718,	0.93358,	
0.93969,	0.94551,	0.95105,	0.9563,		0.96126,	0.96592,	0.97029,	0.97437,	0.97814,	0.98162,	
0.9848,		0.98768,	0.99026,	0.99254,	0.99452,	0.99619,	0.99756,	0.99862,	0.99939,	0.99984,	
1,		    0.99984,	0.99939,	0.99862,	0.99756,	0.99619,	0.99452,	0.99254,	0.99026,	0.98768,	
0.9848,		0.98162,	0.97814,	0.97437,	0.97029,	0.96592,	0.96126,	0.9563,		0.95105,	0.94551,	
0.93969,	0.93358,	0.92718,	0.9205,		0.91354,	0.9063,		0.89879,	0.891,		0.88294,	0.87461,	
0.86602,	0.85716,	0.84804,	0.83867,	0.82903,	0.81915,	0.80901,	0.79863,	0.78801,	0.77714,	
0.76604,	0.7547,		0.74314,	0.73135,	0.71933,	0.7071,		0.69465,	0.68199,	0.66913,	0.65605,	
0.64278,	0.62932,	0.61566,	0.60181,	0.58778,	0.57357,	0.55919,	0.54463,	0.52991,	0.51503,	
0.49999,	0.4848,		0.46947,	0.45399,	0.43837,	0.42261,	0.40673,	0.39073,	0.3746,		0.35836,	
0.34202,	0.32556,	0.30901,	0.29237,	0.27563,	0.25881,	0.24192,	0.22495,	0.20791,	0.1908,	
0.17364,	0.15643,	0.13917,	0.12186,	0.10452,	0.08715,	0.06975,	0.05233,	0.03489,	0.01745,	
0,		    -0.01745,	-0.03489,	-0.05233,	-0.06975,	-0.08715,	-0.10452,	-0.12186,	-0.13917,	-0.15643,	
-0.17364,	-0.1908,	-0.20791,	-0.22495,	-0.24192,	-0.25881,	-0.27563,	-0.29237,	-0.30901,	-0.32556,	
-0.34202,	-0.35836,	-0.3746,	-0.39073,	-0.40673,	-0.42261,	-0.43837,	-0.45399,	-0.46947,	-0.4848,	
-0.5,		-0.51503,	-0.52991,	-0.54463,	-0.55919,	-0.57357,	-0.58778,	-0.60181,	-0.61566,	-0.62932,	
-0.64278,	-0.65605,	-0.66913,	-0.68199,	-0.69465,	-0.7071,	-0.71933,	-0.73135,	-0.74314,	-0.7547,	
-0.76604,	-0.77714,	-0.78801,	-0.79863,	-0.80901,	-0.81915,	-0.82903,	-0.83867,	-0.84804,	-0.85716,	
-0.86602,	-0.87461,	-0.88294,	-0.891,		-0.89879,	-0.9063,	-0.91354,	-0.9205,	-0.92718,	-0.93358,	
-0.93969,	-0.94551,	-0.95105,	-0.9563,	-0.96126,	-0.96592,	-0.97029,	-0.97437,	-0.97814,	-0.98162,	
-0.9848,	-0.98768,	-0.99026,	-0.99254,	-0.99452,	-0.99619,	-0.99756,	-0.99862,	-0.99939,	-0.99984,	
-1,		    -0.99984,	-0.99939,	-0.99862,	-0.99756,	-0.99619,	-0.99452,	-0.99254,	-0.99026,	-0.98768,	
-0.9848,	-0.98162,	-0.97814,	-0.97437,	-0.97029,	-0.96592,	-0.96126,	-0.9563,	-0.95105,	-0.94551,	
-0.93969,	-0.93358,	-0.92718,	-0.9205,	-0.91354,	-0.9063,	-0.89879,	-0.891,		-0.88294,	-0.87461,	
-0.86602,	-0.85716,	-0.84804,	-0.83867,	-0.82903,	-0.81915,	-0.80901,	-0.79863,	-0.78801,	-0.77714,	
-0.76604,	-0.7547,	-0.74314,	-0.73135,	-0.71933,	-0.7071,	-0.69465,	-0.68199,	-0.66913,	-0.65605,	
-0.64278,	-0.62932,	-0.61566,	-0.60181,	-0.58778,	-0.57357,	-0.55919,	-0.54463,	-0.52991,	-0.51503,	
-0.5,		-0.4848,	-0.46947,	-0.45399,	-0.43837,	-0.42261,	-0.40673,	-0.39073,	-0.3746,	-0.35836,	
-0.34202,	-0.32556,	-0.30901,	-0.29237,	-0.27563,	-0.25881,	-0.24192,	-0.22495,	-0.20791,	-0.1908,	
-0.17364,	-0.15643,	-0.13917,	-0.12186,	-0.10452,	-0.08715,	-0.06975,	-0.05233,	-0.03489,	-0.01745

};

const float cosf[360]=
{
1,		    0.99984,	0.99939,	0.99862,	0.99756,	0.99619,	0.99452,	0.99254,	0.99026,	0.98768,	
0.9848,		0.98162,	0.97814,	0.97437,	0.97029,	0.96592,	0.96126,	0.9563,		0.95105,	0.94551,	
0.93969,	0.93358,	0.92718,	0.9205,		0.91354,	0.9063,		0.89879,	0.891,		0.88294,	0.87461,	
0.86602,	0.85716,	0.84804,	0.83867,	0.82903,	0.81915,	0.80901,	0.79863,	0.78801,	0.77714,	
0.76604,	0.7547,		0.74314,	0.73135,	0.71933,	0.7071,		0.69465,	0.68199,	0.66913,	0.65605,	
0.64278,	0.62932,	0.61566,	0.60181,	0.58778,	0.57357,	0.55919,	0.54463,	0.52991,	0.51503,	
0.5,		0.4848,		0.46947,	0.45399,	0.43837,	0.42261,	0.40673,	0.39073,	0.3746,		0.35836,	
0.34202,	0.32556,	0.30901,	0.29237,	0.27563,	0.25881,	0.24192,	0.22495,	0.20791,	0.1908,	
0.17364,	0.15643,	0.13917,	0.12186,	0.10452,	0.08715,	0.06975,	0.05233,	0.03489,	0.01745,	
0,		    -0.01745,	-0.03489,	-0.05233,	-0.06975,	-0.08715,	-0.10452,	-0.12186,	-0.13917,	-0.15643,	
-0.17364,	-0.1908,	-0.20791,	-0.22495,	-0.24192,	-0.25881,	-0.27563,	-0.29237,	-0.30901,	-0.32556,	
-0.34202,	-0.35836,	-0.3746,	-0.39073,	-0.40673,	-0.42261,	-0.43837,	-0.45399,	-0.46947,	-0.4848,	
-0.49999,	-0.51503,	-0.52991,	-0.54463,	-0.55919,	-0.57357,	-0.58778,	-0.60181,	-0.61566,	-0.62932,	
-0.64278,	-0.65605,	-0.66913,	-0.68199,	-0.69465,	-0.7071,	-0.71933,	-0.73135,	-0.74314,	-0.7547,	
-0.76604,	-0.77714,	-0.78801,	-0.79863,	-0.80901,	-0.81915,	-0.82903,	-0.83867,	-0.84804,	-0.85716,	
-0.86602,	-0.87461,	-0.88294,	-0.891,		-0.89879,	-0.9063,	-0.91354,	-0.9205,	-0.92718,	-0.93358,	
-0.93969,	-0.94551,	-0.95105,	-0.9563,	-0.96126,	-0.96592,	-0.97029,	-0.97437,	-0.97814,	-0.98162,	
-0.9848,	-0.98768,	-0.99026,	-0.99254,	-0.99452,	-0.99619,	-0.99756,	-0.99862,	-0.99939,	-0.99984,	
-1,		    -0.99984,	-0.99939,	-0.99862,	-0.99756,	-0.99619,	-0.99452,	-0.99254,	-0.99026,	-0.98768,	
-0.9848,	-0.98162,	-0.97814,	-0.97437,	-0.97029,	-0.96592,	-0.96126,	-0.9563,	-0.95105,	-0.94551,	
-0.93969,	-0.93358,	-0.92718,	-0.9205,	-0.91354,	-0.9063,	-0.89879,	-0.891,		-0.88294,	-0.87461,	
-0.86602,	-0.85716,	-0.84804,	-0.83867,	-0.82903,	-0.81915,	-0.80901,	-0.79863,	-0.78801,	-0.77714,	
-0.76604,	-0.7547,	-0.74314,	-0.73135,	-0.71933,	-0.7071,	-0.69465,	-0.68199,	-0.66913,	-0.65605,	
-0.64278,	-0.62932,	-0.61566,	-0.60181,	-0.58778,	-0.57357,	-0.55919,	-0.54463,	-0.52991,	-0.51503,	
-0.5,		-0.4848,	-0.46947,	-0.45399,	-0.43837,	-0.42261,	-0.40673,	-0.39073,	-0.3746,	-0.35836,	
-0.34202,	-0.32556,	-0.30901,	-0.29237,	-0.27563,	-0.25881,	-0.24192,	-0.22495,	-0.20791,	-0.1908,	
-0.17364,	-0.15643,	-0.13917,	-0.12186,	-0.10452,	-0.08715,	-0.06975,	-0.05233,	-0.03489,	-0.01745,	
0,		    0.01745,	0.03489,	0.05233,	0.06975,	0.08715,	0.10452,	0.12186,	0.13917,	0.15643,	
0.17364,	0.1908,		0.20791,	0.22495,	0.24192,	0.25881,	0.27563,	0.29237,	0.30901,	0.32556,	
0.34202,	0.35836,	0.3746,		0.39073,	0.40673,	0.42261,	0.43837,	0.45399,	0.46947,	0.4848,	
0.5,		0.51503,	0.52991,	0.54463,	0.55919,	0.57357,	0.58778,	0.60181,	0.61566,	0.62932,	
0.64278,	0.65605,	0.66913,	0.68199,	0.69465,	0.7071,		0.71933,	0.73135,	0.74314,	0.7547,	
0.76604,	0.77714,	0.78801,	0.79863,	0.80901,	0.81915,	0.82903,	0.83867,	0.84804,	0.85716,	
0.86602,	0.87461,	0.88294,	0.891,		0.89879,	0.9063,		0.91354,	0.9205,		0.92718,	0.93358,	
0.93969,	0.94551,	0.95105,	0.9563,		0.96126,	0.96592,	0.97029,	0.97437,	0.97814,	0.98162,	
0.9848,		0.98768,	0.99026,	0.99254,	0.99452,	0.99619,	0.99756,	0.99862,	0.99939,	0.99984

};

/**
  * ��  �ܣ�LCDdisplay��Ĺ��캯��
  * ��  ����
	* port��ͨ�ŵĴ��ں�
  * ����ֵ����
  */
LCDdisplay::LCDdisplay(SerialPort *port)
{
	lcddisPort=port;
	//��ʼ�����Ͳ����Ľṹ��
	lcdParameter=new LCDParameter();
	lcdParameter->head=0xaa;
	lcdParameter->command=0x00;
	lcdParameter->end[0]=0xcc;
	lcdParameter->end[1]=0x33;
	lcdParameter->end[2]=0xc3;
	lcdParameter->end[3]=0x3c;
	lcdParameter->len=0x00;
	
	for(int i=0;i<64;i++)
	{
		lcdParameter->buffer[i]=0x00;
	}
	LeftMotorSpeed=0;
	RightMotorSpeed=0;
	LeftCtrlSpeed=0;						//���������ٶ�
	RightCtrlSpeed=0;						//�ҵ�������ٶ�
	XBOT_LcdData=new uint8_t[32];
	XBOT_LcdData[0]=90;
	XBOT_LcdData[1]=90;
	XBOT_LcdData[2]=20;
	XBOT_LcdData[3]=0;
	XBOT_LcdData[4]=100;
	XBOT_LcdData[5]=90;
	XBOT_LcdData[6]=90;
	XBOT_LcdData[7]=0;
	XBOT_LcdData[8]=75;
	XBOT_LcdData[9]=0;
	XBOT_LcdData[10]=0;
	XBOT_LcdData[11]=0;
	XBOT_LcdData[12]=15;
	XBOT_LcdData[13]=80;
	XBOT_LcdData[14]=0;
	XBOT_LcdData[15]=0;
	for(int i=16;i<32;i++)//�����б�
		XBOT_LcdData[i]=0;
	fireFlag=0x00;
	WireLength=0;
	signal=0;
	battery_1=0;
	battery_2=0;
	battery_3=0;
	battery_4=0;
	Position=new uint8_t[10];
	for(int i=0;i<10;i++)
	{
		Position[i]=0x00;
	}
	Angle=new uint16_t[10];
	for(int i=0;i<10;i++)
	{
		Angle[i]=0x00;
	}
	point= new uint16_t*[42];
	for(int i=0;i<42;i++)
	{
		point[i]=new uint16_t[2];
		point[i][0]=0X00;
		point[i][1]=0X00;
	}
	anglePic=3;
}

/**
  * ��  �ܣ�LCDdisplay�����������
  * ��  ������
  * ����ֵ����
  */
LCDdisplay::~LCDdisplay()
{
	lcddisPort=NULL;
	delete lcdParameter;
	delete XBOT_LcdData;
	delete Angle;
	delete Position;
		
	for(int i=0;i<42;i++)
	{
		delete point[i];
	}
	delete [] point;
}

void LCDdisplay::sendCommand()
{
	while(!(lcddisPort->putChar(lcdParameter->head)));				//����ͷ
	while(!(lcddisPort->putChar(lcdParameter->command)));			//����������
	lcddisPort->write(lcdParameter->buffer,lcdParameter->len);//������������
	lcddisPort->write(lcdParameter->end,4);										//����֡β
}

void LCDdisplay::SetSpace(uint8_t clum,uint8_t row) 								//�����ּ��
{
	lcdParameter->command=0x41;
  lcdParameter->buffer[0]=clum;
  lcdParameter->buffer[1]=row;
  lcdParameter->len=2;
	sendCommand();
}
void LCDdisplay::SetColor(uint16_t fcolor,uint16_t bcolor)					//���õ�ɫ��
{
  lcdParameter->command = 0x40;
  lcdParameter->buffer[0]=fcolor>>8;
  lcdParameter->buffer[1]=fcolor;
  lcdParameter->buffer[2]=bcolor>>8;
  lcdParameter->buffer[3]=bcolor;
  lcdParameter->len=4;
  sendCommand();
}
void LCDdisplay::GetColor(uint8_t mode,uint16_t x,uint16_t y)										//ȡָ��λ����ɫ����ɫ��
{
	if(mode==0)
		lcdParameter->command = 0x42;
	else
		lcdParameter->command = 0x43;
  lcdParameter->buffer[0]=x>>8;
  lcdParameter->buffer[1]=x;
  lcdParameter->buffer[2]=y>>8;
  lcdParameter->buffer[3]=y;
  lcdParameter->len=4;
  sendCommand();
}

void LCDdisplay::backlightOn()												//�򿪱���
{
  lcdParameter->command = 0x5f;
  lcdParameter->len=0;
  sendCommand();
}

void LCDdisplay::backlightOff()												//�رձ���
{
  lcdParameter->command = 0x5e;
  lcdParameter->len=0;
  sendCommand();
}

void LCDdisplay::PWMLight(uint8_t pwm)															//���ñ�������
{
	lcdParameter->command = 0x5f;
  lcdParameter->buffer[0]=pwm;
  lcdParameter->len = 0x01;
  sendCommand();
}
void LCDdisplay::ClearScreen(void)																	//�Ա���ɫ����		
{
  lcdParameter->command = 0x52;
  lcdParameter->len=0;
  sendCommand();
}
void LCDdisplay::DisplayTxt_FixedMode(uint8_t size,uint16_t x,uint16_t y,uint8_t *pdata,uint8_t Len)//��׼�ֿ���ʾ
{
	uint8_t i=0;
	lcdParameter->command   = size;
	lcdParameter->buffer[i++] = x>>8;
  lcdParameter->buffer[i++] = x;
  
  lcdParameter->buffer[i++] = y>>8;
  lcdParameter->buffer[i++] = y;
  while(Len--)
  { 
		lcdParameter->buffer[i++]=*pdata;
		pdata++;
	}
	lcdParameter->len = i;
  sendCommand();
}

const uint8_t locktxt[7]={0x20,0x81,0x01,0xFF,0xE0,0x00,0x00}; 
void LCDdisplay::DisplayTxt(uint16_t x,uint16_t y,uint8_t *pdata,uint8_t Len)//ѡ���ֿ���ʾ	
{
	uint8_t i=0;
	lcdParameter->command = 0x98;		//����
  lcdParameter->buffer[0] = x>>8;
  lcdParameter->buffer[1] = x;
  
  lcdParameter->buffer[2] = y>>8;
  lcdParameter->buffer[3] = y;
  
  for(i=4;i<sizeof(locktxt)+4;i++)
  { 
    lcdParameter->buffer[i]=locktxt[i-4];
  }
   
  while(Len--)
  { 
    lcdParameter->buffer[i++] = *pdata;
    pdata++;
  }
 
  lcdParameter->len = i;
  sendCommand();
}


void LCDdisplay::CutPicAndShow(uint8_t Pic_ID ,uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye,uint16_t X,uint16_t Y)//����ͼ����ʾ
{
  lcdParameter->command = 0x71;
  lcdParameter->buffer[0] = Pic_ID;
  
  lcdParameter->buffer[1] = Xs>>8;
  lcdParameter->buffer[2] = Xs;
  
  lcdParameter->buffer[3] = Ys>>8;
  lcdParameter->buffer[4] = Ys;
  
  lcdParameter->buffer[5] = (Xe+Xs)>>8;
  lcdParameter->buffer[6] = (Xe+Xs);
  
  lcdParameter->buffer[7] = (Ye+Ys)>>8;
  lcdParameter->buffer[8] = (Ye+Ys);
  //�ٴ���ʾ��λ��
  lcdParameter->buffer[9] = X>>8;
  lcdParameter->buffer[10] = X;
  
  lcdParameter->buffer[11] = Y>>8;
  lcdParameter->buffer[12] = Y;
  
  lcdParameter->len = 0x0D;
  sendCommand(); 
}
void LCDdisplay::CutPicAndShow_1(uint8_t Pic_ID ,uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye,uint16_t X,uint16_t Y)//����ͼ����ʾ
{
  lcdParameter->command = 0x71;
  lcdParameter->buffer[0] = Pic_ID;
  
  lcdParameter->buffer[1] = Xs>>8;
  lcdParameter->buffer[2] = Xs;
  
  lcdParameter->buffer[3] = Ys>>8;
  lcdParameter->buffer[4] = Ys;
  
  lcdParameter->buffer[5] = Xe>>8;
  lcdParameter->buffer[6] = Xe;
  
  lcdParameter->buffer[7] = Ye>>8;
  lcdParameter->buffer[8] = Ye;
  //�ٴ���ʾ��λ��
  lcdParameter->buffer[9] = X>>8;
  lcdParameter->buffer[10] = X;
  
  lcdParameter->buffer[11] = Y>>8;
  lcdParameter->buffer[12] = Y;
  
  lcdParameter->len = 0x0D;
  sendCommand(); 
}
void LCDdisplay::ConnectTwoPoint(uint8_t cmd,uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye)//��ֱ��
{
  lcdParameter->command = cmd;
  lcdParameter->buffer[0]=Xs>>8;
  lcdParameter->buffer[1]=Xs;
  lcdParameter->buffer[2]=Ys>>8;
  lcdParameter->buffer[3]=Ys;
   
  lcdParameter->buffer[4]=Xe>>8;
  lcdParameter->buffer[5]=Xe;
  lcdParameter->buffer[6]=Ye>>8;
  lcdParameter->buffer[7]=Ye;
  
  lcdParameter->len = 0x08;
  sendCommand();
}
void LCDdisplay::ShowFrequency(uint16_t X,uint16_t Y,uint8_t Hmax,uint8_t *Hi,uint8_t Len)//Ƶ����ʾ ����ͼ
{
  lcdParameter->command = 0x75;
  lcdParameter->buffer[0]=X>>8;
  lcdParameter->buffer[1]=X;
  lcdParameter->buffer[2]=Y>>8;
  lcdParameter->buffer[3]=Y;
  lcdParameter->buffer[4]=Hmax;
	for(int i=0;i<Len;i++)
		lcdParameter->buffer[5+i]=Hi[i];
  lcdParameter->len = 0x05+Len;
  sendCommand();
}
void LCDdisplay::DisRecentage(uint8_t cmd,uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye)//����������ʾ
{
	lcdParameter->command = cmd;
	lcdParameter->buffer[0]=Xs>>8;
	lcdParameter->buffer[1]=Xs;
	lcdParameter->buffer[2]=Ys>>8;
	lcdParameter->buffer[3]=Ys;
	lcdParameter->buffer[4]=Xe>>8;
	lcdParameter->buffer[5]=Xe;
	lcdParameter->buffer[6]=Ye>>8;
	lcdParameter->buffer[7]=Ye;
	lcdParameter->len = 0x08;
	sendCommand();
}
void LCDdisplay::DisRound(uint8_t cmd,uint16_t type,uint16_t Xs,uint16_t Ys,uint16_t r)	//Բ����ʾ
{
  lcdParameter->command = cmd;
  lcdParameter->buffer[0]=type;
  lcdParameter->buffer[1]=Xs>>8;
  lcdParameter->buffer[2]=Xs;
  lcdParameter->buffer[3]=Ys>>8;
  lcdParameter->buffer[4]=Ys;
  lcdParameter->buffer[5]=r;
  lcdParameter->len = 0x06;
  sendCommand();
}
void LCDdisplay::movePic(uint8_t cmd,uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye,uint16_t step)																	//ָ�������ƶ�
{
  lcdParameter->command = cmd;
	lcdParameter->buffer[0]=Xs>>8;
	lcdParameter->buffer[1]=Xs;
	lcdParameter->buffer[2]=Ys>>8;
	lcdParameter->buffer[3]=Ys;
	lcdParameter->buffer[4]=Xe>>8;
	lcdParameter->buffer[5]=Xe;
	lcdParameter->buffer[6]=Ye>>8;
	lcdParameter->buffer[7]=Ye;
	lcdParameter->buffer[8]=step;
  lcdParameter->len = 0x09;
  sendCommand();
}

#define BAR_WIDTH 20
#define BAR_LONG 200
void LCDdisplay::ShowBar(uint16_t Xs,uint16_t Ys,uint8_t step)//��������ʾ
{
  static unsigned char i=0;
  if(i==0)
  {
    DisRecentage(0x59,Xs-2,Ys-2,Xs+BAR_LONG+4,Ys+BAR_WIDTH+2);//104*24
    DisRecentage(0x59,Xs,Ys,Xs+BAR_LONG+2,Ys+BAR_WIDTH);
    i=1;
  }
  DisRecentage(0x5B,Xs+1,Ys+1,Xs+1+step,Ys+BAR_WIDTH-1);
  DisRecentage(0x5A,Xs+2+step,Ys+1,Xs+BAR_LONG+1,Ys+BAR_WIDTH-1);
}

//256ɫСҺ����û��С��̬������ʾ�Ĺ���
void LCDdisplay::ShowCurve(uint16_t X,uint16_t Ys,uint16_t Ye,uint16_t Y,uint16_t Fcolor,uint16_t BColor)						//С��̬������ʾ
{
  lcdParameter->command = 0x74;
  lcdParameter->buffer[0]=X>>8;
  lcdParameter->buffer[1]=X;
  lcdParameter->buffer[2]=Ys>>8;
  lcdParameter->buffer[3]=Ys;
  lcdParameter->buffer[4]=Ye>>8;
  lcdParameter->buffer[5]=Ye;
  lcdParameter->buffer[6]=BColor>>8;
  lcdParameter->buffer[7]=BColor;
  lcdParameter->buffer[8]=Y>>8;
  lcdParameter->buffer[9]=Y;
  lcdParameter->buffer[10]=Fcolor>>8;
  lcdParameter->buffer[11]=Fcolor;
  lcdParameter->len = 0x0C;
  sendCommand();
}
void LCDdisplay::ShowPic(uint8_t picnum)//��ʾͼƬ
{
	lcdParameter->command = 0x70;
	lcdParameter->buffer[0]=picnum;
	lcdParameter->len=0x01;
	sendCommand();
}
void LCDdisplay::ShakeHand(void)//����
{
  lcdParameter->command = 0x00;
  lcdParameter->len=0x00;
  sendCommand();
}

void LCDdisplay::showVoltageAndSpeed()	//��ʾ��ѹ���ٶ�
{
	int TempInt = 0;
	uint8_t TempChar[10] = {0};
	uint8_t i=0;
//��ʾ�����˱����ѹ
	 TempInt=XBOT_LcdData[14]*2;
	 if(TempInt==0)
	 {
				TempChar[i++] = '0'; 
	 }
	 else
	 {
         if(TempInt>=100)
            TempChar[i++] = TempInt/100+'0';  
         TempChar[i++] = (TempInt%100)/10+'0';
         TempChar[i++] = '.';
         TempChar[i++] = TempInt%10 + '0';
    }
    TempChar[i++] =  'V';
		while(i<5)
	    TempChar[i++] = ' '; 
		if(TempInt<238)
		{
				SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisplayTxt_FixedMode(0x54,236,59,TempChar,i);//16*16������ʾ
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
		}
		else
			DisplayTxt_FixedMode(0x54,236,59,TempChar,i);//16*16������ʾ

    //��ʾ�������ѹ
	 i=0;
	 TempInt=XBOT_LcdData[10]*2;
	 if(TempInt==0)
			TempChar[i++] = '0';
	 else
	 {
         if(TempInt>=100)
            TempChar[i++] = TempInt/100+'0';  
         TempChar[i++] = (TempInt%100)/10+'0';
         TempChar[i++] = '.';
         TempChar[i++] = TempInt%10 + '0';
    }
    TempChar[i++] =  'V';
		while(i<5)
	    TempChar[i++] = ' '; 
		if(TempInt<112)
		{
			SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
			DisplayTxt_FixedMode(0x54,236,93,TempChar,i);
			SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
		}
		else
			 DisplayTxt_FixedMode(0x54,236,93,TempChar,i);
   
    
    //�����ٶ�
    i = 0;
    TempInt = LeftMotorSpeed*2;
    if(TempInt == 0)
    {	
        TempChar[i++] = '0'; 
	}
    else
    {
    	if(TempInt<0)
		{
		     TempChar[i++] = '-'; 
			 TempInt = -TempInt;
		} 
		else
		{
		     TempChar[i++] = '+'; 
		}
        TempChar[i++] = TempInt/100+ '0';
        TempChar[i++] = '.';
        TempChar[i++] = (TempInt%100)/10+ '0';    
        TempChar[i++] = TempInt%10+ '0';    
    }
    TempChar[i++] = 'm';
	TempChar[i++] = '/';
	TempChar[i++] = 's';
	while(i<8)
	    TempChar[i++] = ' '; 
    DisplayTxt_FixedMode(0x54,236,127,TempChar,i);    
        
        //��ʾ�ҵ���ٶ�
    i = 0;
    TempInt = RightMotorSpeed*2;
    if(TempInt == 0)
    {
       TempChar[i++] = '0'; 
		}
    else
    {
    	if(TempInt<0)
		{
		     TempChar[i++] = '-'; 
			 TempInt = -TempInt;
		} 
		else
		{
		     TempChar[i++] = '+'; 
		}
        TempChar[i++] = TempInt/100+ '0';
        TempChar[i++] = '.';
        TempChar[i++] = (TempInt%100)/10+ '0';    
        TempChar[i++] = TempInt%10+ '0';    
    }
    TempChar[i++] = 'm';
	TempChar[i++] = '/';
	TempChar[i++] = 's';
	while(i<8)
	    TempChar[i++] = ' '; 
    DisplayTxt_FixedMode(0x54,236,169,TempChar,i);
}

void LCDdisplay::showVoltageAndSpeed_1()														//��ʾ��ѹ���ٶ�(��������)
{
    int TempInt = 0;
    uint8_t TempChar[10] = {0};
    uint8_t i=0;
 //��ʾ���³���
	 TempInt=WireLength;
	 if(TempInt==0)
	 {
		TempChar[i++] = '0'; 
	 }
	 else
	 {
		 if(TempInt>=100)
			 TempChar[i++] = TempInt/100+'0';
		 if(TempInt>10)
			TempChar[i++] = (TempInt%100)/10+'0';
		 TempChar[i++] = TempInt%10 + '0';
    }
    TempChar[i++] =  'M';
		while(i<5)
	    TempChar[i++] = ' '; 
    DisplayTxt_FixedMode(0x54,236,52,TempChar,i);//16*16������ʾ

	i=0;
 //��ʾ�����˱����ѹ
     TempInt=XBOT_LcdData[14]*2;
     if(TempInt==0)
     {
          TempChar[i++] = '0'; 
     }
     else
	 {
         if(TempInt>=100)
            TempChar[i++] = TempInt/100+'0';  
         TempChar[i++] = (TempInt%100)/10+'0';
         TempChar[i++] = '.';
         TempChar[i++] = TempInt%10 + '0';
    }
    TempChar[i++] =  'V';
		while(i<5)
	    TempChar[i++] = ' '; 
	
		if(TempInt<238)
		{
			SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
			DisplayTxt_FixedMode(0x54,236,80,TempChar,i);//16*16������ʾ
			SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
		}
		else
			 DisplayTxt_FixedMode(0x54,236,80,TempChar,i);//16*16������ʾ
    
    
    
    
    //��ʾ�������ѹ
     i=0;
     TempInt=XBOT_LcdData[10]*2;
     if(TempInt==0)
          TempChar[i++] = '0';
     else
	 {
         if(TempInt>=100)
            TempChar[i++] = TempInt/100+'0';  
         TempChar[i++] = (TempInt%100)/10+'0';
         TempChar[i++] = '.';
         TempChar[i++] = TempInt%10 + '0';
    }
    TempChar[i++] =  'V';
	while(i<5)
	    TempChar[i++] = ' '; 
    DisplayTxt_FixedMode(0x54,236,108,TempChar,i);
    
    //�����ٶ�
    i = 0;
    TempInt = LeftMotorSpeed*2;
    if(TempInt == 0)
    {	
        TempChar[i++] = '0'; 
	}
    else
    {
    	if(TempInt<0)
		{
		     TempChar[i++] = '-'; 
			 TempInt = -TempInt;
		} 
		else
		{
		     TempChar[i++] = '+'; 
		}
        TempChar[i++] = TempInt/100+ '0';
        TempChar[i++] = '.';
        TempChar[i++] = (TempInt%100)/10+ '0';    
        TempChar[i++] = TempInt%10+ '0';    
    }
    TempChar[i++] = 'm';
	TempChar[i++] = '/';
	TempChar[i++] = 's';
	while(i<8)
	    TempChar[i++] = ' '; 
	if(TempInt<112)
	{
		SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
		DisplayTxt_FixedMode(0x54,236,136,TempChar,i);    
		SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
	}
	else
		DisplayTxt_FixedMode(0x54,236,136,TempChar,i);    

        //��ʾ�ҵ���ٶ�
    i = 0;
    TempInt = RightMotorSpeed*2;
    if(TempInt == 0)
    {
        TempChar[i++] = '0'; 
	}
    else
    {
    	if(TempInt<0)
		{
		     TempChar[i++] = '-'; 
			 TempInt = -TempInt;
		} 
		else
		{
		     TempChar[i++] = '+'; 
		}
        TempChar[i++] = TempInt/100+ '0';
        TempChar[i++] = '.';
        TempChar[i++] = (TempInt%100)/10+ '0';    
        TempChar[i++] = TempInt%10+ '0';    
    }
    TempChar[i++] = 'm';
	TempChar[i++] = '/';
	TempChar[i++] = 's';
	while(i<8)
	    TempChar[i++] = ' '; 
    DisplayTxt_FixedMode(0x54,236,174,TempChar,i);
}
void LCDdisplay::ShowBattery(bool staflag)																			//��ʾ��ص���
{
	static uint8_t beckBattery_1=0;
	static uint8_t beckBattery_2=0;
	static uint8_t beckBattery_3=0;
	static uint8_t beckBattery_4=0;
	
	if(staflag)//ǿ��ˢ��
	{
		SetColor(0xFFFF,0x00);//ǰ��ɫ��ɰ�ɫ
		if(battery_1!=0)
		{
			if(battery_1<6)
			{
				SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,137,10,battery_1+137,13);
				SetColor(0xFFFF,0x00);//ǰ��ɫ��ɺ�ɫ
			}
			else
				DisRecentage(0x5b,137,10,battery_1+137,13);
		}

		if(battery_2!=0)
		{
			if(battery_2<6)
			{
				SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,163,10,battery_2+163,13);
				SetColor(0xFFFF,0x00);//ǰ��ɫ��ɺ�ɫ
			}
			else
				DisRecentage(0x5b,163,10,battery_2+163,13);
		}

		if(battery_3!=0)
		{
			if(battery_3<6)
			{
				SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,188,10,battery_3+188,13);
				SetColor(0xFFFF,0x00);//ǰ��ɫ��ɺ�ɫ
			}
			else
				DisRecentage(0x5b,188,10,battery_3+188,13);
		}
			
		if(battery_4!=0)
		{
			if(battery_4<6)
			{
				SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,213,10,battery_4+213,13);
				SetColor(0xFFFF,0x00);//ǰ��ɫ��ɺ�ɫ
			}
			else
				DisRecentage(0x5b,213,10,battery_4+213,13);
		}
			
		
		beckBattery_1=battery_1;
		beckBattery_2=battery_2;
		beckBattery_3=battery_3;
		beckBattery_4=battery_4;
		SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
	}
	else if(beckBattery_1!=battery_1||beckBattery_2!=battery_2||beckBattery_3!=battery_3||beckBattery_4!=battery_4)
	{
		SetColor(0xFFFF,0x00);//ǰ��ɫ��ɰ�ɫ
		if(beckBattery_1!=battery_1)
		{
			if(battery_1<6)
			{
				SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,137,10,battery_1+137,13);
				SetColor(0xFFFF,0x00);//ǰ��ɫ��ɰ�ɫ
			}
			else
				DisRecentage(0x5b,137,10,battery_1+137,13);
			if(beckBattery_1>battery_1)
			{
				DisRecentage(0x5A,137+battery_1,10,137+beckBattery_1,13);
				beckBattery_1=battery_1;
			}
			beckBattery_1=battery_1;
		}
			
		if(beckBattery_2!=battery_2)
		{
			if(battery_2<6)
			{
				SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,163,10,battery_2+163,13);
				SetColor(0xFFFF,0x00);//ǰ��ɫ��ɰ�ɫ
			}
			else
				DisRecentage(0x5b,163,10,battery_2+163,13);
			if(beckBattery_2>battery_2)
			{
				DisRecentage(0x5A,163+battery_2,10,163+beckBattery_2,13);
				beckBattery_2=battery_2;
				
			}
			beckBattery_2=battery_2;
		}
		
		if(beckBattery_3!=battery_3)
		{
			if(battery_3<6)
			{
				SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,188,10,battery_3+188,13);
				SetColor(0xFFFF,0x00);//ǰ��ɫ��ɰ�ɫ
			}
			else
				DisRecentage(0x5b,188,10,battery_3+188,13);
			if(beckBattery_3>battery_3)
			{
				DisRecentage(0x5A,188+battery_3,10,188+beckBattery_3,13);
				beckBattery_3=battery_3;
				
			}
			beckBattery_3=battery_3;
		}
		
		if(beckBattery_4!=battery_4)
		{
			if(battery_4<6)
			{
				SetColor(0xF800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,213,10,battery_4+213,13);
				SetColor(0xFFFF,0x00);//ǰ��ɫ��ɰ�ɫ
			}
			else
				DisRecentage(0x5b,213,10,battery_4+213,13);
			if(beckBattery_4>battery_4)
			{
				DisRecentage(0x5A,213+battery_4,10,213+beckBattery_4,13);
				beckBattery_4=battery_4;
				
			}
			beckBattery_4=battery_4;
		}
		SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
	}
}

void LCDdisplay::ShowSignal(bool staflag)																				//��ʾ�ź�ǿ��
{
	static uint8_t backSignal=0;
	if(staflag)//ǿ��ˢ��
	{
		SetColor(0xFFFF,0x00);//ǰ��ɫ��ɰ�ɫ
		for(int i=0;i<signal;i++)
		{
			DisRecentage(0x5b,285+i*3,15-i,286+i*3,16);
		}
		SetColor(0x4208,0x00);//ǰ��ɫ��ɻ�ɫ
		for(int i=signal;i<7;i++)
		{
			DisRecentage(0x5b,285+i*3,15-i,286+i*3,16);
		}
		SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
		backSignal=signal;
	}
	else
	{
		if(backSignal<signal)//�ź���ǿ
		{
			SetColor(0xFFFF,0x00);//ǰ��ɫ��ɰ�ɫ
			for(int i=backSignal;i<signal;i++)
			{
				DisRecentage(0x5b,285+i*3,15-i,286+i*3,16);
			}
			SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			backSignal=signal;
		}
		else if(backSignal>signal)//�źż���
		{
			SetColor(0x4208,0x00);//ǰ��ɫ��ɻ�ɫ
			for(int i=signal;i<backSignal;i++)
			{
				DisRecentage(0x5b,285+i*3,15-i,286+i*3,16);
			}
			SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			backSignal=signal;
		}
	}
}
void LCDdisplay::ShowCtrlSpeed(bool staflag)																//�Խ������ķ�ʽ��ʾ�����ٶ�
{
	static int backLeftCtrlSpeed=0;
	static int backRightCtrlSpeed=0;
	if(staflag)//ǿ����ʾ�ٶ�
	{
		if(LeftCtrlSpeed>0)//�����ٶ�
		{
			if(LeftCtrlSpeed>49)//���ڵ���1m/s
			{
				SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,219,151,219+LeftCtrlSpeed,153);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else if(LeftCtrlSpeed>24)//���ڵ���0.5m/s
			{
				SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
				DisRecentage(0x5b,219,151,219+LeftCtrlSpeed,153);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else
			{
				DisRecentage(0x5b,219,151,219+LeftCtrlSpeed,153);
			}
		}
		else if(LeftCtrlSpeed<0)//�����ٶ�
		{
			if(LeftCtrlSpeed<-49)//���ڵ���1m/s
			{
				SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,218+LeftCtrlSpeed,151,218,153);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else if(LeftCtrlSpeed<-24)//���ڵ���0.5m/s
			{
				SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
				DisRecentage(0x5b,218+LeftCtrlSpeed,151,218,153);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else
			{
				DisRecentage(0x5b,218+LeftCtrlSpeed,151,218,153);
			}
		}
		if(RightCtrlSpeed>0)//�ҵ���ٶ�
		{
			if(RightCtrlSpeed>49)//���ڵ���1m/s
			{
				SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,219,193,219+RightCtrlSpeed,195);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else if(RightCtrlSpeed>24)//���ڵ���0.5m/s
			{
				SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
				DisRecentage(0x5b,219,193,219+RightCtrlSpeed,195);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else
			{
				DisRecentage(0x5b,219,193,219+RightCtrlSpeed,195);
			}
		}
		else if(RightCtrlSpeed<0)//�ҵ���ٶ�
		{
			if(RightCtrlSpeed<-49)//���ڵ���1m/s
			{
				SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,218+RightCtrlSpeed,193,218,195);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else if(RightCtrlSpeed<-24)//���ڵ���0.5m/s
			{
				SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
				DisRecentage(0x5b,218+RightCtrlSpeed,193,218,195);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else
			{
				DisRecentage(0x5b,218+RightCtrlSpeed,193,218,195);
			}
		}
	}
	else //�����ϴν����ʾ
	{
		if(backLeftCtrlSpeed!=LeftCtrlSpeed)
		{
			if(LeftCtrlSpeed>0)//�����ٶ�
			{
				if(LeftCtrlSpeed>49)//���ڵ���1m/s
				{
					SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
					DisRecentage(0x5b,219,151,219+LeftCtrlSpeed,153);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else if(LeftCtrlSpeed>24)//���ڵ���0.5m/s
				{
					SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
					DisRecentage(0x5b,219,151,219+LeftCtrlSpeed,153);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else
				{
					DisRecentage(0x5b,219,151,219+LeftCtrlSpeed,153);
				}
				if(backLeftCtrlSpeed<0)
				{
					DisRecentage(0x5a,218+backLeftCtrlSpeed,151,218,153);//���ϴ���ʾ���
				}
				else if(backLeftCtrlSpeed>LeftCtrlSpeed)//������Ĳ������
				{
					DisRecentage(0x5a,219+LeftCtrlSpeed,151,219+backLeftCtrlSpeed,153);
				}
			}
			else if(LeftCtrlSpeed<0)//�����ٶ�
			{
				if(LeftCtrlSpeed<-49)//���ڵ���1m/s
				{
					SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
					DisRecentage(0x5b,218+LeftCtrlSpeed,151,218,153);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else if(LeftCtrlSpeed<-24)//���ڵ���0.5m/s
				{
					SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
					DisRecentage(0x5b,218+LeftCtrlSpeed,151,218,153);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else
				{
					DisRecentage(0x5b,218+LeftCtrlSpeed,151,218,153);
				}
				if(backLeftCtrlSpeed>0)
				{
					DisRecentage(0x5a,219,151,219+backLeftCtrlSpeed,153);//���ϴ���ʾ���
				}
				else if(backLeftCtrlSpeed<LeftCtrlSpeed)//������Ĳ������
				{
					DisRecentage(0x5a,218+backLeftCtrlSpeed,151,218+LeftCtrlSpeed,153);
				}
			}
			else //�����ٶ�Ϊ0
			{
				if(backLeftCtrlSpeed>0)
				{
					DisRecentage(0x5a,219,151,219+backLeftCtrlSpeed,153);//���ϴ���ʾ���
				}
				else if(backLeftCtrlSpeed<0)
				{
					DisRecentage(0x5a,218+backLeftCtrlSpeed,151,218,153);
				}
			}
		}
		
		
		if(backRightCtrlSpeed!=RightCtrlSpeed)
		{
			if(RightCtrlSpeed>0)//�ҵ���ٶ�
			{
				if(RightCtrlSpeed>49)//���ڵ���1m/s
				{
					SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
					DisRecentage(0x5b,219,193,219+RightCtrlSpeed,195);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else if(RightCtrlSpeed>24)//���ڵ���0.5m/s
				{
					SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
					DisRecentage(0x5b,219,193,219+RightCtrlSpeed,195);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else
				{
					DisRecentage(0x5b,219,193,219+RightCtrlSpeed,195);
				}
				if(backRightCtrlSpeed<0)
				{
					DisRecentage(0x5a,218+backRightCtrlSpeed,193,218,195);//���ϴ���ʾ���
				}
				else if(backRightCtrlSpeed>RightCtrlSpeed)//������Ĳ������
				{
					DisRecentage(0x5a,219+RightCtrlSpeed,193,219+backRightCtrlSpeed,195);
				}
			}
			else if(RightCtrlSpeed<0)//�ҵ���ٶ�
			{
				if(RightCtrlSpeed<-49)//���ڵ���1m/s
				{
					SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
					DisRecentage(0x5b,218+RightCtrlSpeed,193,218,195);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else if(RightCtrlSpeed<-24)//���ڵ���0.5m/s
				{
					SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
					DisRecentage(0x5b,218+RightCtrlSpeed,193,218,195);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else
				{
					DisRecentage(0x5b,218+RightCtrlSpeed,193,218,195);
				}
				if(backRightCtrlSpeed>0)
				{
					DisRecentage(0x5a,219,193,219+backRightCtrlSpeed,195);//���ϴ���ʾ���
				}
				else if(backRightCtrlSpeed<RightCtrlSpeed)//������Ĳ������
				{
					DisRecentage(0x5a,218+backRightCtrlSpeed,193,218+RightCtrlSpeed,195);
				}
			}
			else //�����ٶ�Ϊ0
			{
				if(backRightCtrlSpeed>0)
				{
					DisRecentage(0x5a,219,193,219+backRightCtrlSpeed,195);//���ϴ���ʾ���
				}
				else if(backRightCtrlSpeed<0)
				{
					DisRecentage(0x5a,218+backRightCtrlSpeed,193,218,195);
				}
			}
		}
	}
	backLeftCtrlSpeed=LeftCtrlSpeed;
	backRightCtrlSpeed=RightCtrlSpeed;
}
void LCDdisplay::ShowCtrlSpeed_1(bool staflag)															//�Խ������ķ�ʽ��ʾ�����ٶ�(��������)
{
	static int backLeftCtrlSpeed=0;
	static int backRightCtrlSpeed=0;
	if(staflag)//ǿ����ʾ�ٶ�
	{
		if(LeftCtrlSpeed>0)//�����ٶ�
		{
			if(LeftCtrlSpeed>49)//���ڵ���1m/s
			{
				SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,219,160,219+LeftCtrlSpeed,162);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else if(LeftCtrlSpeed>24)//���ڵ���0.5m/s
			{
				SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
				DisRecentage(0x5b,219,160,219+LeftCtrlSpeed,162);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else
			{
				DisRecentage(0x5b,219,160,219+LeftCtrlSpeed,162);
			}
		}
		else if(LeftCtrlSpeed<0)//�����ٶ�
		{
			if(LeftCtrlSpeed<-49)//���ڵ���1m/s
			{
				SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,218+LeftCtrlSpeed,160,218,162);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else if(LeftCtrlSpeed<-24)//���ڵ���0.5m/s
			{
				SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
				DisRecentage(0x5b,218+LeftCtrlSpeed,160,218,162);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else
			{
				DisRecentage(0x5b,218+LeftCtrlSpeed,160,218,162);
			}
		}
		if(RightCtrlSpeed>0)//�ҵ���ٶ�
		{
			if(RightCtrlSpeed>49)//���ڵ���1m/s
			{
				SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,219,198,219+RightCtrlSpeed,200);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else if(RightCtrlSpeed>24)//���ڵ���0.5m/s
			{
				SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
				DisRecentage(0x5b,219,198,219+RightCtrlSpeed,200);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else
			{
				DisRecentage(0x5b,219,198,219+RightCtrlSpeed,200);
			}
		}
		else if(RightCtrlSpeed<0)//�ҵ���ٶ�
		{
			if(RightCtrlSpeed<-49)//���ڵ���1m/s
			{
				SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
				DisRecentage(0x5b,218+RightCtrlSpeed,198,218,200);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else if(RightCtrlSpeed<-24)//���ڵ���0.5m/s
			{
				SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
				DisRecentage(0x5b,218+RightCtrlSpeed,198,218,200);
				SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
			}
			else
			{
				DisRecentage(0x5b,218+RightCtrlSpeed,198,218,200);
			}
		}
	}
	else //�����ϴν����ʾ
	{
		if(backLeftCtrlSpeed!=LeftCtrlSpeed)
		{
			if(LeftCtrlSpeed>0)//�����ٶ�
			{
				if(LeftCtrlSpeed>49)//���ڵ���1m/s
				{
					SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
					DisRecentage(0x5b,219,160,219+LeftCtrlSpeed,162);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else if(LeftCtrlSpeed>24)//���ڵ���0.5m/s
				{
					SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
					DisRecentage(0x5b,219,160,219+LeftCtrlSpeed,162);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else
				{
					DisRecentage(0x5b,219,160,219+LeftCtrlSpeed,162);
				}
				if(backLeftCtrlSpeed<0)
				{
					DisRecentage(0x5a,218+backLeftCtrlSpeed,160,218,162);//���ϴ���ʾ���
				}
				else if(backLeftCtrlSpeed>LeftCtrlSpeed)//������Ĳ������
				{
					DisRecentage(0x5a,219+LeftCtrlSpeed,160,219+backLeftCtrlSpeed,162);
				}
			}
			else if(LeftCtrlSpeed<0)//�����ٶ�
			{
				if(LeftCtrlSpeed<-49)//���ڵ���1m/s
				{
					SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
					DisRecentage(0x5b,218+LeftCtrlSpeed,160,218,162);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else if(LeftCtrlSpeed<-24)//���ڵ���0.5m/s
				{
					SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
					DisRecentage(0x5b,218+LeftCtrlSpeed,160,218,162);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else
				{
					DisRecentage(0x5b,218+LeftCtrlSpeed,160,218,162);
				}
				if(backLeftCtrlSpeed>0)
				{
					DisRecentage(0x5a,219,160,219+backLeftCtrlSpeed,162);//���ϴ���ʾ���
				}
				else if(backLeftCtrlSpeed<LeftCtrlSpeed)//������Ĳ������
				{
					DisRecentage(0x5a,218+backLeftCtrlSpeed,160,218+LeftCtrlSpeed,162);
				}
			}
			else //�����ٶ�Ϊ0
			{
				if(backLeftCtrlSpeed>0)
				{
					DisRecentage(0x5a,219,160,219+backLeftCtrlSpeed,162);//���ϴ���ʾ���
				}
				else if(backLeftCtrlSpeed<0)
				{
					DisRecentage(0x5a,218+backLeftCtrlSpeed,160,218,162);
				}
			}
		}
		
		
		if(backRightCtrlSpeed!=RightCtrlSpeed)
		{
			if(RightCtrlSpeed>0)//�ҵ���ٶ�
			{
				if(RightCtrlSpeed>49)//���ڵ���1m/s
				{
					SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
					DisRecentage(0x5b,219,198,219+RightCtrlSpeed,200);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else if(RightCtrlSpeed>24)//���ڵ���0.5m/s
				{
					SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
					DisRecentage(0x5b,219,198,219+RightCtrlSpeed,200);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else
				{
					DisRecentage(0x5b,219,198,219+RightCtrlSpeed,200);
				}
				if(backRightCtrlSpeed<0)
				{
					DisRecentage(0x5a,218+backRightCtrlSpeed,198,218,200);//���ϴ���ʾ���
				}
				else if(backRightCtrlSpeed>RightCtrlSpeed)//������Ĳ������
				{
					DisRecentage(0x5a,219+RightCtrlSpeed,198,219+backRightCtrlSpeed,200);
				}
			}
			else if(RightCtrlSpeed<0)//�ҵ���ٶ�
			{
				if(RightCtrlSpeed<-49)//���ڵ���1m/s
				{
					SetColor(0xf800,0x00);//ǰ��ɫ��ɺ�ɫ
					DisRecentage(0x5b,218+RightCtrlSpeed,198,218,200);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else if(RightCtrlSpeed<-24)//���ڵ���0.5m/s
				{
					SetColor(0xffe0,0x00);//ǰ��ɫ��ɻ�ɫ
					DisRecentage(0x5b,218+RightCtrlSpeed,198,218,200);
					SetColor(0x07E0,0x00);//ǰ��ɫ�����ɫ
				}
				else
				{
					DisRecentage(0x5b,218+RightCtrlSpeed,198,218,200);
				}
				if(backRightCtrlSpeed>0)
				{
					DisRecentage(0x5a,219,198,219+backRightCtrlSpeed,200);//���ϴ���ʾ���
				}
				else if(backRightCtrlSpeed<RightCtrlSpeed)//������Ĳ������
				{
					DisRecentage(0x5a,218+backRightCtrlSpeed,198,218+RightCtrlSpeed,200);
				}
			}
			else //�����ٶ�Ϊ0
			{
				if(backRightCtrlSpeed>0)
				{
					DisRecentage(0x5a,219,198,219+backRightCtrlSpeed,200);//���ϴ���ʾ���
				}
				else if(backRightCtrlSpeed<0)
				{
					DisRecentage(0x5a,218+backRightCtrlSpeed,198,218,200);
				}
			}
		}
	}
	backLeftCtrlSpeed=LeftCtrlSpeed;
	backRightCtrlSpeed=RightCtrlSpeed;
}
void LCDdisplay::showAngle(uint16_t posX,uint16_t posY,bool staflag)						//��ʾ�Ƕ���Ϣ
{
     uint8_t i=0,j=0,k=0,m=0;
     uint8_t TempChar[10] = {0};
     if(Position[0]!=XBOT_LcdData[0]||staflag)
     {
          i=0;
          Position[0]=XBOT_LcdData[0];
          ConnectTwoPoint(0x5d,25,109,25+18*cosf[(Angle[0]+ReviseAngle[1]+360)%360],109-18*sinf[(Angle[0]+ReviseAngle[1]+360)%360]);//����������ת
          Angle[0] = XBOT_LcdData[0]*2;
          if(Angle[0]>=100)
          {
              TempChar[i++] = Angle[0]/100+'0';
              TempChar[i++] = (Angle[0]%100)/10+'0';
          }
					else if(Angle[0]>=10)
          {
              TempChar[i++] = Angle[0]/10+'0';
          }
          TempChar[i++] = Angle[0]%10+'0';
					while(i<3)
						TempChar[i++] = ' ';
          DisplayTxt_FixedMode(0x6e,13,40,TempChar,i);
          ConnectTwoPoint(0x56,25,109,25+18*cosf[(Angle[0]+ReviseAngle[1]+360)%360],109-18*sinf[(Angle[0]+ReviseAngle[1]+360)%360]);//��ʾ������ת
     }     
     if(Position[4]!=XBOT_LcdData[1]||staflag)
     {
	      i=0;
          Position[4]=XBOT_LcdData[1];
          ConnectTwoPoint(0x5d,25,161,25+18*cosf[(Angle[4]+ReviseAngle[1]+360)%360],161-18*sinf[(Angle[4]+ReviseAngle[1]+360)%360]);//������ץ��ת
          Angle[4] = XBOT_LcdData[1]*2;
          if(Angle[4]>=100)
          {
              TempChar[i++] = Angle[4]/100+'0';
              TempChar[i++] = (Angle[4]%100)/10+'0';
          }
					else if(Angle[4]>=10)
          {
              TempChar[i++] = Angle[4]/10+'0';
          }
          TempChar[i++] = Angle[4]%10+'0';
					while(i<3)
						TempChar[i++] = ' ';
          DisplayTxt_FixedMode(0x6e,273,40,TempChar,i);
          ConnectTwoPoint(0x56,25,161,25+18*cosf[(Angle[4]+ReviseAngle[1]+360)%360],161-18*sinf[(Angle[4]+ReviseAngle[1]+360)%360]);//��ʾ��ץ��ת
              
     }
     if(Position[6]!=XBOT_LcdData[9]||staflag)//��̨��ת
     {
	      i=0;
				Position[6]=XBOT_LcdData[9];
				ConnectTwoPoint(0x5d,25,213,25+18*cosf[(Angle[6]+ReviseAngle[1]+360)%360],213-18*sinf[(Angle[6]+ReviseAngle[1]+360)%360]);//������̨��ת
				Angle[6] = XBOT_LcdData[9]*2;
				if(Angle[6]>=100)
				{
						TempChar[i++] = Angle[6]/100+'0';
						TempChar[i++] = (Angle[6]%100)/10+'0';
				}
				else if(Angle[6]>=10)
				{
						TempChar[i++] = Angle[6]/10+'0';
				}
				TempChar[i++] = Angle[6]%10+'0';
				while(i<3)
					TempChar[i++] = ' ';
				DisplayTxt_FixedMode(0x6e,78,69,TempChar,i);  
				ConnectTwoPoint(0x56,25,213,25+18*cosf[(Angle[6]+ReviseAngle[1]+360)%360],213-18*sinf[(Angle[6]+ReviseAngle[1]+360)%360]);//��ʾ��̨��ת
     }          
//      if(Position[7]!=XBOT_LcdData[13]||staflag)
//      {
// 	      i=0;
//           Position[7]=XBOT_LcdData[13];
//           Angle[7] = XBOT_LcdData[13]*2;
//           if(Angle[7]>=100)
//           {
//               TempChar[i++] = Angle[7]/100+'0';
//               TempChar[i++] = (Angle[7]%100)/10+'0';
//           }
// 					else if(Angle[7]>=10)
//           {
//               TempChar[i++] = Angle[7]/10+'0';
//           }
//           TempChar[i++] = Angle[7]%10+'0';
// 					while(i<3)
// 						TempChar[i++] = ' ';
//           DisplayTxt_FixedMode(0x54,143,64,TempChar,i);  
//      }
     for(i=0;i<10;i++)
     {
	      j=(i%4)*4+i/4;
          Angle[i] = XBOT_LcdData[j]*2;
	      if(Position[i]!=XBOT_LcdData[j]||staflag)
				{
					Position[i]=XBOT_LcdData[j];
					m=0;
					if(Angle[i]>=100)
					{
						TempChar[m++] = Angle[i]/100+'0';
						TempChar[m++] = (Angle[i]%100)/10+'0';
					}
					else if(Angle[i]>=10)
					{
						TempChar[m++] = Angle[i]/10+'0';
					}
					TempChar[m++] = Angle[i]%10+'0';
					while(m<3)
						TempChar[m++] = ' ';
					DisplayTxt_FixedMode(0x6e,13+65*(i%5),40+29*(i/5),TempChar,m);
					k++;
				}
     }
		 if(k==0&&!staflag)//K���Ӽ�����޹ؽڵı仯
	     return;
//      if(status==0x6c)
//      {
//           if(Angle[1]<188)
//               Angle[1] = 188;
//           if(Angle[2]>164)
//               Angle[2] = 164;
//           if(Angle[3]<16)
//               Angle[3] = 16;
//      }    
		if (Angle[1] < 182)
				Angle[1] = 182;
		if (Angle[2] > 168)
				Angle[2] = 168;
		if (Angle[3] < 10)
				Angle[3] = 10;
     Angle[1]=(Angle[1]+540)%360;
     Angle[2]=(Angle[1]+Angle[2]+360)%360;
     Angle[3]=(Angle[2]+Angle[3]+540)%360;
     Angle[5]=(Angle[3]+Angle[5]+630)%360;
     Angle[9]=(Angle[9]+360)%360;

     point[0][0]=posX;
     point[0][1]=posY;
     
     point[1][0]=posX-18;
     point[1][1]=posY+6;
     
     point[2][0]=posX+32;
     point[2][1]=posY+6;    
     
     point[3][0]=(posX-18)+20*cosf[(Angle[9])];
     point[3][1]=(posY+6)-20*sinf[(Angle[9])]; 
     
     point[4][0]=posX+40*cosf[(Angle[1])];
     point[4][1]=posY-40*sinf[(Angle[1])];
     
     point[5][0]=point[4][0]+40*cosf[(Angle[2])];
     point[5][1]=point[4][1]-40*sinf[(Angle[2])];
     
     point[6][0]=point[5][0]+28*cosf[(Angle[3])];
     point[6][1]=point[5][1]-28*sinf[(Angle[3])];
     
     point[7][0]=posX-18;
     point[7][1]=posY;
     
     point[38][0]=posX-5;
     point[38][1]=posY;
 
     point[39][0]=posX+5;
     point[39][1]=posY;
          
     
     point[8][0]=posX+32;
     point[8][1]=posY;
     
     point[9][0]=posX-18;
     point[9][1]=posY+12;
     
     point[10][0]=posX+32;
     point[10][1]=posY+12;
     
     point[11][0]=point[1][0]+6*cosf[(Angle[9]-ReviseAngle[1]+360)%360];
     point[11][1]=point[1][1]-6*sinf[(Angle[9]-ReviseAngle[1]+360)%360];
     
     point[12][0]=point[1][0]+20.4*cosf[(Angle[9]-ReviseAngle[0]+360)%360];
     point[12][1]=point[1][1]-20.4*sinf[(Angle[9]-ReviseAngle[0]+360)%360];
     
     point[13][0]=point[1][0]+6*cosf[(Angle[9]+ReviseAngle[1])%360];
     point[13][1]=point[1][1]-6*sinf[(Angle[9]+ReviseAngle[1])%360];
     
     point[14][0]=point[1][0]+20.4*cosf[(Angle[9]+ReviseAngle[0])%360];
     point[14][1]=point[1][1]-20.4*sinf[(Angle[9]+ReviseAngle[0])%360];
     
     point[15][0]=posX+5*cosf[(Angle[1]-ReviseAngle[2]+360)%360];
     point[15][1]=posY-5*sinf[(Angle[1]-ReviseAngle[2]+360)%360];
     
     point[16][0]=posX+36*cosf[(Angle[1]-ReviseAngle[3]+360)%360];
     point[16][1]=posY-36*sinf[(Angle[1]-ReviseAngle[3]+360)%360];
     
     point[17][0]=posX+5*cosf[(Angle[1]+ReviseAngle[2]+360)%360];
     point[17][1]=posY-5*sinf[(Angle[1]+ReviseAngle[2]+360)%360];
     
     point[18][0]=posX+36*cosf[(Angle[1]+ReviseAngle[3]+360)%360];
     point[18][1]=posY-36*sinf[(Angle[1]+ReviseAngle[3]+360)%360];
     
     point[19][0]=point[4][0]+4*cosf[(Angle[2]-ReviseAngle[4]+360)%360];
     point[19][1]=point[4][1]-4*sinf[(Angle[2]-ReviseAngle[4]+360)%360];
     
     point[20][0]=point[4][0]+36*cosf[(Angle[2]-ReviseAngle[3]+360)%360];
     point[20][1]=point[4][1]-36*sinf[(Angle[2]-ReviseAngle[3]+360)%360];
     
     point[21][0]=point[4][0]+4*cosf[(Angle[2]+ReviseAngle[4]+360)%360];
     point[21][1]=point[4][1]-4*sinf[(Angle[2]+ReviseAngle[4]+360)%360];
     
     point[22][0]=point[4][0]+36*cosf[(Angle[2]+ReviseAngle[3]+360)%360];
     point[22][1]=point[4][1]-36*sinf[(Angle[2]+ReviseAngle[3]+360)%360];
     
     point[23][0]=point[5][0]+4*cosf[(Angle[3]-ReviseAngle[4]+360)%360];
     point[23][1]=point[5][1]-4*sinf[(Angle[3]-ReviseAngle[4]+360)%360];
     
     point[24][0]=point[5][0]+24.3*cosf[(Angle[3]-ReviseAngle[5]+360)%360];
     point[24][1]=point[5][1]-24.3*sinf[(Angle[3]-ReviseAngle[5]+360)%360];
     
     point[25][0]=point[5][0]+4*cosf[(Angle[3]+ReviseAngle[4]+360)%360];
     point[25][1]=point[5][1]-4*sinf[(Angle[3]+ReviseAngle[4]+360)%360];
     
     point[26][0]=point[5][0]+24.3*cosf[(Angle[3]+ReviseAngle[5]+360)%360];
     point[26][1]=point[5][1]-24.3*sinf[(Angle[3]+ReviseAngle[5]+360)%360];
     
     point[27][0]=point[6][0]+6*cosf[(Angle[5]-ReviseAngle[1]+360)%360];
     point[27][1]=point[6][1]-6*sinf[(Angle[5]-ReviseAngle[1]+360)%360];
     
     point[28][0]=point[6][0]+13.4*cosf[(Angle[5]-ReviseAngle[4]+360)%360];
     point[28][1]=point[6][1]-13.4*sinf[(Angle[5]-ReviseAngle[4]+360)%360];
     
     point[29][0]=point[6][0]+6*cosf[(Angle[5]+ReviseAngle[1]+360)%360];
     point[29][1]=point[6][1]-6*sinf[(Angle[5]+ReviseAngle[1]+360)%360];
     
     point[30][0]=point[6][0]+13.4*cosf[(Angle[5]+ReviseAngle[4]+360)%360];
     point[30][1]=point[6][1]-13.4*sinf[(Angle[5]+ReviseAngle[4]+360)%360];
     
     point[40][0]=point[6][0]+4*cosf[(Angle[5]-ReviseAngle[1]+360)%360];
     point[40][1]=point[6][1]-4*sinf[(Angle[5]-ReviseAngle[1]+360)%360];
     
     point[41][0]=point[6][0]+4*cosf[(Angle[5]+ReviseAngle[1]+360)%360];
     point[41][1]=point[6][1]-4*sinf[(Angle[5]+ReviseAngle[1]+360)%360];
     
     //point[31][0]=point[6][0]+15.6*cosf(Angle[6]-ReviseAngle[6]);
     //point[31][1]=point[6][1]-15.6*sinf(Angle[6]-ReviseAngle[6]);
     
     point[32][0]=point[6][0]+17.2*cosf[(Angle[5]+ReviseAngle[7]+360)%360];
     point[32][1]=point[6][1]-17.2*sinf[(Angle[5]+ReviseAngle[7]+360)%360];
     
     point[33][0]=point[6][0]+11.7*cosf[(Angle[5]+ReviseAngle[8]+360)%360];
     point[33][1]=point[6][1]-11.7*sinf[(Angle[5]+ReviseAngle[8]+360)%360];
     
     point[34][0]=point[5][0]+14*cosf[(Angle[3]-Angle[8]/2+540)%360];
     point[34][1]=point[5][1]-14*sinf[(Angle[3]-Angle[8]/2+540)%360];
          
     point[35][0]=point[5][0]+14*cosf[(Angle[3]+Angle[8]/2+540)%360]; 
     point[35][1]=point[5][1]-14*sinf[(Angle[3]+Angle[8]/2+540)%360];
     
     point[36][0]=point[5][0]+9*cosf[(Angle[3]-Angle[8]/2-ReviseAngle[9]+540)%360];
     point[36][1]=point[5][1]-9*sinf[(Angle[3]-Angle[8]/2-ReviseAngle[9]+540)%360];
                        
     point[37][0]=point[5][0]+9*cosf[(Angle[3]+Angle[8]/2+ReviseAngle[9]+540)%360]; 
     point[37][1]=point[5][1]-9*sinf[(Angle[3]+Angle[8]/2+ReviseAngle[9]+540)%360];
		//��ʼ��������2Dģ��
     CutPicAndShow_1(anglePic,66,84,318,240,66,84); 
     DisRound(0x57,0x01,point[1][0],point[1][1],6);//ǰ����ʾ
     DisRound(0x57,0x01,point[2][0],point[2][1],6);//������ʾ
     DisRound(0x57,0x01,point[3][0],point[3][1],4);//�ڱ�����ʾ
     DisRound(0x57,0x01,point[0][0],point[0][1],5);//���֧��԰
     DisRound(0x57,0x01,point[4][0],point[4][1],4);//С��֧��԰
     DisRound(0x57,0x01,point[5][0],point[5][1],4);//����֧��԰
     
     DisRound(0x57,0x01,point[6][0],point[6][1],4);//����ͷ֧��԰
     
     ConnectTwoPoint(0x56,point[7][0],point[7][1],point[38][0],point[38][1]);
     ConnectTwoPoint(0x56,point[8][0],point[8][1],point[39][0],point[39][1]);
     
     ConnectTwoPoint(0x56,point[9][0],point[9][1],point[10][0],point[10][1]);
     
     ConnectTwoPoint(0x56,point[11][0],point[11][1],point[12][0],point[12][1]);
     ConnectTwoPoint(0x56,point[13][0],point[13][1],point[14][0],point[14][1]);
     
     ConnectTwoPoint(0x56,point[15][0],point[15][1],point[16][0],point[16][1]);
     ConnectTwoPoint(0x56,point[17][0],point[17][1],point[18][0],point[18][1]);
     
     ConnectTwoPoint(0x56,point[19][0],point[19][1],point[20][0],point[20][1]);
     ConnectTwoPoint(0x56,point[21][0],point[21][1],point[22][0],point[22][1]);
     
     ConnectTwoPoint(0x56,point[23][0],point[23][1],point[24][0],point[24][1]);
     ConnectTwoPoint(0x56,point[25][0],point[25][1],point[26][0],point[26][1]);
     
     ConnectTwoPoint(0x56,point[27][0],point[27][1],point[28][0],point[28][1]);
     ConnectTwoPoint(0x56,point[29][0],point[29][1],point[30][0],point[30][1]);
     
     ConnectTwoPoint(0x56,point[27][0],point[27][1],point[40][0],point[40][1]);
     ConnectTwoPoint(0x56,point[29][0],point[29][1],point[41][0],point[41][1]);
     ConnectTwoPoint(0x56,point[30][0],point[30][1],point[28][0],point[28][1]);
     
     ConnectTwoPoint(0x56,point[30][0],point[30][1],point[32][0],point[32][1]);
     ConnectTwoPoint(0x56,point[33][0],point[33][1],point[32][0],point[32][1]);
     
     ConnectTwoPoint(0x56,point[5][0],point[5][1],point[34][0],point[34][1]);
     ConnectTwoPoint(0x56,point[5][0],point[5][1],point[35][0],point[35][1]);
     
     ConnectTwoPoint(0x56,point[5][0],point[5][1],point[36][0],point[36][1]);
     ConnectTwoPoint(0x56,point[5][0],point[5][1],point[37][0],point[37][1]);
     
     ConnectTwoPoint(0x56,point[34][0],point[34][1],point[36][0],point[36][1]);
     ConnectTwoPoint(0x56,point[35][0],point[35][1],point[37][0],point[37][1]); 
}

#define EEPROR_ADDR_1 0x01
#define EEPROR_ADDR_2 0xDE

//�������� 0x00�� Ӣ�ģ� ����������
void LCDdisplay::setLanguageBuf(uint8_t data)																																				
{
	lcdParameter->command=0x90;
	lcdParameter->buffer[0]=0x55;
	lcdParameter->buffer[1]=0xaa;
	lcdParameter->buffer[2]=0x5a;
	lcdParameter->buffer[3]=0xa5;

	lcdParameter->buffer[4]=EEPROR_ADDR_1;
	lcdParameter->buffer[5]=EEPROR_ADDR_2;
	lcdParameter->buffer[6]=0x00;
	lcdParameter->buffer[7]=0x00;
	
	lcdParameter->buffer[8]=data;
	lcdParameter->buffer[9]=data;
	lcdParameter->buffer[10]=data;
	
	lcdParameter->len=11;
	sendCommand();
}

//�������� aa 90 01 de 00 00 03 xx xx xx cc 33 c3 3c 
//����0 ����Ч 1��Ӣ�� 2������
uint8_t LCDdisplay::riceveData()																			
{
	//֡ͷ aa bb 01
	uint8_t readFlag=0;
	static bool headFlag=false;
	static uint8_t head[8]={0,0,0,0,0,0,0,0};
	static uint8_t tail[4]={0,0,0,0};
	static uint8_t index=0;
	static uint8_t data[3]={0,0,0};

	uint8_t language=0;

	while (lcddisPort->readAllow()&&(language==0))
	{
		if(headFlag)//֡ͷ���յ�
		{
			if(index==0)
				data[0]=lcddisPort->getChar();
			else if(index==1)
				data[1]=lcddisPort->getChar();
			else if(index==2)
				data[2]=lcddisPort->getChar();
			else if(index==3)
				tail[0]=lcddisPort->getChar();
			else if(index==4)
				tail[1]=lcddisPort->getChar();
			else if(index==5)
				tail[2]=lcddisPort->getChar();
			else if(index==6)
				tail[3]=lcddisPort->getChar();
			index++;
			if(index>6)
			{
				readFlag=0;
				index=0;
				headFlag=false;
				if(tail[0]==0xcc&&tail[1]==0x33&&tail[2]==0xc3&&tail[3]==0x3c)//֡β��ȷ
				{
					for(int8_t i=0;i<3;i++)
					{
						if(data[i]==0x00)
							readFlag++;
					}
					if(readFlag>1)//����
						language=2;
					else
					{
						readFlag=0;
						for(int8_t i=0;i<3;i++)
						{
							if(data[i]==0xee)
								readFlag++;
						}
						if(readFlag>1)//Ӣ��
							language=1;
						}
				}
				readFlag=0;
				tail[0]=0;
				tail[1]=0;
				tail[2]=0;
				tail[3]=0;
				data[0]=0;
				data[1]=0;
				data[2]=0;
			}
		}
		else//֡ͷû�յ�
		{
			head[7]=head[6];
			head[6]=head[5];
			head[5]=head[4];
			head[4]=head[3];
			head[3]=head[2];
			head[2]=head[1];
			head[1]=head[0];
			head[0]=lcddisPort->getChar();
			if(head[7]==0xaa&&head[6]==0x91&&head[5]==EEPROR_ADDR_1&&head[4]==EEPROR_ADDR_2&&head[3]==0x00&&head[2]==0x00&&head[1]==0x00&&head[0]==0x03)
			{
				headFlag=true;
			}
		}
	}
	return language;
}
//���Ͷ�ȡ������������
void LCDdisplay::readLanguageBuf()
{
	lcdParameter->command=0x91;
	
	lcdParameter->buffer[0]=EEPROR_ADDR_1;
	lcdParameter->buffer[1]=EEPROR_ADDR_2;
	lcdParameter->buffer[2]=0x00;
	lcdParameter->buffer[3]=0x00;
	
	lcdParameter->buffer[4]=0x00;
	lcdParameter->buffer[5]=0x03;
	lcdParameter->len=6;
	sendCommand();
}

void LCDdisplay::setAnglePic(uint8_t pic)
{
	anglePic=pic;
}






