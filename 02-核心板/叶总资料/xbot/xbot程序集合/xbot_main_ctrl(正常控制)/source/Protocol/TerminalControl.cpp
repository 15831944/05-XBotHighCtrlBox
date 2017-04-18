/**
  ******************************************************************************
	*�ļ���TerminalControl.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ��Xbot���ն˽�����Э����ʵ��
	*��ע�����ݳ��Ⱥͳ�ʱ�����ú���ƣ���ʱ����������200���ڣ�̫����ܻᵼ�»�����ʧȥ�źź��ܼܺ�ʱ��ֹͣ
  ******************************************************************************  
	*/ 


/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "TerminalControl.h"

/* ���Ͷ��� --------------------------------------------------------------------*/

/* �궨��-----------------------------------------------------------------------*/ 
//����֡���Ⱥ�
#define SEND_BUF_LEN 13
#define RECIVE_BUF_LEN 13

//֡ͷ����
#define FRAME_HEADER 0XA5

//��ʱ����
#define WIRELESS_TIME_TICK_MAX	500
#define WIRE_TIME_TICK_MAX	500

//���캯��
TerminalControl::TerminalControl(SerialPort * p1,SerialPort * p2)
{
	terminalWirePort=p1;
	terminalWireLessPort=p2;
	serialWorkMode=NOSIGNAL_WORK_MODE;
	reciveChin=new RingChain(RECIVE_BUF_LEN);
	sendBuf=new uint8_t[SEND_BUF_LEN];
	reciveBuf=new uint8_t[RECIVE_BUF_LEN];
	for(int i=0;i<SEND_BUF_LEN;i++)
	{
		sendBuf[i]=0;
	}
	for(int i=0;i<RECIVE_BUF_LEN;i++)
	{
		reciveBuf[i]=0;
	}	
}


//��������
TerminalControl::~TerminalControl()
{
	delete reciveChin;
	delete [] sendBuf;
	delete [] reciveBuf;
}

/**
  * ��  �ܣ��������ݵ������ն�
  * ��  ������
  * ����ֵ����
	* ��  ע: ��������߲����޷��͹��ܵĹ���ͨ�������Ӧ�ùرշ��ͣ��������
  */
void TerminalControl::sendcommand()
{
	if(serialWorkMode==WIRE_WORK_MODE)
		terminalWirePort->write(sendBuf,SEND_BUF_LEN);
	else// if(serialWorkMode==WIRELESS_WORK_MODE)
		terminalWireLessPort->write(sendBuf,SEND_BUF_LEN);
}

/**
  * ��  �ܣ����տ����ն˵�����
  * ��  �����������ݵĴ���
  * ����ֵ��
			true:�ɹ�����һ֡
			false:û�н��յ�һ֡����
  */
bool TerminalControl::reciveData(SerialPort *port)
{
	uint8_t checkSum=0;
	bool readFlag=false;
  //���մ�������
	while (port->readAllow()&&(readFlag==false))
	{
		reciveChin->setData(port->getChar());
		reciveChin->next();
		if(reciveChin->getData()==FRAME_HEADER)//���֡ͷ	
		{	
			checkSum+=FRAME_HEADER;
			reciveChin->next();
			if((reciveChin->getData()&0X80)==0x00)//����λ��ȷ
			{
				for(int i=0;i<RECIVE_BUF_LEN-2;i++)
				{
				   checkSum+=reciveChin->getData();
				   reciveChin->next();
				}
				if(checkSum==reciveChin->getData())//У�����ȷ
				{
					//�����ݴ�������
					for(int i=0;i<RECIVE_BUF_LEN;i++)
					{
					   reciveChin->next();
					   reciveBuf[i]=reciveChin->getData();
					}
					readFlag=true;
				}
				reciveChin->next();
			}
			else
			{
				 reciveChin->previous();//�����ϸ��ڵ�	
			}			
		 	checkSum=0;
		}	
	}
	return 	readFlag;
}

/**
  * ��  �ܣ����տ����ն˵����ݲ��Զ��ж������߻�������
  * ��  ������
  * ����ֵ��
			true:�ɹ�����һ֡
			false:û�н��յ�һ֡����
  */
bool TerminalControl::reciveData()
{
	bool tempFlag = false;
	static uint16_t wireRcTimeTick = 0;
	static uint16_t wirelessTimeTick = 0;
	//�������ߵ�����

	tempFlag = reciveData(terminalWirePort);
	if(tempFlag == true)									//���������յ�
	{
		wireRcTimeTick = 0;
		serialWorkMode =  WIRE_WORK_MODE;
	}
	else
	{
		if (wireRcTimeTick<WIRE_TIME_TICK_MAX)				//����Ч����֡��ʱ��ֱ������WIRE_TIME_TICK_MAX����
		{
			wireRcTimeTick++;
		}
		else													//���WIRE_TIME_TICK_MAX������������źţ���ʼ���߽���
		{
			//���տ����������
			tempFlag = reciveData(terminalWireLessPort);
			if(tempFlag == true)								// ���������յ�
			{
				wirelessTimeTick = 0;
				serialWorkMode =  WIRELESS_WORK_MODE;
			}
			else if (wirelessTimeTick<WIRELESS_TIME_TICK_MAX)	//����Ч����֡��ʱ��ֱ������WIRELESS_TIME_TICK_MAX��
			{
				wirelessTimeTick++;
			}
			else												//���WIRELESS_TIME_TICK_MAX������������ź�
			{
				serialWorkMode = NOSIGNAL_WORK_MODE;
			}
		}
	}
	return tempFlag;
}

/**
  * ��  �ܣ����·��͵�����
  * ��  �������µ�����
  * ����ֵ����
  */
void TerminalControl::updateSendBuf(uint8_t * temBuf)
{
	for(int i=0;i<SEND_BUF_LEN;i++)
		sendBuf[i]=temBuf[i];
}









