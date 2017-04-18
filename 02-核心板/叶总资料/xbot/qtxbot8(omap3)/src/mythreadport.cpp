#include "mythreadport.h"   
//#include <QThread>
#include <QMessageBox>

//#include "joystick.h"


using namespace std;

typedef struct ricedata//�������һ�����ݵĽṹ��
{
    unsigned char data;
    ricedata *next;
    ricedata *last;
}RICEDATA;

QMutex mutexflag;
bool busyflag=false;	//�źŴ�����ɱ�־
/****************************** SENDTHREAD ************************************ 
 ******************************************************************************/  
SendThread::SendThread(SerialPort  &adrPort): port(adrPort)  
{  
    dataToSend.clear();  
    stopped = false;  
}  
/******************************* Distructor ***********************************/  
SendThread::~SendThread()  
{  
    if (isRunning())  
    {  
        stopSending();//ֹͣ�������� �ȴ��߳��˳�  
        wait();  
    }  
}  
/******************************* Methods **************************************/  
// Add the data to the Send Queue   
void SendThread::addDataToSend(const QByteArray &dataToAdd)  
{  
    QMutexLocker locker(&mutexSend);  
    for (int i=0; i<dataToAdd.size(); i++)  
        dataToSend.enqueue(QByteArray(1,dataToAdd.at(i)));  
    if (!isRunning())  
        start();  
}  
// Stop the sending operation   
void SendThread::stopSending()  
{  
    stopped = true;  
}  
// Thread Send Loop   
void SendThread::run()
{  
    QByteArray byteArray;  
    forever  // while(1)������������������ 
    {  
        mutexSend.lock();  
        if (dataToSend.isEmpty() || stopped)  
        {  
            mutexSend.unlock();  
            stopped = false;  
            break;  
        }  
        byteArray = dataToSend.dequeue();  
        mutexSend.unlock();  
        port.write(byteArray);  
    }  
}  

/******************************************************************************* 
 ******************************* RECEIVETHREAD ********************************* 
 ******************************************************************************/  
 
//void ReceiveThread::openJoy() //���ֱ� 
//{
	//unsigned int num = qJoyGetNumDevs(); 
	//if(num <= 0)
	//{ 
		//QMessageBox::information(NULL,"Warning","ϵͳ��֧����Ϸ��!");
		//return; 
	//} 
//}

ReceiveThread::ReceiveThread(SerialPort *adrPort): port(adrPort)  
{
	//port=adrPort;
    stopped = false;  
}  
/******************************* Distructor ***********************************/  
ReceiveThread::~ReceiveThread()  
{  
    if (isRunning())  
    {  
        stopReceiving();  
        wait();  
    }  
}  
/******************************* Methods **************************************/  
// Stop the sending operation   
void ReceiveThread::stopReceiving()  
{  
    stopped = true;  
}  

