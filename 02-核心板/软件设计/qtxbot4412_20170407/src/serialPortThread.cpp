
/********************************************************************************
������serialPortThread.cpp��������֡�����߳�
���ߣ�������
���ڣ�2017-01-12
��ע���������ݲ���ѭ�����������ղ�ת��У��

********************************************************************************/

//Linux��ص�ͷ�ļ�
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>
#include <termio.h>

//Qt��ص�ͷ�ļ�
#include <qtextedit.h>
#include <qprogressbar.h>
#include <qtimer.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qstringlist.h>


#include "serialPortThread.h"


SerialPortThread::SerialPortThread(ReceiveFrame *recData,SendFrame *sendData)
{
	receiveFrame=recData;    //������ ʵ�ֹ�������
	sendFrame   =sendData;
	sendFrame->controlData.head=SEND_FRAME_HEAD;
	sendFrame->controlData.command=SEND_FRAME_COMMAND;	
		
	receiveQueue = new CyQueue();    
    
    m_fd = openSerialPort();
    if (m_fd < 0) {
          //  QMessageBox::warning(this, tr("Error"), tr("Fail to open serial port!"));
            return ;
    }

    m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
  //  connect (m_notifier, SIGNAL(activated(int)), this, SLOT(remoteDataIncoming()));
	
	timerSend = new QTimer(this);
    connect(timerSend,SIGNAL(timeout()),this,SLOT(sendData()));
    timerSend->start(100);
}


SerialPortThread::~SerialPortThread()
{
	 if (m_notifier) {
            delete m_notifier;
            m_notifier = 0;
        }

        if (m_fd >= 0) {
            ::close(m_fd);
            m_fd = -1;
        }
}


// Thread  Loop   
void SerialPortThread::run()
{

    forever
    {  

	
	remoteDataIncoming();    //�����շŵ��߳���
    QThread::msleep (2);
    }
} 


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SerialPortThread::openSerialPort()
{
        int fd = -1;
        const char *devName = "/dev/ttySAC3";
        fd = ::open(devName, O_RDWR|O_NONBLOCK);
        if (fd < 0) {
                return -1;
        }
        termios serialAttr;
        memset(&serialAttr, 0, sizeof serialAttr);
        serialAttr.c_iflag = IGNPAR;
        serialAttr.c_cflag = B115200 | HUPCL | CS8 | CREAD | CLOCAL;
        serialAttr.c_cc[VMIN] = 1;
        if (tcsetattr(fd, TCSANOW, &serialAttr) != 0) {
                return -1;
        }
        return fd;
}
        

void SerialPortThread::remoteDataIncoming()
{
        char c;
        //��ȡ�����ַ������浽c��
        if (read(m_fd, &c, sizeof c) != 1) {
               // QMessageBox::warning(this, tr("Error"), tr("Receive error!"));
                return;
        }
        
        
        //�������ݲ���ʾ
        receiveData(c);
        

       
}

bool SerialPortThread::receiveData(char c)
{
	unsigned char tempData[RECEIVE_FRAME_LEN]={0};
	
	static bool isHeadEntry=false;	

    //���
	if(c==RECEIVE_FRAME_HEAD || isHeadEntry)      //�����֡ͷ����֡ͷ�Ѿ���ӣ����ݲſ�����ӣ�����һ�Ų�����ӡ�
	{
		isHeadEntry=true;     //���֡ͷ�Ѿ����
		receiveQueue->EnQueue(c);
	}
	//<��������>
	if(receiveQueue->IsFull())  //�����������ȫ������
	{	
		//����,��ʱ����		
		for(int i=0;i<QUEUESIZE-1;i++)
		{
			receiveQueue->DeQueue(tempData[i]);  //������ʱ����
		}			
		
		isHeadEntry=false;  //֡ͷ�Ѿ�����		

		//��У���
		unsigned char checkSum=0;
		for(int icheck=0;icheck<QUEUESIZE-2;icheck++)
		{
			checkSum+=tempData[icheck];			
		}

		//���У����ȷ�򣬱�������
		if(checkSum==tempData[RECEIVE_FRAME_LEN-1])
		{
			for(int i=0;i<QUEUESIZE-1;i++)
			{
				receiveFrame->byte[i]=tempData[i];				
			}
			if(receiveFrame->byte[1]==0x10)    //�յ����ǻ���������
			{
				emit robotDataSignal();
			}
			else// if(receiveFrame->byte[1]==0x30)//�յ����ǰ�������
			{
				emit keyDataSignal();
			}
			return true;
		}
		//У�鴦����


	}
	//</��������>
	return false;
	
}

void SerialPortThread::sendData()
{
    //QString text;
	//text="wuXY serialPortThread!  /n";
    //if (text.isEmpty()) {
            //return ;
    //}
    
    ::write(m_fd, sendFrame->byte, SEND_FRAME_LEN);// 经实� 得读取到的长度乘2才能收得�    //ui->m_sendEdit->setText("");

}
        
        