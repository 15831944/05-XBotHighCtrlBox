#include <QtGui>

#include "mainframe.h"
#include <QLibrary>
#define POS_MIN 0 
#define POS_MAX 65535 
#define POS_CENTER 32767 



#define ABS_value(x) (((x)<0)?(-(x)):(x))


using namespace std; 	


Mainframe::Mainframe( QWidget * parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));  
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312")); 
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));  
	senddata=NULL;
	commanddata=new char[13];
	commanddata[0]=0x00; 		//���ݷ���0��+�����֣�1��+���ҵ������
	commanddata[1]=0x00;		//�����ٶ� 
	commanddata[2]=0x00;	 	//�ҵ���ٶ�
	commanddata[3]=0;	 		//������ת����+��۸�������+���ģʽ����
	commanddata[4]=0;	 		//С�۸�������+����ػ���������
	commanddata[5]=0;	 		//������ת����+�ڱۿ���+�ڱ�ģʽ����
	commanddata[6]=0;	 		//��̨��ת����+��̨��������+��̨ģʽ����
	commanddata[7]=0x0f;	 	//��ץץ�ֿ���
	commanddata[8]=0;	 		//��������ͷ��������+��̨�����ֿ���+ģʽ��־
	commanddata[9]=0;	 		//�ƹ����+����+����
	commanddata[10]=0x80;	 	//ͼ���ķ�Ƶ����+�������
	commanddata[11]=0;	 		//��������ѡ��+�𶯿���+2*GLED
	commanddata[12]=0;	 		//У���
	modelflag=0;
	
	backjoy=new unsigned char[12];
	
	backjoy[0]=0; 	//ka
	backjoy[1]=0; 	//kb
	backjoy[2]=0; 	//ke
	backjoy[3]=0; 	//kf
	backjoy[4]=0; 	//kh&km
	backjoy[5]=0; 	//ki&kj&kg
	
	backjoy[6]=128; //jlx
	backjoy[7]=128; //jly
	
	backjoy[8]=128; //jrx
	backjoy[9]=128; //jry
	
	backjoy[10]=0;  //adc1
	backjoy[11]=0;  //adc2
	
	ctrsizeflag=0;
	verticalflag=0;
	horizontalflag=0;
	videoflag=false;	
	mouseOK=false;
	
	winposflag=0;
	
	armspeedflag=0;
	runapeedflag=0;
		
	armsp=0;
	runsp=0;
		
	focflag=0;
	focsp=0;
	
	
	Qt::WindowFlags flags = windowFlags();
	setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);

	setupUi(this);
	//w=(double)(QApplication::desktop()->width())/800.0;
	//h=(double)(QApplication::desktop()->height())/600.0;
	w=1;                          
	h=1;
	setGeometry(0,0,800*w,600*h);
	
    mycompass=new Compass(this);
    myspeed=new Speed(this);
    mypitch=new Pitch(this);
	mybattery=new Battery(this);
	mybattery_1=new Battery(this);
	mybattery_2=new Battery(this);
	mybattery_3=new Battery(this);
	mybattery_4=new Battery(this);
	mybattery_5=new Battery(this);
	myroll=new Roll(this);
	mywid_2d=new Modle_2d(this);
	myselect=new Selectfalg(this);
	mywid=new mymodel(this);
	
	mysignalshow=new SignalShow(this);
	myarms=new SpeedGrade(this);
	myruns=new SpeedGrade(this);
	myctrsize=new CtrSize(this);
	myfocaldis=new FocalDis(this);
		
	backdata=new unsigned char[26];//��������ռ�
	mycompass->setGeometry(124*w,498*h,108*w,100*h);
		
	/********************************************/
	
	mywid_2d->setGeometry(234*w,435*h,332*w,164*h);
	mywid->setGeometry(234*w,435*h,332*w,164*h);
	
	/********************************************/
	
		
	mypitch->setGeometry(647*w,434*h,100*w,94*h);
	myspeed->setGeometry(568*w,498*h,108*w,100*h);
	myroll->setGeometry(54*w,434*h,100*w,94*h);
	//myfocaldis->setGeometry(4*w,244*h,54*w,52*h);
	mysignalshow->setGeometry(570*w,460*h,70*w,21*h);

	myarms->setGeometry(148*w,432*h,84*w,22*h);

	myruns->setGeometry(568*w,432*h,84*w,22*h);
	myctrsize->setGeometry(538*w,276*h,83*w,21*h);
	mybattery  ->setGeometry(58*w,545*h,14*w,38*h);
	mybattery_1->setGeometry(74*w,545*h,14*w,38*h);
	mybattery_2->setGeometry(90*w,545*h,14*w,38*h);
	mybattery_3->setGeometry(106*w,545*h,14*w,38*h);
	mybattery_4->setGeometry(700*w,545*h,14*w,38*h);
	mybattery_5->setGeometry(720*w,545*h,14*w,38*h);
	myselect->setGeometry(0,0,800*w,600*h);
	//	myselect->setGeometry(0,0,2*w,2*h);
	label->setGeometry(105*w,585*h,80*w,16*h);
	label_4->setGeometry(696*w,585*h,92*w,16*h);
	mywid->dabiPitch(180);
	mywid->xiaobiPitch(172);
	mywid->shouwanPitch(7);
	timer= new QTimer(this);

	myctrsize->hide();
	myfocaldis->hide();
    QFont ft; //���ñ�ǩ�����С
    ft.setPointSize(9*h);
	label->setFont(ft);
	label_4->setFont(ft);
	//�����źźͲ�
	connect(myctrsize, SIGNAL(sizeflagchange(int)), this, SLOT( changmodelsize(int)));
	
	connect(timer, SIGNAL(timeout()), this, SLOT(sendcommand())); 	
	timer->start(80);//���ö�ʱ��Ϊ80����
	serialport->setPort(1);
	serialport->open();
	
	receiveThread=new ReceiveThread(serialport);
	connect(receiveThread, SIGNAL(dataReceived(QByteArray)), this, SLOT( readyRead(QByteArray)));
	connect(receiveThread, SIGNAL(dataReceived1(QByteArray)), this, SLOT( disposejoy(QByteArray)));
	receiveThread->start();
	//avideo->setGeometry(56*w,0*h,2*w,2*h);
	avideo->setGeometry(56*w,0*h,688*w,432*h);
	//horizontalSlider  ->setGeometry(60*w,10*h,300*w,25*h);
	//horizontalSlider_2->setGeometry(60*w,40*h,300*w,25*h);
	//horizontalSlider_3->setGeometry(60*w,70*h,300*w,25*h);
	//horizontalSlider_4->setGeometry(60*w,100*h,300*w,25*h);
	//horizontalSlider_5->setGeometry(60*w,130*h,300*w,25*h);
	//horizontalSlider_6->setGeometry(60*w,160*h,300*w,25*h);
	//horizontalSlider_7->setGeometry(60*w,190*h,300*w,25*h);
	//horizontalSlider_8->setGeometry(60*w,220*h,300*w,25*h);
	//horizontalSlider_9->setGeometry(60*w,250*h,300*w,25*h);
	//connect(horizontalSlider, SIGNAL(valueChanged(int)), mywid, SLOT( shouzhuaMediate(int)));
	//
	//connect(horizontalSlider_2, SIGNAL(valueChanged(int)), mywid, SLOT( dabiPitch(int)));
	//connect(horizontalSlider_3, SIGNAL(valueChanged(int)), mywid, SLOT( dabiRotate(int)));
	//connect(horizontalSlider_4, SIGNAL(valueChanged(int)), mywid, SLOT( xiaobiPitch(int)));
	//connect(horizontalSlider_5, SIGNAL(valueChanged(int)), mywid, SLOT( yuntaiPitch(int)));
	//connect(horizontalSlider_6, SIGNAL(valueChanged(int)), mywid, SLOT( yuntaiRotate(int)));
	//connect(horizontalSlider_7, SIGNAL(valueChanged(int)), mywid, SLOT( shouwanPitch(int)));
	//connect(horizontalSlider_8, SIGNAL(valueChanged(int)), mywid, SLOT( shouwanRotate(int)));
	//connect(horizontalSlider_9, SIGNAL(valueChanged(int)), mywid, SLOT( zhibiPitch(int)));
	
	if(!pix.load(":/images/back11.jpg",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
	{
		QMessageBox::information(this, "", "failed load file");
	}
	if(!pix1.load(":/images/back22.jpg",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
	{
		QMessageBox::information(this, "", "failed load file");
	}
	if(!pix2.load(":/images/back33.jpg",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
	{
		QMessageBox::information(this, "", "failed load file");
	}
}


Mainframe::~Mainframe()
{
	delete mywid;
	delete mycompass;
	delete myspeed;
	delete myroll;
	delete mypitch;
	delete mybattery;
	delete mybattery_1;
	delete mybattery_2;
	delete mybattery_3;
	delete mybattery_4;
	delete mybattery_5;
	delete myarms;
	delete myruns;
	delete mysignalshow;
	delete myctrsize;
	delete myfocaldis;
	delete myselect;
	receiveThread->exit() ;
	delete receiveThread;  
    receiveThread = NULL;
    delete [] backdata;
    delete [] commanddata;
    delete [] backjoy;
}

void Mainframe::sendcommand()//��ʱ�������Ӧ��������ʾʱ��ͷ�������
{
	//��ʾʱ��
	static int s=0;
	QDateTime datatime = QDateTime::currentDateTime();
	if(s!= datatime.time().second ())
	{
		QString strtime = datatime.time().toString();
		label_4->setText(strtime);
		s = datatime.time().second ();
	}
	
	if(ctrsizeflag==1)
	{
		changmodelsize(3);
	}
	else if(ctrsizeflag==2)
	{
		changmodelsize(1);
	}
	
	if(verticalflag==1)
	{
		mywid->updateview_y(mywid->getangle_h()-0.1);
	}
	else if(verticalflag==2)
	{
		mywid->updateview_y(mywid->getangle_h()+0.1);
	} 
	
	if(armspeedflag==1)
	{
		armsp++;
		if(armsp==6)
		{
			armsp=0;
			if((myarms->value())<7)
				myarms->setValue((myarms->value())+1);
		}
	}
	else if(armspeedflag==2)
	{
		armsp++;
		if(armsp==6)
		{
			armsp=0;
			if((myarms->value())>1)
				myarms->setValue((myarms->value())-1);
		}
	}
	else
	{
		armsp=0;
	}
	
	if(runapeedflag==1)
	{
		runsp++;
		if(runsp==6)
		{
			runsp=0;
			if((myruns->value())<7)
				myruns->setValue((myruns->value())+1);
		}
	}
	else if(runapeedflag==2)
	{
		runsp++;
		if(runsp==6)
		{
			runsp=0;
			if((myruns->value())>1)
				myruns->setValue((myruns->value())-1);
		}
	}
	else
	{
		runsp=0;
	}

	if(focflag==1)
	{
		focsp++;
		if(focsp==6)
		{
			if(myfocaldis->value()<31)
				myfocaldis->setValue((myfocaldis->value())+1);
			commanddata[10]&=0xe0;//ǰ��λ������
			commanddata[10]|=((char)(myfocaldis->value()));				
			focsp=0;	
		}
		
	}
	else if(focflag==2)
	{
		focsp++;
		if(focsp==6)
		{
			if(myfocaldis->value()>0)
				myfocaldis->setValue((myfocaldis->value())-1);
			commanddata[10]&=0xe0;//ǰ��λ������
			commanddata[10]|=((char)(myfocaldis->value()));				
			focsp=0;	
		}
	}
	else
	{
		focsp=0;
	}		
	if(horizontalflag==1)
	{
		mywid->updateview_xz(mywid->getangle_v()+0.1);
	}
	else if(horizontalflag==2)
	{
		mywid->updateview_xz(mywid->getangle_v()-0.1);
	}	
	//��������
	senddata=NULL;
	senddata.append((char)0xa5);
	senddata.append((char)0xa0);
	commanddata[12]=0xa5;
	commanddata[12]+=0xa0;
	for(int i=0;i<12;i++)
	{
		commanddata[12]+=commanddata[i];
	}
	senddata.append(commanddata,13);
	
	serialport->write(senddata);
}
void Mainframe::disposejoy(QByteArray joy)
{
	if(((unsigned char)joy.at(5)&0x02)==0x02&&(unsigned char)joy.at(0)==0&&(unsigned char)joy.at(1)==0&&(unsigned char)joy.at(2)==0&&(unsigned char)joy.at(3)==0&&(unsigned char)joy.at(4)==0)//�ı�ģʽ
	{
		backjoy[5]=(unsigned char)joy.at(5);//���ݰ�ť
		if((backjoy[5]&0x01)==0x01)
		{
			if(modelflag!=0)
				modelflag--;
			else
				modelflag=2;
			update();
		}
		else
		{
			if(modelflag!=2)
				modelflag++;
			else
				modelflag=0;
			update();	
		}
		myselect->setValue(modelflag);
		if(modelflag==0)
		{
			commanddata[8]&=0xf0;//����ֱ�ӿ���ģʽ
			commanddata[3]&=0xf8;	   //״̬λ��0
			commanddata[5]&=0xf8;	   //״̬λ��0
			myselect->setValue_3(0x00);
		}			
	}
	else
	{
		if((unsigned char)joy.at(5)!=backjoy[5])
		{
			backjoy[5]=(unsigned char)joy.at(5);
			if((backjoy[5]&0x0c)==0x04)//j1
			{				
				if((backjoy[5]&0x01)==0x01)
				{
					armspeedflag=1;
					if((myarms->value())<7)
						myarms->setValue((myarms->value())+1);
				}
				else
				{
					runapeedflag=1;
					if((myruns->value())<7)
						myruns->setValue((myruns->value())+1);
				}
			}
			else if((backjoy[5]&0x0c)==0x08)//j2
			{
				if((backjoy[5]&0x01)==0x01)
				{
					armspeedflag=2;
					if((myarms->value())>1)
						myarms->setValue((myarms->value())-1);
				}
				else
				{
					runapeedflag=2;
					if((myruns->value())>1)
						myruns->setValue((myruns->value())-1);				
				}	
			}
			else
			{
				armspeedflag=0;
				runapeedflag=0;
			}
			//if((backjoy[5]&0x10)==0x10)//g1 ������
			//{
					//
			//}
			//if((backjoy[5]&0x20)==0x20)//g2 �������俪��
			//{
					//
			//}
		}	
	}
	
	
	if((unsigned char)joy.at(0)!=backjoy[0])//key_a
	{
		backjoy[0]=(unsigned char)joy.at(0);
		switch(modelflag)
		{
			case 0:
				if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
					break;
				if((backjoy[0]&0x03)==0x01)//С������
				{
					commanddata[4]&=0x7f;//BIT7��0
					commanddata[4]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[4]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_1(((int)myselect->value_1()&0xfffc)|0x01);

				}
				else if((backjoy[0]&0x03)==0x02)//С���¸�
				{
					commanddata[4]|=0x80;//BIT7��1
					commanddata[4]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[4]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_1(((int)myselect->value_1()&0xfffc)|0x02);
					
				}
				else	//(backjoy[0]&0x03)==0x03 || (backjoy[0]&0x03)==0x00
				{
					commanddata[4]&=0x8f;//BIT 4 5 6 λ��0
					myselect->setValue_1((int)myselect->value_1()&0xfffc);
				}
				
				if((backjoy[0]&0x0c)==0x04)//��������
				{
					commanddata[4]&=0xf7;//BIT3��0 
					commanddata[4]&=0xf8;//ǰ��λ��0
					//commanddata[4]|=3;
					commanddata[4]|=((char)(myarms->value())); //BIT 0 1 2 λ���ٶ�
					myselect->setValue_1(((int)myselect->value_1()&0xfff3)|0x04);
					
				}
				else if((backjoy[0]&0x0c)==0x08)//�����¸�
				{
					commanddata[4]|=0x08;//BIT3��1
					commanddata[4]&=0xf8;//ǰ��λ��0
					//commanddata[4]|=3;
					commanddata[4]|=((char)(myarms->value())); //BIT 0 1 2 λ���ٶ�
					myselect->setValue_1(((int)myselect->value_1()&0xfff3)|0x08);
					
				}
				else
				{
					commanddata[4]&=0xf8;//ǰ��λ��0
					myselect->setValue_1((int)myselect->value_1()&0xfff3);
				}
				
				if((backjoy[0]&0x30)==0x10)//�������
				{
					commanddata[8]&=0x3f;//BIT7 6 ��0 0
					commanddata[8]|=0x80;//BIT7 6 ��1 0
					myselect->setValue_1(((int)myselect->value_1()&0xffcf)|0x10);
					
				}
				else if((backjoy[0]&0x30)==0x20)//����¸�
				{
					commanddata[8]&=0x3f;//BIT7 6 ��0 0
					commanddata[8]|=0x40;//BIT7 6 ��1 0
					myselect->setValue_1(((int)myselect->value_1()&0xffcf)|0x20);
					
				}
				else
				{
					commanddata[8]&=0x3f;//BIT7 6 ��0 0	
					myselect->setValue_1((int)myselect->value_1()&0xffcf);									
				}
				
				if((backjoy[0]&0xc0)==0x40)//֧���¸�
				{
					commanddata[5]&=0xf7;//BIT3��0
					commanddata[5]&=0xf8;//ǰ��λ��0
					commanddata[5]|=((char)myarms->value()); //BIT 0 1 2 λ���ٶ� 
					myselect->setValue_1(((int)myselect->value_1()&0xff3f)|0x40);
					
				}
				else if((backjoy[0]&0xc0)==0x80)//֧������
				{
					commanddata[5]|=0x08;//BIT3��1
					commanddata[5]&=0xf8;//ǰ��λ��0
					commanddata[5]|=((char)myarms->value()); //BIT 0 1 2 λ���ٶ�
					myselect->setValue_1(((int)myselect->value_1()&0xff3f)|0x80);
					
				}
				else
				{
					commanddata[5]&=0xf8;//ǰ��λ��0			
					myselect->setValue_1((int)myselect->value_1()&0xff3f);
				}
			
				break;
			case 1:
				switch(backjoy[0])
				{
					case 0x01:			//֧��̧��
						commanddata[3]&=0xf8;	   //��?
						commanddata[8]&=0xf0;	   //��־��Ϊֱ�ӿ���								
						if((commanddata[5]&0x07)==0x01)//�жϸ�״̬�Ƿ�����
						{
							commanddata[5]&=0xf8;	   //״̬λ��0
							myselect->setValue_2(myselect->value_2()&0xf0c0);
						}		   
						else//��״̬û����
						{
							commanddata[8]|=0x08;
							commanddata[5]&=0xf8;	   //״̬λ��0
							commanddata[5]|=0x01;
							myselect->setValue_2((myselect->value_2()&0xf0c0)|0x01);
						}						
						break;
					case 0x02:				//֧��֧��
						commanddata[3]&=0xf8;	   //״̬λ��0	
						commanddata[8]&=0xf0;	   //��־��Ϊֱ�ӿ���						
						if((commanddata[5]&0x07)==0x02)//�жϸ�״̬�Ƿ�����
						{
							commanddata[5]&=0xf8;	   //״̬λ��0
							myselect->setValue_2(myselect->value_2()&0xf0c0);
						}		   
						else//��״̬û����
						{
							commanddata[8]|=0x08;
							commanddata[5]&=0xf8;	   //״̬λ��0
							commanddata[5]|=0x02;
							myselect->setValue_2((myselect->value_2()&0xf0c0)|0x02);
						}				
						break;				
					case 0x04:		//֧��ˮƽ
						commanddata[3]&=0xf8;	   //״̬λ��0	
						commanddata[8]&=0xf0;	   //��־��Ϊֱ�ӿ���						
						if((commanddata[5]&0x07)==0x04)//�жϸ�״̬�Ƿ�����
						{
							commanddata[5]&=0xf8;	   //״̬λ��0
							myselect->setValue_2(myselect->value_2()&0xf0c0);
						}		   
						else//��״̬û����
						{
							commanddata[8]|=0x08;
							commanddata[5]&=0xf8;	   //״̬λ��0
							commanddata[5]|=0x04;
							myselect->setValue_2((myselect->value_2()&0xf0c0)|0x04);
						}
						break;
					case 0x08:	//֧������
						commanddata[3]&=0xf8;	   //״̬λ��0	
						commanddata[8]&=0xf0;	   //��־��Ϊֱ�ӿ���						
						if((commanddata[5]&0x07)==0x03)//�жϸ�״̬�Ƿ�����
						{
							commanddata[5]&=0xf8;	   //״̬λ��0
							myselect->setValue_2(myselect->value_2()&0xf0c0);
						}		   
						else//��״̬û����
						{
							commanddata[8]|=0x08;
							commanddata[5]&=0xf8;	   
							commanddata[5]|=0x03;
							myselect->setValue_2((myselect->value_2()&0xf0c0)|0x08);
						}
						break;											
					case 0x10://֧��΢֧
						commanddata[3]&=0xf8;	   //״̬λ��0	
						commanddata[8]&=0xf0;	   //��־��Ϊֱ�ӿ���						
						if((commanddata[5]&0x07)==0x05)//�жϸ�״̬�Ƿ�����
						{
							commanddata[5]&=0xf8;	   //״̬λ��0
							myselect->setValue_2(myselect->value_2()&0xf0c0);
						}		   
						else//��״̬û����
						{
							commanddata[8]|=0x08;
							commanddata[5]&=0xf8;	   
							commanddata[5]|=0x05;
							myselect->setValue_2((myselect->value_2()&0xf0c0)|0x10);
						}
						break;
					case 0x20:// �ֱ�ǰ��
						commanddata[4]&=0xf8;//ǰ��λ��0
						if((commanddata[3]&0x07)==0x04)//�жϸ�״̬�Ƿ�����
						{
						commanddata[8]&=0xf0; //��־��Ϊֱ�ӿ���
						commanddata[3]&=0xf8; //״̬λ��0
						commanddata[5]&=0xf8; //״̬λ��0
						myselect->setValue_2(myselect->value_2()&0xf0c0);
						}
						else//��״̬û����
						{
						commanddata[8]|=0x0c;
						commanddata[3]&=0xf8; //״̬λ��0
						commanddata[3]|=0x04; //��ץǰ�۲�
						commanddata[5]&=0xf8; //״̬λ��0
						myselect->setValue_2((myselect->value_2()&0xf0c0)|0x20);
						}
						break;
					case 0x40:
					case 0x80:
						break;	
					default:
						//commanddata[7]&=0x8f;//BIT 4 5 6 λ��0
						//myselect->setValue_2(myselect->value_2()&0xf0c0);
						break;											
				}
				break;
			case 2:
				switch(backjoy[0])
				{
					//case 0x01://��������ͷ���࣬ͼ��Ŵ�
						//myfocaldis->setValue((myfocaldis->value())+1);
						//if(myfocaldis->value()==32)
							//myfocaldis->setValue(31);
						//commanddata[10]&=0xe0;//ǰ��λ������
						//commanddata[10]|=((char)(myfocaldis->value()));
						//myselect->setValue_3(((int)myselect->value_3()&0x3f)|0x40);					
						//break;
					//case 0x02://��С����ͷ����
						//myfocaldis->setValue((myfocaldis->value())-1);
						//commanddata[10]&=0xe0;//ǰ��λ������
						//commanddata[10]|=((char)(myfocaldis->value()));
						//myselect->setValue_3(((int)myselect->value_3()&0x3f)|0x80);					
						//break;
					case 0x04://�򿪺͹ر�������
						if((mycompass->lightflag)==false)
						{
							mycompass->setlightflag(true);
							commanddata[9]|=0xe0;
							myselect->setValue_3(((int)myselect->value_3()&0xfffb)|0x04);
						}
						else
						{
							mycompass->setlightflag(false);
							commanddata[9]&=0x1f;
							myselect->setValue_3((int)myselect->value_3()&0xfffb);
						}					
						break;							
					default:	
						//myselect->setValue_3((int)myselect->value_3()&0x3f);
						break;							
				}
				
				if((backjoy[0]&0x03)==0x01)//���󽹾�
				{
					focflag=1;
					if(myfocaldis->value()<31)
						myfocaldis->setValue((myfocaldis->value())+1);
					commanddata[10]&=0xe0;//ǰ��λ������
					commanddata[10]|=((char)(myfocaldis->value()));
					myselect->setValue_3(((int)myselect->value_3()&0xfffc)|0x01);
				}
				else if((backjoy[0]&0x03)==0x02)//��С����
				{
					focflag=2;
					if(myfocaldis->value()>0)
						myfocaldis->setValue((myfocaldis->value())-1);
					commanddata[10]&=0xe0;//ǰ��λ������
					commanddata[10]|=((char)(myfocaldis->value()));
					myselect->setValue_3(((int)myselect->value_3()&0xfffc)|0x02);	
				}
				else
				{
					myselect->setValue_3((int)myselect->value_3()&0xfffc);	
				}
				break;
		}
		
	}
	
	if((unsigned char)joy.at(1)!=backjoy[1])//key_b
	{
		backjoy[1]=(unsigned char)joy.at(1);
		
		switch(modelflag)
		{
			case 0:
				if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
					break;
				if((backjoy[1]&0x03)==0x01)		//�������
				{
					commanddata[3]&=0xf7;//BIT3��0
					commanddata[3]&=0xf8;//ǰ��λ��0
					commanddata[3]|=((char)myarms->value()); //BIT 0 1 2 λ���ٶ�
					myselect->setValue_1(((int)myselect->value_1()&0xfcff)|0x100);

				}
				else if((backjoy[1]&0x03)==0x02)//����¸�
				{
					commanddata[3]|=0x08;//BIT3��1
					commanddata[3]&=0xf8;//ǰ��λ��0
					commanddata[3]|=((char)myarms->value()); //BIT 0 1 2 λ���ٶ�
					myselect->setValue_1(((int)myselect->value_1()&0xfcff)|0x200);

				}
				else
				{
					commanddata[3]&=0xf8;//ǰ��λ��0
					myselect->setValue_1((int)myselect->value_1()&0xfcff);
				}
				
				if((backjoy[1]&0x0c)==0x04)		//�������
				{
					commanddata[3]|=0x80;//BIT7��1
					commanddata[3]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[3]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_1(((int)myselect->value_1()&0xf3ff)|0x400);
					
				}
				else if((backjoy[1]&0x0c)==0x08)//�������
				{
					commanddata[3]&=0x7f;//BIT7��0
					commanddata[3]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[3]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_1(((int)myselect->value_1()&0xf3ff)|0x800);
				}
				else
				{
					commanddata[3]&=0x8f;//BIT 4 5 6 λ��0
					myselect->setValue_1((int)myselect->value_1()&0xf3ff);
				}
				
				if((backjoy[1]&0x30)==0x10)		//��ץ���
				{
					commanddata[7]|=0x80;//BIT7��1
					commanddata[7]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[7]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_1(((int)myselect->value_1()&0xcfff)|0x1000);
					
				}
				else if((backjoy[1]&0x30)==0x20)//��ץ�ɿ�
				{
					commanddata[7]&=0x7f;//BIT7��0
					commanddata[7]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[7]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_1(((int)myselect->value_1()&0xcfff)|0x2000);
					
				}
				else
				{
					commanddata[7]&=0x8f;//BIT 4 5 6 λ��0
					myselect->setValue_1((int)myselect->value_1()&0xcfff);
				}
				
				if((backjoy[1]&0xc0)==0x40)		//��ץ����
				{
					commanddata[5]|=0x80;//BIT7��1
					commanddata[5]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[5]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_1(((int)myselect->value_1()&0x3fff)|0x4000);
					
				}
				else if((backjoy[1]&0xc0)==0x80)//��ץ����
				{
					commanddata[5]&=0x7f;//BIT7��0
					commanddata[5]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[5]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_1(((int)myselect->value_1()&0x3fff)|0x8000);
					
				}
				else
				{
					commanddata[5]&=0x8f;//BIT 4 5 6 λ��0
					myselect->setValue_1((int)myselect->value_1()&0x3fff);
				}
				break;
				
			case 1:
				switch(backjoy[1])
				{
					case 0x01:
						commanddata[4]&=0xf8;//ǰ��λ��0
						if((commanddata[3]&0x07)==0x05)//�жϸ�״̬�Ƿ�����
						{
						commanddata[8]&=0xf0; //��־��Ϊֱ�ӿ���
						commanddata[3]&=0xf8; //״̬λ��0
						commanddata[5]&=0xf8; //״̬λ��0
						myselect->setValue_2(myselect->value_2()&0xf0c0);
						}
						else//��״̬û����
						{
						commanddata[8]|=0x0c;
						commanddata[3]&=0xf8; //״̬λ��0
						commanddata[3]|=0x05; //��ץȫչ��
						commanddata[5]&=0xf8; //״̬λ��0
						commanddata[5]|=0x05;
						myselect->setValue_2((myselect->value_2()&0xf0c0)|0x100); 
						}
						break;
					case 0x02:
						commanddata[4]&=0xf8;//ǰ��λ��0
						if((commanddata[3]&0x07)==0x03)//�жϸ�״̬�Ƿ�����
						{
						commanddata[8]&=0xf0; //��־��Ϊֱ�ӿ���
						commanddata[3]&=0xf8; //״̬λ��0
						commanddata[5]&=0xf8; //״̬λ��0
						myselect->setValue_2(myselect->value_2()&0xf0c0);
						}
						else//��״̬û����
						{
						commanddata[8]|=0x0c;
						commanddata[3]&=0xf8; //״̬λ��0
						commanddata[3]|=0x03; //��ץ����
						commanddata[5]&=0xf8; //״̬λ��0
						commanddata[5]|=0x03; 
						myselect->setValue_2((myselect->value_2()&0xf0c0)|0x200);
						}
					
						break;
					case 0x04:
						commanddata[4]&=0xf8;//ǰ��λ��0
						if((commanddata[3]&0x07)==0x02)//�жϸ�״̬�Ƿ�����
						{
						commanddata[8]&=0xf0; //��־��Ϊֱ�ӿ���
						commanddata[3]&=0xf8; //״̬λ��0
						commanddata[5]&=0xf8; //״̬λ��0
						myselect->setValue_2(myselect->value_2()&0xf0c0);
						}
						else//��״̬û����
						{
						commanddata[8]|=0x0c;
						commanddata[3]&=0xf8; //״̬λ��0
						commanddata[3]|=0x02; //��ץǰץȡ
						commanddata[5]&=0xf8; //״̬λ��0
						commanddata[5]|=0x05;
						myselect->setValue_2((myselect->value_2()&0xf0c0)|0x400);
						//label_18 ->setText("��ά����ģʽ����"); 
						}
					
						break;
					case 0x08:
						commanddata[4]&=0xf8;//ǰ��λ��0
						if((commanddata[3]&0x07)==0x01)//�жϸ�״̬�Ƿ�����
						{
						commanddata[8]&=0xf0; //��־��Ϊֱ�ӿ���
						commanddata[3]&=0xf8; //״̬λ��0
						commanddata[5]&=0xf8; //״̬λ��0
						myselect->setValue_2(myselect->value_2()&0xf0c0);
						}
						else//��״̬û����
						{
						commanddata[8]|=0x0c;
						commanddata[3]&=0xf8; //״̬λ��0
						commanddata[3]|=0x01; //��ץ��չ��
						commanddata[5]&=0xf8; //״̬λ��0
						commanddata[5]|=0x05;
						myselect->setValue_2((myselect->value_2()&0xf0c0)|0x800);
						}
						break;
					default:
						commanddata[4]&=0xf8;//ǰ��λ��0
						//myselect->setValue_2(myselect->value_2()&0xf0c0);
						break;
				}
				if((backjoy[1]&0x30)==0x10)		//��ץ���
				{
					commanddata[7]|=0x80;//BIT7��1
					commanddata[7]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[7]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_2((myselect->value_2()&0xcfff)|0x1000);
					
				}
				else if((backjoy[1]&0x30)==0x20)//��ץ�ɿ�
				{
					commanddata[7]&=0x7f;//BIT7��0
					commanddata[7]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[7]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_2((myselect->value_2()&0xcfff)|0x2000);
					
				}
				else
				{
					commanddata[7]&=0x8f;//BIT 4 5 6 λ��0
					myselect->setValue_2(myselect->value_2()&0xcfff);
				}
				
				if((backjoy[1]&0xc0)==0x40)		//��ץ����
				{
					commanddata[5]|=0x80;//BIT7��1
					commanddata[5]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[5]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_2((myselect->value_2()&0x3fff)|0x04000);
					
				}
				else if((backjoy[1]&0xc0)==0x80)//��ץ����
				{
					commanddata[5]&=0x7f;//BIT7��0
					commanddata[5]&=0x8f;//BIT 4 5 6 λ��0
					commanddata[5]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
					myselect->setValue_2((myselect->value_2()&0x3fff)|0x8000);
					
				}
				else
				{
					commanddata[5]&=0x8f;//BIT 4 5 6 λ��0
					myselect->setValue_2(myselect->value_2()&0x3fff);
				}																							
				break;
			case 2:
				switch(backjoy[1])
				{
					case 0x01://��̨����ͷ��ʾ
						commanddata[10]&=0x1f;
						myselect->setValue_3(((int)myselect->value_3()&0xe0ff)|0x100);	
						break;
					case 0x02://�г�����ͷ��ʾ
						commanddata[10]&=0x1f;
						commanddata[10]|=0x40;
						myselect->setValue_3(((int)myselect->value_3()&0xe0ff)|0x200);					
						break;
					case 0x04://��ץǰ������ͷ��ʾ
						commanddata[10]&=0x1f;
						commanddata[10]|=0x20;
						myselect->setValue_3(((int)myselect->value_3()&0xe0ff)|0x400);
						break;	
					case 0x08://��ץ��������ͷ��ʾ
						commanddata[10]&=0x1f;
						commanddata[10]|=0x60;
						myselect->setValue_3(((int)myselect->value_3()&0xe0ff)|0x800);
						break;		
					case 0x10://����ͷ�ۺ���ʾ
						commanddata[10]&=0x1f;//����λ��0
						commanddata[10]|=0x80;						
						myselect->setValue_3(((int)myselect->value_3()&0xe0ff)|0x1000);					
						break;	
				}			
				break;
			}
	}	

	if((unsigned char)joy.at(2)!=backjoy[2])//key_e 
	{
		backjoy[2]=(unsigned char)joy.at(2);
		if(((unsigned char)joy.at(5)&0x01)==0x01)//shift������
		{	
			if((commanddata[3]&0x07)==0x06)//�������3Dģʽ��
			{
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[8]&=0xf0;
				commanddata[3]&=0xf8;	   //״̬λ��0 ȡ��3Dģʽ
			}
			if((backjoy[2]&0x01)==0x01)//��̨����ͷ��ʾ
			{
				commanddata[10]&=0x1f;
				myselect->setValue_3(((int)myselect->value_3()&0xe0ff)|0x100);				
			}
			if((backjoy[2]&0x02)==0x02)//�г�����ͷ��ʾ
			{
				commanddata[10]&=0x1f;
				commanddata[10]|=0x40;
				myselect->setValue_3(((int)myselect->value_3()&0xe0ff)|0x200);						
			}
			if((backjoy[2]&0x04)==0x04)//��ץǰ������ͷ��ʾ
			{
				commanddata[10]&=0x1f;
				commanddata[10]|=0x20;
				myselect->setValue_3(((int)myselect->value_3()&0xe0ff)|0x400);				
			}
			if((backjoy[2]&0x08)==0x08)//��ץ��������ͷ��ʾ
			{
				commanddata[10]&=0x1f;
				commanddata[10]|=0x60;
				myselect->setValue_3(((int)myselect->value_3()&0xe0ff)|0x800);				
			}
			if((backjoy[2]&0x10)==0x10)//�ķ�����ʾ��������ͷ		
			{
				commanddata[10]&=0x1f;//����λ��0
				commanddata[10]|=0x80;						
				myselect->setValue_3(((int)myselect->value_3()&0xe0ff)|0x1000);	
			}			
		}
		else//shift��û����
		{
			if((backjoy[2]&0x0f)==0x01&&(backjoy[0]==0)&&(backjoy[1]==0)&&(((unsigned char)joy.at(3)&0x03)==0))//Y��ǰ
			{
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	//״̬λ��0
				commanddata[3]|=0x06;	//3dģʽ��	
				commanddata[6]&=0xf7;//BIT3��0
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[6]|=((char)myarms->value());//���ٶ�λ      //BIT 0 1 2 λ���ٶ�	
			}
			else if((backjoy[2]&0x0f)==0x02&&(backjoy[0]==0)&&(backjoy[1]==0)&&(((unsigned char)joy.at(3)&0x03)==0))//Y���
			{
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	//״̬λ��0
				commanddata[3]|=0x06;	//3dģʽ��					
				commanddata[6]|=0x08;//BIT3��1
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[6]|=(char)myarms->value();//���ٶ�λ      //BIT 4 5 6 λ���ٶ�			
			}
			else if((backjoy[2]&0x0f)==0x04&&(backjoy[0]==0)&&(backjoy[1]==0)&&(((unsigned char)joy.at(3)&0x03)==0))//X����
			{
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	//״̬λ��0
				commanddata[3]|=0x06;	//3dģʽ��	
				commanddata[6]|=0x80;//BIT7��1
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[6]|=((char)myarms->value()<<4);//���ٶ�λ      //BIT 0 1 2 λ���ٶ�				
			}
			else if((backjoy[2]&0x0f)==0x08&&(backjoy[0]==0)&&(backjoy[1]==0)&&(((unsigned char)joy.at(3)&0x03)==0))//X����
			{
				
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	//״̬λ��0
				commanddata[3]|=0x06;	//3dģʽ��					
				commanddata[6]&=0x7f;//BIT7��0
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[6]|=((char)myarms->value()<<4);//���ٶ�λ      //BIT 4 5 6 λ���ٶ�				
			}
			else
			{
				if((commanddata[3]&0x07)==0x06)//�������3Dģʽ��
				{
					commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
					commanddata[8]&=0xf0;
					commanddata[3]&=0xf8;	   //״̬λ��0 ȡ��3Dģʽ
				}
				if(hide_flag&&backjoy[2]==0x10&&videoflag==false)
				{
					
					mywid->setGeometry(234*w,435*h,332*w,164*h);
					mywid_2d->setDis(false);
					hide_flag=false;
				}
				else if(backjoy[2]==0x10&&videoflag==false)
				{
					mywid->setGeometry(234*w,635*h,332*w,164*h);
					mywid_2d->setDis(true);
					
					hide_flag=true;
				}
			}			
			
		}
	}

	if((unsigned char)joy.at(3)!=backjoy[3])//key_f
	{
		backjoy[3]=(unsigned char)joy.at(3);

		//myselect->setValue_1((int)myselect->value_1()&0x3f);	
		if(((unsigned char)joy.at(5)&0x01)==0x01)//shift������
		{
			if((commanddata[3]&0x07)==0x06)//�������3Dģʽ��
			{
				commanddata[8]&=0xf0;
				commanddata[3]&=0xf8;	    //״̬λ��0 ȡ��3Dģʽ
				commanddata[4]&=0xf8;		//ǰ��λ��0
			}
			myselect->setValue_1((int)myselect->value_1()&0x3f);
			
			if((backjoy[3]&0x03)==0x01)
			{
				//mywid->updateview_y(mywid->getangle_h()-0.1);
				verticalflag=1;				
			}
			else if((backjoy[3]&0x03)==0x02)
			{
				//mywid->updateview_y(mywid->getangle_h()+0.1);
				verticalflag=2;
			}
			else
			{
				verticalflag=0;
			}
			
			if((backjoy[3]&0x0c)==0x04)
			{
				//mywid->updateview_xz(mywid->getangle_v()+0.1);
				horizontalflag=1;
			}
			else if((backjoy[3]&0x0c)==0x08)
			{
				//mywid->updateview_xz(mywid->getangle_v()-0.1);
				horizontalflag=2;
			}
			else
			{
				horizontalflag=0;
			}
			
			if((backjoy[3]&0x10)==0x10)//�Ŵ�3dģ��
			{
				ctrsizeflag=2;
			}
			else
			{
				ctrsizeflag=0;
			}			
		}
		else
		{
			horizontalflag=0;
			verticalflag=0;
			if((backjoy[3]&0x03)==0x01&&(backjoy[0]==0)&&(backjoy[1]==0)&&((backjoy[2]&0x0f)==0))//z��������
			{
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	   //״̬λ��0
				commanddata[3]|=0x06;		//3dģʽ��	
				
				commanddata[4]&=0xf7;//BIT3��0							
				commanddata[4]&=0xf8;//ǰ��λ��0
				commanddata[4]|=((char)myarms->value());//���ٶ�λ						
			}
			else if((backjoy[3]&0x03)==0x02&&(backjoy[0]==0)&&(backjoy[1]==0)&&((backjoy[2]&0x0f)==0))//z��������
			{
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	   //״̬λ��0
				commanddata[3]|=0x06;		//3dģʽ��
				
				commanddata[4]|=0x08;	   //��־��1
				commanddata[4]&=0xf8;//ǰ��λ��0
				commanddata[4]|=((char)myarms->value());//���ٶ�λ			myselect->setValue_3((myselect->value_3()&0x3000)|0x20);				
			}
			else if((commanddata[3]&0x07)==0x06)//�������3Dģʽ��
			{
				commanddata[8]&=0xf0;
				commanddata[3]&=0xf8;	   //״̬λ��0 ȡ��3Dģʽ
				commanddata[4]&=0xf8;//ǰ��λ��0
			}
			
			if((backjoy[3]&0x0c)==0x04)//���󽹾�
			{
				focflag=1;
				if(myfocaldis->value()<31)
					myfocaldis->setValue((myfocaldis->value())+1);
				commanddata[10]&=0xe0;//ǰ��λ������
				commanddata[10]|=((char)(myfocaldis->value()));
				myselect->setValue_3(((int)myselect->value_3()&0xfffc)|0x01);
			}
			else if((backjoy[3]&0x0c)==0x08)//��С����
			{
				focflag=2;
				if(myfocaldis->value()>0)
					myfocaldis->setValue((myfocaldis->value())-1);
				commanddata[10]&=0xe0;//ǰ��λ������
				commanddata[10]|=((char)(myfocaldis->value()));
				myselect->setValue_3(((int)myselect->value_3()&0xfffc)|0x02);	
			}
			else
			{
				focflag=0;
				myselect->setValue_3((int)myselect->value_3()&0xfffc);	
			}
			
			if((backjoy[3]&0x10)==0x10)//��С3Dģ��
			{
				ctrsizeflag=1;
			}
			else
			{
				ctrsizeflag=0;
			}
		}
	}

	if((unsigned char)joy.at(4)!=backjoy[4])//key_hm
	{
		backjoy[4]=(unsigned char)joy.at(4);
		if((backjoy[4]&0x1f)==0x01)//h1
		{
			modelflag=0;
			myselect->setValue(modelflag);
			update();
			commanddata[8]&=0xf0;//����ֱ�ӿ���ģʽ
			commanddata[3]&=0xf8;	   //״̬λ��0
			commanddata[5]&=0xf8;	   //״̬λ��0
		}
		else if((backjoy[4]&0x1f)==0x02)
		{
			modelflag=1;
			myselect->setValue(modelflag);
			update();
		}
		else if((backjoy[4]&0x1f)==0x04)
		{
			modelflag=2;
			myselect->setValue(modelflag);
			update();
		}
		else if((backjoy[4]&0x1f)==0x08)
		{
			//Ԥ����ģʽ
		}
		else if((backjoy[4]&0x1f)==0x10)
		{
			//Ԥ����ģʽ
		}
		
		
		if((backjoy[4]&0xe0)==0x20)//�߿�
		{
			if(commanddata[11]&0x80)
			{
				commanddata[11]&=0x7f;
				mysignalshow->setwiredflag(true);
			}
			else
			{
				mysignalshow->setwiredflag(false);
				commanddata[11]|=0x80;	
			}	

		}
		if((backjoy[4]&0xe0)==0x40)//����
		{
			if((mycompass->lightflag)==false)
			{
				mycompass->setlightflag(true);
				commanddata[9]|=0xe0;
				myselect->setValue_3(((int)myselect->value_3()&0xfffb)|0x04);
			}
			else
			{
				mycompass->setlightflag(false);
				commanddata[9]&=0x1f;
				myselect->setValue_3((int)myselect->value_3()&0xfffb);
			}			
		}
		if((backjoy[4]&0xe0)==0x80)//һ��ͼ��Ŵ�
		{

			if(videoflag)
			{
				avideo->setGeometry(56*w,0*h,688*w,432*h);
				if(hide_flag==false)
					mywid->setGeometry(234*w,435*h,332*w,164*h);
				myselect->setFull(false);
				videoflag=false;
			}
			else
			{
				avideo->setGeometry(0,0,800*w,576*h);
				if(hide_flag==false)
					mywid->setGeometry(0,601*h,332*w,164*h);
				myselect->setFull(true);
				videoflag=true;
			}	
		}
	}
	
	if((unsigned char)joy.at(6)!=backjoy[6])//��̨������ת
	{
		backjoy[6]=(unsigned char)joy.at(6);
		signed char speed=(signed char)joy.at(6);
		//ȡ��3ά����
		commanddata[8]&=0xf0;
		commanddata[3]&=0xf8;	   //״̬λ��0
		commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
		commanddata[4]&=0xf8;//ǰ��λ��0
		commanddata[5]&=0xf8;//ǰ��λ��0		
		//myselect->setValue_3(myselect->value_3()&0x3060);
		
		if(speed==0)//��תֹͣ
		{
			commanddata[6]&=0x8f;//BIT 4 5 6 λ��0	
		}
		else
		if(speed < 0)//��̨����
		{
			commanddata[6]|=0x80;//BIT7��1
			commanddata[6]&=0x8f;//BIT 4 5 6 λ��0
			commanddata[6]|=(((unsigned char)((-speed)/18)<<4));      //BIT 4 5 6 λ���ٶ�
		}	
		if(speed>0)//��̨����
		{
			commanddata[6]&=0x7f;//BIT7��0
			commanddata[6]&=0x8f;//BIT 4 5 6 λ��0
			commanddata[6]|=(((unsigned char)((speed)/18)<<4));      //BIT 4 5 6 λ���ٶ�		
		}		
	}
	
	if((unsigned char)joy.at(7)!=backjoy[7])//��̨���¸���
	{

		
		
		commanddata[8]&=0xf0;
		commanddata[3]&=0xf8;	   //״̬λ��0
		commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
		commanddata[4]&=0xf8;//ǰ��λ��0
		commanddata[5]&=0xf8;//ǰ��λ��0	
		
		
		
		
		
		
				
		backjoy[7]=(unsigned char)joy.at(7);
		
		signed char speed=(signed char)joy.at(7);
		
		if(speed==0)//��̨����ֹͣ
		{
			commanddata[6]&=0xf8;//BIT 0 1 2 λ��0	
		}
		else	
		if(speed<0)//��̨�¸�
		{
			commanddata[6]&=0xf7;//BIT3��0
			
			commanddata[6]&=0xf8;//BIT 0 1 2 λ��0
			commanddata[6]|=((unsigned char)((-speed)/18));      //BIT 0 1 2 λ���ٶ�		
		}
		else	
		if(speed>0)//��̨����
		{
			commanddata[6]|=0x08;//BIT3��1
			commanddata[6]&=0xf8;//BIT 0 1 2 λ��0
			commanddata[6]|=((unsigned char)((speed)/18));      //BIT 0 1 2 λ���ٶ�
		}		
	}
	
	if((unsigned char)joy.at(8)!=backjoy[8]||(unsigned char)joy.at(9)!=backjoy[9])//�г�����
	{		
		backjoy[8]=(unsigned char)joy.at(8);
		backjoy[9]=(unsigned char)joy.at(9);
		
		signed char x=(signed char)joy.at(8);
		signed char y=(signed char)joy.at(9);
		
		int ls=((y+x/3)/6)*myruns->value();
		int rs=((y-x/3)/6)*myruns->value();

		if(rs<-160)
			rs=-160;
		if(rs>160)
			rs=160;
		if(ls<-160)
			ls=-160;
		if(ls>160)
			ls=160;
			
		myspeed->setValue(ls);
		myspeed->setValue_1(rs);
							
		if(ls==0&&rs==0)
			commanddata[0]&=0xF0;
		else if(ls==0&&rs<0)
		{
			commanddata[0]&=0xF0;
			commanddata[0]|=0x02;
		}
		else if(ls==0&&rs>0)
		{
			commanddata[0]&=0xF0;
			commanddata[0]|=0x01;				
		}
		else if(ls<0&&rs==0)
		{
			commanddata[0]&=0xF0;
			commanddata[0]|=0x08;			
		}
		else if(ls<0&&rs<0)
		{
			commanddata[0]&=0xF0;
			commanddata[0]|=0x0A;			
		}
		else if(ls<0&&rs>0)
		{
			commanddata[0]&=0xF0;
			commanddata[0]|=0x09;				
		}
		else if(ls>0&&rs==0)
		{
			commanddata[0]&=0xF0;
			commanddata[0]|=0x04;				
		}
		else if(ls>0&&rs<0)
		{
			commanddata[0]&=0xF0;
			commanddata[0]|=0x06;				
		}
		else if(ls>0&&rs>0)
		{
			commanddata[0]&=0xF0;
			commanddata[0]|=0x05;				
		}
		commanddata[1]=ABS_value(ls);
		commanddata[2]=ABS_value(rs);			
	}

	if((unsigned char)joy.at(10)!=backjoy[10])//���1��ѹ
	{

		backjoy[10]=(unsigned char)joy.at(10);
		mybattery_4->setValue(backjoy[10]);
	}
	if((unsigned char)joy.at(11)!=backjoy[11])//���2��ѹ
	{
		backjoy[11]=(unsigned char)joy.at(11);
		mybattery_5->setValue(backjoy[11]);
	}
}

void Mainframe::readyRead(QByteArray str)
{	
	mutexflag.lock(); //���������� 
	busyflag=true;
	mutexflag.unlock(); //����������

	if(backdata[0]!=str.at(1))//�����ٶ�
	{
		backdata[0]=str.at(1);
		//myspeed->setValue(backdata[0]);
	}
	if(backdata[1]!=str.at(2))//�ҵ���ٶ�
	{
		backdata[1]=str.at(2);
		//myspeed->setValue_1(backdata[1]);
	}
	unsigned char a=(unsigned char)(str.at(0));
	
	switch(a)
	{
		case 0x80:
			if(backdata[2]!=str.at(3))//������ת�Ƕ�
			{
				backdata[2]=str.at(3);
				mywid->dabiRotate(backdata[2]*2);
				mycompass->setValue((360-backdata[2]*2)%360);
				mywid_2d->setValue_7(backdata[2]*2);
			}
			if(backdata[3]!=str.at(4))//��צ��ת�Ƕ�
			{
				backdata[3]=str.at(4);
				mywid->shouwanRotate(-backdata[3]*2);
				mywid_2d->setValue_6(backdata[3]*2);
			}
			if(backdata[4]!=str.at(5))//��צץ�ֿ��
			{
				backdata[4]=str.at(5);
				mywid->shouzhuaMediate(backdata[4]*2);
				mywid_2d->setValue_5(backdata[4]*2);
			}
			if(backdata[5]!=str.at(6))//�ڱ�ģʽ����??????????
			{
				backdata[5]=str.at(6);
			}
			if(backdata[6]!=str.at(7))//��ص�ѹ1
			{
				backdata[6]=str.at(7);
				//mybattery->setValue(backdata[6]*2);
			}															
			break;
		case 0x81:
			if(backdata[7]!=str.at(3))//��۸����Ƕ�
			{
				backdata[7]=str.at(3);
				mywid->dabiPitch(backdata[7]*2);
				mywid_2d->setValue_1(backdata[7]*2);
			}
			if(backdata[8]!=str.at(4))//��̨�����Ƕ�
			{
				backdata[8]=str.at(4);
				mywid->yuntaiPitch(backdata[8]*2+180);
				mywid_2d->setValue_4(backdata[8]*2);
			}
			if(backdata[9]!=str.at(5))//ǰ֧�۽Ƕ�
			{
				backdata[9]=str.at(5);
				mywid->zhibiPitch(backdata[9]*2);
				mypitch->setValue_1((backdata[9]*2+180)%360);
				mywid_2d->setValue_9(backdata[9]*2);
			}
			if(backdata[10]!=str.at(6))//��е��ģʽ??????
			{
				backdata[10]=str.at(6);
			}
			if(backdata[11]!=str.at(7))//��ص�ѹ2
			{
				backdata[11]=str.at(7);
				//mybattery_1->setValue(backdata[11]);
			}				
			break;
		case 0x82:
			if(backdata[12]!=str.at(3))//С�۸����Ƕ�
			{
				backdata[12]=str.at(3);
				mywid->xiaobiPitch(backdata[12]*2);
				mywid_2d->setValue_2(backdata[12]*2);
			}
			if(backdata[13]!=str.at(4))//��̨��ת�Ƕ�
			{
				backdata[13]=str.at(4);
				mywid->yuntaiRotate(backdata[13]*2);
				mywid_2d->setValue_8(backdata[13]*2);
			}
			if(backdata[14]!=str.at(5))//����
			{
				backdata[14]=str.at(5);
				
			}
			if(backdata[15]!=str.at(6))//����
			{
				backdata[15]=str.at(6);
				
			}
			if(backdata[16]!=str.at(7))//��ص�ѹ3
			{
				backdata[16]=str.at(7);
				//mybattery_2->setValue(backdata[16]);
			}			
			break;
			//
		case 0x83:
			if(backdata[17]!=str.at(3))//��ؽڽǶ�
			{
				backdata[17]=str.at(3);
				mywid->shouwanPitch(backdata[17]*2-6);
				mywid_2d->setValue_3(backdata[17]*2);
			}
			if(backdata[18]!=str.at(4))//����ͷ�����Ƕ�
			{
				backdata[18]=str.at(4);
				mywid->qianjinxiangjiPitch(backdata[18]*2);
			}
			if(backdata[19]!=str.at(5))//ϵͳ��ѹ
			{
				backdata[19]=str.at(5);
				
			}
			if(backdata[20]!=str.at(6))//����
			{
				backdata[20]=str.at(6);
				
			}
			if(backdata[21]!=str.at(7))//��ص�ѹ4
			{
				backdata[21]=str.at(7);
				//mybattery_3->setValue(backdata[21]);
			}			
			break;
	}
	mutexflag.lock(); //���������� 
	busyflag=false;
	mutexflag.unlock(); //���������� 	
}

void Mainframe::showmyself()
{
		this->show();
		this->move(0,height());
}

void Mainframe::changmodelsize(int flag)
{
	double fl=mywid->getfocalLength();
	if(flag==1)
	{
		if(fl>1.8)
		{
			fl-=0.05;
			mywid->updatesize(fl);
		}
	}
	if(flag==3)
	{
		if(fl<6.1)
		{
			fl+=0.05;
			mywid->updatesize(fl);
		}		
	}
	if(flag==2)
	{
		if(fl!=3.0)
		{
			fl=3.0;
			mywid->updatesize(fl);
		}
	}
}
void Mainframe::hidemenu()
{
  //mymenu->hide();
}
void Mainframe::paintEvent(QPaintEvent *)
{

 	 //static const QString ModStr[5][16] = { {"С������","С���¸�","��������","�����¸�","�������","����¸�","֧���¸�","֧������"
							  //,"�������","����¸�","�������","�������","��ץ���","��ץ�ɿ�","��ץ����","��ץ����"}
							 //,{"֧��̧��","֧��֧��","֧��ˮƽ","֧������","��ץ���","��ץ�ɿ�","Ԥ������","Ԥ������"
							  //,"�ֱ�ȫչ","�ֱ�����","�ֱ�ǰ��","�ֱ۰�չ","�ֱ�ǰ��","Ԥ������","Ԥ������","Ԥ������"}
							 //,{"�Ŵ���Ƶ","��С��Ƶ","��������","�ۺ���ʾ","Ԥ������","Ԥ������","Ԥ������","Ԥ������"
							  //,"CH1ȫ��","CH2ȫ��","CH3ȫ��","CH4ȫ��","Ԥ������","Ԥ������","Ԥ������","Ԥ������"}
							 //,{"Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������"
							  //,"Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������"}
							 //,{"Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������"
							  //,"Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������","Ԥ������"}};		
	QPainter painter(this);	
	painter.setRenderHint(QPainter::Antialiasing);
	painter.scale(width()/800.0,height()/600.0);
	//QPixmap pix;
	switch(modelflag)
	{
		//case 0:
			//if(!pix.load("/data/run/back11.jpg",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
			//{
				//QMessageBox::information(this, "", "failed load file");
			//}
			//break;			
		//case 1:
			//if(!pix.load("/data/run/back22.jpg",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
			//{
				//QMessageBox::information(this, "", "failed load file");
			//}
			//break;			
		//case 2:
			//if(!pix.load("/data/run/back33.jpg",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
			//{
				//QMessageBox::information(this, "", "failed load file");
			//}
			//break; 
			
		case 0:
			//if(!pix.load(":/images/back11.jpg",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
			//{
				//QMessageBox::information(this, "", "failed load file");
			//}
			//QPixmap pixs=pix.scaled (800,600);
			painter.drawPixmap ( 0, 0, 800,600,pix);
			break;			
		case 1:
			//if(!pix.load(":/images/back22.jpg",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
			//{
				//QMessageBox::information(this, "", "failed load file");
			//}
			//QPixmap pixs1=pix1.scaled (800,600);
			painter.drawPixmap ( 0, 0, 800,600,pix1);
			break;			
		case 2:
			//if(!pix.load(":/images/back33.jpg",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
			//{
				//QMessageBox::information(this, "", "failed load file");
			//}
			//QPixmap pixs2=pix2.scaled (800,600);
			painter.drawPixmap ( 0, 0, 800,600,pix2);
			break; 			
							
	}
	//QPixmap pixs=pix.scaled (800,600);
	//painter.drawPixmap ( 0, 0, 800,600,pix);
}