// Thread Receive Loop   
void ReceiveThread::run()  
{  
	RICEDATA *sp=new RICEDATA[15];//����ʮ��������λһ��ѭ��
	QByteArray tem=NULL;			 //��ʱ������
    unsigned char checksum=0;		 //У���
	QByteArray recedata=NULL;     	 //������
	QByteArray backupdata[4]={NULL,NULL,NULL,NULL};     //����
	QByteArray backjoydata=NULL;		 //��������
	bool backupsentflag=false;			 //�����Ƿ��ͱ�־ ��Ӧ����backupdata 0 1 2 3
	bool freeflag=false;
	
	bool backupsentflag1=false;			 //���������Ƿ��ͱ�־ ��Ӧ����backupdata 0 1 2 3
		
	int backupflag=0;
    for(int i=0;i<15;i++)//����˫��������ÿ���ڵ�����ݳ�ʼ��Ϊ 0
    {
        sp[i].data=0;
        if(i==14)
        {
            sp[i].next=sp;
        }
        else
        {
            sp[i].next=&sp[i+1];
        }
        
        if(i==0)
        {
            sp[i].last=&sp[i+14];
        }
        else
        {
            sp[i].last=&sp[i-1];
        }
    }//����������
    RICEDATA *pos=sp;
    
    
    //int joybot=0;
	//int joyposx1=0;
	//int joyposy1=0;
	//int joyposx2=0;
	//int joyposy2=0;
	//int joypov=0;
	//
	//int joydata[6]={0,0,0,0,0,0};//����
    //
	//JOYINFOEX joyInfoEx; 							//���������Ϸ�����ݵĽṹ��
	//joyInfoEx.dwSize = sizeof(typeof(JOYINFOEX));   //����ṹ��Ĵ�С������ϵͳ�Ĵ�С��һ����
	//joyInfoEx.dwFlags = (int)JOY_RETURNBUTTONS;		//��־λ����ʾ������Щ���� 
	
    forever
	{
		if (stopped)  
        {  
            stopped = false; 
            break;  							//����ѭ��
        }
        tem=port->read(1);
		if (!tem.isEmpty())  				    //��Ϊ�� ������
        {
        	 pos->data=(char)(tem.at(0));
        	 pos=pos->next;
        	 if(pos->data==0xa5)				//�¸������Ƿ��֡ͷ������ͬ
        	 {
        	 	checksum+=pos->data;
       	 		pos=pos->next;
       	 		if(pos->data==0x10)				//����������
       	 		{
       	 			checksum+=pos->data;
       	 			pos=pos->next;
       	 			if((pos->data==0x80)||(pos->data==0x81)||(pos->data==0x82)||(pos->data==0x83))
	       	 		{
	       	 			int bf=((pos->data)&0x03);
		        	 	for(int i=0;i<11;i++)
		        	 	{
		        	 		recedata.append(pos->data);//���뵽�����ֽ�����,���õ�����
		        	 		checksum+=pos->data;
		        	 		pos=pos->next;
		       	 		}
		       	 		checksum+=pos->data;			//NC 0x66
		        	 	pos=pos->next;
		       			if(checksum==pos->data)//���У�����ȷ��������ȷ֡����
		       			{
		       				backupflag=bf;
		       				if(!backupdata[backupflag].isNull())			//���ݲ�Ϊ�գ����ͱ���֡�����������𣬾ͷ��ͣ��������±���
		       				{
		       					for(int i=0;i<11;++i)
		       					{
		       						if(backupdata[backupflag].at(i)!=recedata.at(i))
		       						{
						        		backupdata[backupflag]=recedata;		//���±���
						        		mutexflag.lock(); //���������� 
						        		freeflag=busyflag;
						        		mutexflag.unlock(); //���������� 
										if(!freeflag)					//UI�̲߳�æ
										{
											emit dataReceived(recedata);//�����ź�
											backupsentflag=true;
										}	
		       							else
		       								backupsentflag=false;   //�ź�δ���ͣ��ñ��ݷ��ͱ�־Ϊ�٣���ʾ�����´�ѭ����������������Է���
		       							break;					//����forѭ��
		      						}
		      					}
		       				}
		       				else								//����Ϊ�գ�ֱ�ӷ��ͣ�������
		       				{
		       					backupdata[backupflag]=recedata;		//����
		       					mutexflag.lock(); //���������� 
				        		freeflag=busyflag;
				        		mutexflag.unlock(); //���������� 
								if(!freeflag)					//UI�̲߳�æ
								{
						        	emit dataReceived(recedata);//�����ź�
						        	backupsentflag=true;
								}		       					backupdata[backupflag]=recedata;		//����
		       					mutexflag.lock(); //���������� 
				        		freeflag=busyflag;
				        		mutexflag.unlock(); //���������� 
								if(!freeflag)					//UI�̲߳�æ
								{
						        	emit dataReceived(recedata);//�����ź�
						        	backupsentflag=true;
								}
						        else
						        {
		       						backupsentflag=false;   //�ź�δ���ͣ��ñ��ݷ��ͱ�־Ϊ�٣���ʾ�����´�ѭ����������������Է���					        	
					        	}
		   					}       	 			
		   	 			}
		   	 			else									//У��ʹ��󣬷��ͱ�������
	        			{
				        	if(!backupsentflag && !backupdata[backupflag].isNull())//���ݷ��ͱ�־Ϊ�٣����ұ��ݲ�Ϊ��
							{
				        		mutexflag.lock(); //���������� 
				        		freeflag=busyflag;
				        		mutexflag.unlock(); //���������� 
								if(!freeflag)					//UI�̲߳�æ
								{
									emit dataReceived(backupdata[backupflag]);//���ͱ�������
									backupsentflag=true;		  //���������Ѿ����ͣ��ñ�־Ϊ��
								}
																	//UI�߳�æ�������ͱ��ݣ��Զ������´�ѭ��
				        	}
	        			}
	        			recedata=NULL;					//��֡����
	        			checksum=0;						//У�������
						pos=pos->next;                  //ָ��ָ���¸��ڵ�
	      	 		}
	      	 		else//���������ݣ�
	      	 		{
	      	 			checksum=0;						//У�������
	      	 			pos=pos->last;//ָ��ָ���ϸ��ڵ�
	      	 			pos=pos->last;
     	 			}
       	 		}
      	 		else if(pos->data==0x30)//��������
      	 		{
      	 			checksum+=pos->data;
					pos=pos->next;
					for(int i=0;i<12;i++)
					{
						recedata.append(pos->data);//���뵽�����ֽ�����,���õ�����
						checksum+=pos->data;
						pos=pos->next;
					}
					if(checksum==pos->data)//���У�����ȷ��������ȷ֡����
		       		{
	       				if(!backjoydata.isNull())			//���ݲ�Ϊ�գ����ͱ���֡�����������𣬾ͷ��ͣ��������±���
	       				{
	       					for(int i=0;i<12;++i)
	       					{
	       						if(backjoydata.at(i)!=recedata.at(i))
	       						{
					        		mutexflag.lock(); //���������� 
					        		freeflag=busyflag;
					        		mutexflag.unlock(); //���������� 
									if(!freeflag)					//UI�̲߳�æ
									{
										if(((recedata.at(5)&0x02)!=0x02)||((backjoydata.at(5)&0x02)!=0x02))
										{
											emit dataReceived1(recedata);//�����ź�	
										}
										backupsentflag1=true;
									}	
	       							else
	       								backupsentflag1=false;   	//�ź�δ���ͣ��ñ��ݷ��ͱ�־Ϊ�٣���ʾ�����´�ѭ����������������Է���
	       							backjoydata=recedata;		//���±���
	       							break;							//����forѭ��
	      						}
	      					}
	       				}
	       				else			//����Ϊ�գ�ֱ�ӷ���
	       				{
	       					
	       					mutexflag.lock(); //���������� 
			        		freeflag=busyflag;
			        		mutexflag.unlock(); //���������� 
							if(!freeflag)					//UI�̲߳�æ
							{
								if(((recedata.at(5)&0x02)!=0x02)||((backjoydata.at(5)&0x02)!=0x02))
								{
									emit dataReceived1(recedata);//�����ź�	
								}
					        	backupsentflag1=true;
							}
					        else
					        {
	       						backupsentflag1=false;   //�ź�δ���ͣ��ñ��ݷ��ͱ�־Ϊ�٣���ʾ�����´�ѭ����������������Է���					        	
				        	}	       					
	       				}
	       				backjoydata=recedata;		//����
		       		}
		       		else									//У��ʹ��󣬷��ͱ�������
        			{
			        	if(!backupsentflag1 && !backjoydata.isNull())//���ݷ��ͱ�־Ϊ�٣����ұ��ݲ�Ϊ��
						{
			        		mutexflag.lock(); //���������� 
			        		freeflag=busyflag;
			        		mutexflag.unlock(); //���������� 
							if(!freeflag)					//UI�̲߳�æ
							{
								if(((recedata.at(5)&0x02)!=0x02)||((backjoydata.at(5)&0x02)!=0x02))
								{
									emit dataReceived1(recedata);//�����ź�
								}
								backupsentflag1=true;		  //���������Ѿ����ͣ��ñ�־Ϊ��
							}
																//UI�߳�æ�������ͱ��ݣ��Զ������´�ѭ��
			        	}
        			}
        			recedata=NULL;					//��֡����
	        		checksum=0;						//У�������
					pos=pos->next;//ָ��ָ���¸��ڵ�
     	 		}
      	 		else
      	 		{
      	 			pos=pos->last;
     	 		}

        	 }
        }
        else
        	QThread::usleep(1); 
        tem.clear();    	
	}
	delete [] sp; 

}
