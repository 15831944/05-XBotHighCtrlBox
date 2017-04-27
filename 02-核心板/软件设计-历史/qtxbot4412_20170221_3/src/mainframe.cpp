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

	Qt::WindowFlags flags = windowFlags();
	setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);

	setupUi(this);
	//w=(double)(QApplication::desktop()->width())/800.0;
	//h=(double)(QApplication::desktop()->height())/600.0;
	w=1;                          
	h=1;
	setGeometry(0,0,800*w,600*h);
	
	initPix();	
	initData();
	initComponent();
	initConnect();
	
	//�����ɼ�����
	cameraProcess = new ProcessImage(this);
	cameraProcess->setGeometry(80,32,640*w,416*h);
	cameraProcess->label->setGeometry(0,0,640*w,416*h);
	//receiveThread->start();
	//timer->start(80);
	//serialport->open();
}
//��ʼ�����汳��
void Mainframe::initPix()
{
	if(!pix.load(":/images/m2.png",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither))
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

//��ʼ��ȫ�ֱ���
void Mainframe::initData()
{
	//senddata=NULL;
	backdata=new unsigned char[26];//��������ռ�
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
	myfocaldis=0;
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
}

//��ʼ������
void Mainframe::initComponent()
{
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
	// mywid=new mymodel(this);
	mysignalshow=new SignalShow(this);
	myarms=new SpeedGrade(this);
	myruns=new SpeedGrade(this);
	lightShow=new Light(this);
	coordShow=new Coord(this);
	videoFlagShow=new VideoFlag(this);
	sizeCtr3d=new Change3d(this);
	
	//avideo=new VideoDis(this);
	
	timer= new QTimer(this);	
	//
	//receiveFrame = new ReceiveFrame;
    //serialPortThread = new SerialPortThread(receiveFrame);
	//receiveThread=new ReceiveThread(serialport);
	
	but_M1=new VirtualDisjunctor(this);
	but_M2=new VirtualDisjunctor(this);
	but_M3=new VirtualDisjunctor(this);
	but_M4=new VirtualDisjunctor(this);
	but_M5=new VirtualDisjunctor(this);
	
	
	but_asg1=new VirtualDisjunctor(this);
	but_asg2=new VirtualDisjunctor(this);
	but_rsg1=new VirtualDisjunctor(this);
	but_rsg2=new VirtualDisjunctor(this);
	
	but_M1_A1=new VirtualDisjunctor(this);
	but_M1_A2=new VirtualDisjunctor(this);
	but_M1_A3=new VirtualDisjunctor(this);
	but_M1_A4=new VirtualDisjunctor(this);
	but_M1_A5=new VirtualDisjunctor(this);
	but_M1_A6=new VirtualDisjunctor(this);	
	but_M1_A7=new VirtualDisjunctor(this);
	but_M1_A8=new VirtualDisjunctor(this);
	
	but_M1_B1=new VirtualDisjunctor(this);
	but_M1_B2=new VirtualDisjunctor(this);
	but_M1_B3=new VirtualDisjunctor(this);
	but_M1_B4=new VirtualDisjunctor(this);
	but_M1_B5=new VirtualDisjunctor(this);
	but_M1_B6=new VirtualDisjunctor(this);
	but_M1_B7=new VirtualDisjunctor(this);
	but_M1_B8=new VirtualDisjunctor(this);
	
	but_M2_A1=new VirtualDisjunctor(this);
	but_M2_A2=new VirtualDisjunctor(this);
	but_M2_A3=new VirtualDisjunctor(this);
	but_M2_A4=new VirtualDisjunctor(this);
	but_M2_A5=new VirtualDisjunctor(this);
	but_M2_A6=new VirtualDisjunctor(this);	
	but_M2_A7=new VirtualDisjunctor(this);
	but_M2_A8=new VirtualDisjunctor(this);
	
	but_M2_B1=new VirtualDisjunctor(this);
	but_M2_B2=new VirtualDisjunctor(this);
	but_M2_B3=new VirtualDisjunctor(this);
	but_M2_B4=new VirtualDisjunctor(this);
	//but_M2_B5=new VirtualDisjunctor(this);
	//but_M2_B6=new VirtualDisjunctor(this);
	//but_M2_B7=new VirtualDisjunctor(this);
	//but_M2_B8=new VirtualDisjunctor(this);
	
	but_M3_A1=new VirtualDisjunctor(this);
	but_M3_A2=new VirtualDisjunctor(this);
	but_M3_A3=new VirtualDisjunctor(this);
	but_M3_A4=new VirtualDisjunctor(this);
	but_M3_A5=new VirtualDisjunctor(this);
	but_M3_A6=new VirtualDisjunctor(this);	
	but_M3_A7=new VirtualDisjunctor(this);
	but_M3_A8=new VirtualDisjunctor(this);
	
	but_M3_B1=new VirtualDisjunctor(this);
	but_M3_B2=new VirtualDisjunctor(this);
	but_M3_B3=new VirtualDisjunctor(this);
	but_M3_B4=new VirtualDisjunctor(this);
	but_M3_B5=new VirtualDisjunctor(this);
	but_M3_B6=new VirtualDisjunctor(this);
	but_M3_B7=new VirtualDisjunctor(this);
	but_M3_B8=new VirtualDisjunctor(this);	

	but_M1_A1->setPressIco(":/images/xb_sy_2.png");
	but_M1_A2->setPressIco(":/images/xb_xf_2.png");
	but_M1_A3->setPressIco(":/images/sw_sy_2.png");
	but_M1_A4->setPressIco(":/images/sw_xf_2.png");
	but_M1_A5->setPressIco(":/images/xj_sy_2.png");
	but_M1_A6->setPressIco(":/images/xj_xf_2.png");
	but_M1_A7->setPressIco(":/images/zb_sy_2.png");
	but_M1_A8->setPressIco(":/images/zb_xf_2.png");	
	but_M1_B1->setPressIco(":/images/db_sy_2.png");
	but_M1_B2->setPressIco(":/images/db_xf_2.png");
	but_M1_B3->setPressIco(":/images/db_zx_2.png");
	but_M1_B4->setPressIco(":/images/db_yx_2.png");
	but_M1_B5->setPressIco(":/images/sz_close_2.png");
	but_M1_B6->setPressIco(":/images/sz_open_2.png");
	but_M1_B7->setPressIco(":/images/sz_right_2.png");
	but_M1_B8->setPressIco(":/images/sz_left_2.png");
	
	but_M1_A1->setReleaseIco(":/images/xb_sy_1.png");
	but_M1_A2->setReleaseIco(":/images/xb_xf_1.png");
	but_M1_A3->setReleaseIco(":/images/sw_sy_1.png");
	but_M1_A4->setReleaseIco(":/images/sw_xf_1.png");
	but_M1_A5->setReleaseIco(":/images/xj_sy_1.png");
	but_M1_A6->setReleaseIco(":/images/xj_xf_1.png");
	but_M1_A7->setReleaseIco(":/images/zb_sy_1.png");
	but_M1_A8->setReleaseIco(":/images/zb_xf_1.png");	
	but_M1_B1->setReleaseIco(":/images/db_sy_1.png");
	but_M1_B2->setReleaseIco(":/images/db_xf_1.png");
	but_M1_B3->setReleaseIco(":/images/db_zx_1.png");
	but_M1_B4->setReleaseIco(":/images/db_yx_1.png");	
	but_M1_B5->setReleaseIco(":/images/sz_close_1.png");
	but_M1_B6->setReleaseIco(":/images/sz_open_1.png");
	but_M1_B7->setReleaseIco(":/images/sz_right_1.png");
	but_M1_B8->setReleaseIco(":/images/sz_left_1.png");
		
	but_M2_A1->setPressIco(":/images/zb_tq_2.png");
	but_M2_A2->setPressIco(":/images/zb_zd_2.png");
	but_M2_A3->setPressIco(":/images/zb_sp_2.png");
	but_M2_A4->setPressIco(":/images/zb_sq_2.png");
	but_M2_A5->setPressIco(":/images/zb_wz_2.png");
	but_M2_A6->setPressIco(":/images/sb_qg_2.png");
	but_M2_A7->setPressIco(":/images/zbqh_2.png");
	but_M2_A8->setPressIco(":/images/yuliu_2.png");
	but_M2_B1->setPressIco(":/images/sb_qz_2.png");
	but_M2_B2->setPressIco(":/images/sb_sq_2.png");
	but_M2_B3->setPressIco(":/images/sb_qs_2.png");
	but_M2_B4->setPressIco(":/images/sb_bz_2.png");

	
	but_M2_A1->setReleaseIco(":/images/zb_tq_1.png");
	but_M2_A2->setReleaseIco(":/images/zb_zd_1.png");
	but_M2_A3->setReleaseIco(":/images/zb_sp_1.png");
	but_M2_A4->setReleaseIco(":/images/zb_sq_1.png");
	but_M2_A5->setReleaseIco(":/images/zb_wz_1.png");
	but_M2_A6->setReleaseIco(":/images/sb_qg_1.png");
	but_M2_A7->setReleaseIco(":/images/zbqh_1.png");
	but_M2_A8->setReleaseIco(":/images/yuliu_1.png");
	but_M2_B1->setReleaseIco(":/images/sb_qz_1.png");
	but_M2_B2->setReleaseIco(":/images/sb_sq_1.png");
	but_M2_B3->setReleaseIco(":/images/sb_qs_1.png");
	but_M2_B4->setReleaseIco(":/images/sb_bz_1.png");

	
	
	but_M3_A1->setReleaseIco(":/images/jj_ld_1.png");
	but_M3_A2->setReleaseIco(":/images/jj_sx_1.png");
	but_M3_A3->setReleaseIco(":/images/zm_1.png");
	but_M3_A4->setReleaseIco(":/images/yuliu_1.png");
	but_M3_A5->setReleaseIco(":/images/yuliu_1.png");
	but_M3_A6->setReleaseIco(":/images/yuliu_1.png");
	but_M3_A7->setReleaseIco(":/images/yuliu_1.png");
	but_M3_A8->setReleaseIco(":/images/yuliu_1.png");
	but_M3_B1->setReleaseIco(":/images/ch1_1.png");
	but_M3_B2->setReleaseIco(":/images/ch3_1.png");
	but_M3_B3->setReleaseIco(":/images/ch2_1.png");
	but_M3_B4->setReleaseIco(":/images/ch4_1.png");
	but_M3_B5->setReleaseIco(":/images/ch_1.png");
	but_M3_B6->setReleaseIco(":/images/yuliu_1.png");
	but_M3_B7->setReleaseIco(":/images/yuliu_1.png");
	but_M3_B8->setReleaseIco(":/images/yuliu_1.png");
	
	but_M3_A1->setPressIco(":/images/jj_ld_2.png");
	but_M3_A2->setPressIco(":/images/jj_sx_2.png");
	but_M3_A3->setPressIco(":/images/zm_2.png");
	but_M3_A4->setPressIco(":/images/yuliu_2.png");
	but_M3_A5->setPressIco(":/images/yuliu_2.png");
	but_M3_A6->setPressIco(":/images/yuliu_2.png");
	but_M3_A7->setPressIco(":/images/yuliu_2.png");
	but_M3_A8->setPressIco(":/images/yuliu_2.png");
	but_M3_B1->setPressIco(":/images/ch1_2.png");
	but_M3_B2->setPressIco(":/images/ch3_2.png");
	but_M3_B3->setPressIco(":/images/ch2_2.png");
	but_M3_B4->setPressIco(":/images/ch4_2.png");
	but_M3_B5->setPressIco(":/images/ch_2.png");
	but_M3_B6->setPressIco(":/images/yuliu_2.png");
	but_M3_B7->setPressIco(":/images/yuliu_2.png");
	but_M3_B8->setPressIco(":/images/yuliu_2.png");
	
	but_M1->setPressIco(":/images/M1_2.png");
	but_M2->setPressIco(":/images/M2_2.png");
	but_M3->setPressIco(":/images/M3_2.png");
	but_M4->setPressIco(":/images/M4_2.png");
	but_M5->setPressIco(":/images/M5_2.png");
	
	but_M1->setReleaseIco(":/images/M1_1.png");
	but_M2->setReleaseIco(":/images/M2_1.png");
	but_M3->setReleaseIco(":/images/M3_1.png");
	but_M4->setReleaseIco(":/images/M4_1.png");
	but_M5->setReleaseIco(":/images/M5_1.png");
	
	but_asg1->setPressIco(":/images/jb_down_2.png");
	but_asg2->setPressIco(":/images/jb_up_2.png");
	but_rsg1->setPressIco(":/images/jb_down_2.png");
	but_rsg2->setPressIco(":/images/jb_up_2.png");
	
	but_asg1->setReleaseIco(":/images/jb_down_1.png");
	but_asg2->setReleaseIco(":/images/jb_up_1.png");
	but_rsg1->setReleaseIco(":/images/jb_down_1.png");
	but_rsg2->setReleaseIco(":/images/jb_up_1.png");	
	
	but_M1->setGeometry(693*w,456*h,25*w,25*h);
	but_M2->setGeometry(693*w,484*h,25*w,25*h);
	but_M3->setGeometry(693*w,512*h,25*w,25*h);
	but_M4->setGeometry(693*w,540*h,25*w,25*h);
	but_M5->setGeometry(693*w,568*h,25*w,25*h);
	

	
	but_rsg1->setGeometry(373*w,457*h,28*w,26*h);
	but_rsg2->setGeometry(492*w,457*h,28*w,26*h);
	
	but_asg1->setGeometry(534*w,457*h,28*w,26*h);
	but_asg2->setGeometry(653*w,457*h,28*w,26*h);
	
	but_M1_A1->setGeometry(2*w,30*h,75*w,70*h);
	but_M1_A2->setGeometry(2*w,101*h,75*w,70*h);
	but_M1_A3->setGeometry(2*w,172*h,75*w,70*h);
	but_M1_A4->setGeometry(2*w,243*h,75*w,70*h);
	but_M1_A5->setGeometry(2*w,314*h,75*w,70*h);
	but_M1_A6->setGeometry(2*w,385*h,75*w,70*h);
	but_M1_A7->setGeometry(2*w,456*h,75*w,70*h);
	but_M1_A8->setGeometry(2*w,527*h,75*w,70*h);
	
	but_M1_B1->setGeometry(724*w,30*h,75*w,70*h);
	but_M1_B2->setGeometry(724*w,101*h,75*w,70*h);
	but_M1_B3->setGeometry(724*w,172*h,75*w,70*h);
	but_M1_B4->setGeometry(724*w,243*h,75*w,70*h);
	but_M1_B5->setGeometry(724*w,314*h,75*w,70*h);
	but_M1_B6->setGeometry(724*w,385*h,75*w,70*h);
	but_M1_B7->setGeometry(724*w,456*h,75*w,70*h);
	but_M1_B8->setGeometry(724*w,527*h,75*w,70*h);	
	
	
	but_M2_A1->setGeometry(2*w,30*h,75*w,70*h);
	but_M2_A2->setGeometry(2*w,101*h,75*w,70*h);
	but_M2_A3->setGeometry(2*w,172*h,75*w,70*h);
	but_M2_A4->setGeometry(2*w,243*h,75*w,70*h);
	but_M2_A5->setGeometry(2*w,314*h,75*w,70*h);
	but_M2_A6->setGeometry(2*w,385*h,75*w,70*h);
	but_M2_A7->setGeometry(2*w,456*h,75*w,70*h);
	but_M2_A8->setGeometry(2*w,527*h,75*w,70*h);
	
	but_M2_B1->setGeometry(724*w,30*h,75*w,70*h);
	but_M2_B2->setGeometry(724*w,101*h,75*w,70*h);
	but_M2_B3->setGeometry(724*w,172*h,75*w,70*h);
	but_M2_B4->setGeometry(724*w,243*h,75*w,70*h);
	
	//but_M2_B5->setGeometry(724*w,314*h,75*w,70*h);
	//but_M2_B6->setGeometry(724*w,385*h,75*w,70*h);
	//but_M2_B7->setGeometry(724*w,456*h,75*w,70*h);
	//but_M2_B8->setGeometry(724*w,527*h,75*w,70*h);
	
	but_M3_A1->setGeometry(2*w,30*h,75*w,70*h);
	but_M3_A2->setGeometry(2*w,101*h,75*w,70*h);
	but_M3_A3->setGeometry(2*w,172*h,75*w,70*h);
	but_M3_A4->setGeometry(2*w,243*h,75*w,70*h);
	but_M3_A5->setGeometry(2*w,314*h,75*w,70*h);
	but_M3_A6->setGeometry(2*w,385*h,75*w,70*h);
	but_M3_A7->setGeometry(2*w,456*h,75*w,70*h);
	but_M3_A8->setGeometry(2*w,527*h,75*w,70*h);
	
	but_M3_B1->setGeometry(724*w,30*h,75*w,70*h);
	but_M3_B2->setGeometry(724*w,101*h,75*w,70*h);
	but_M3_B3->setGeometry(724*w,172*h,75*w,70*h);
	but_M3_B4->setGeometry(724*w,243*h,75*w,70*h);
	but_M3_B5->setGeometry(724*w,314*h,75*w,70*h);
	but_M3_B6->setGeometry(724*w,385*h,75*w,70*h);
	but_M3_B7->setGeometry(724*w,456*h,75*w,70*h);
	but_M3_B8->setGeometry(724*w,527*h,75*w,70*h);	
	
	updateModel();
	mywid_2d->setGeometry(104*w,453*h,259*w,143*h);
	// no_use3d mywid->setGeometry(104*w,453*h,259*w,143*h);

	mypitch->setGeometry(476*w,494*h,102*w,102*h);
	myspeed->setGeometry(369*w,494*h,102*w,102*h);
	myroll->setGeometry(583*w,494*h,102*w,102*h);
	mysignalshow->setGeometry(635*w,5*h,70*w,21*h);
	myarms->setGeometry(563*w,456*h,84*w,22*h);
	myruns->setGeometry(402*w,456*h,84*w,22*h);
	mybattery  ->setGeometry(332*w,9*h,29*w,16*h);
	mybattery_1->setGeometry(362*w,9*h,29*w,16*h);
	mybattery_2->setGeometry(392*w,9*h,29*w,16*h);
	mybattery_3->setGeometry(422*w,9*h,29*w,16*h);
	mybattery_4->setGeometry(506*w,9*h,29*w,16*h);
	mybattery_5->setGeometry(536*w,9*h,29*w,16*h);
	label->setGeometry(6*w,6*h,180*w,21*h);
	label_4->setGeometry(715*w,6*h,111*w,21*h);
	
	//avideo->setGeometry(80*w,32*h,640*w,416*h);
	lightShow->setGeometry(575*w,8*h,20*w,17*h);
	coordShow->setGeometry(255*w,8*h,20*w,17*h);
	videoFlagShow->setGeometry(610*w,8*h,17*w,17*h);
	sizeCtr3d->setGeometry(80*w,480*h,20*w,20*h);

	but_M1->setValue(true);
	QFont ft; //���ñ�ǩ�����С
    ft.setPointSize(14*h);
    label_4->setFont(ft);
	label->setFont(ft);
	
	//mywid->dabiPitch(180);
	//mywid->xiaobiPitch(172);
	//mywid->shouwanPitch(7);

	//serialport->setPort(1);
	
}
//��ʼ���źźͲ۵Ĺ���
void Mainframe::initConnect()
{
	//connect(myctrsize, SIGNAL(sizeflagchange(int)), this, SLOT( changmodelsize(int)));
	connect(timer, SIGNAL(timeout()), this, SLOT(sendcommand())); 	
	//connect(receiveThread, SIGNAL(dataReceived(QByteArray)), this, SLOT( readyRead(QByteArray)));
	//connect(receiveThread, SIGNAL(dataReceived1(QByteArray)), this, SLOT( disposejoy(QByteArray)));
	// no_use3d connect(sizeCtr3d, SIGNAL(valueChanged(double)), mywid, SLOT( updatesize(double)));
//	connect(avideo, SIGNAL(mouseChange(int)), this, SLOT( changeVideo(int)));
	
	connect(but_M1_A1, SIGNAL(pressed()), this, SLOT( xb_fy()));//С������
	connect(but_M1_A2, SIGNAL(pressed()), this, SLOT( xb_fy()));//С���¸�
	connect(but_M1_A3, SIGNAL(pressed()), this, SLOT( sw_fy()));//��������
	connect(but_M1_A4, SIGNAL(pressed()), this, SLOT( sw_fy()));//�����¸�
	connect(but_M1_A5, SIGNAL(pressed()), this, SLOT( xj_fy()));//�������
	connect(but_M1_A6, SIGNAL(pressed()), this, SLOT( xj_fy()));//����¸�
	connect(but_M1_A7, SIGNAL(pressed()), this, SLOT( zb_fy()));//֧���¸�
	connect(but_M1_A8, SIGNAL(pressed()), this, SLOT( zb_fy()));//֧������

	connect(but_M1_B1, SIGNAL(pressed()), this, SLOT( db_fy()));//�������
	connect(but_M1_B2, SIGNAL(pressed()), this, SLOT( db_fy()));//����¸�
	connect(but_M1_B3, SIGNAL(pressed()), this, SLOT( db_xz()));//�������
	connect(but_M1_B4, SIGNAL(pressed()), this, SLOT( db_xz()));//�������
	connect(but_M1_B5, SIGNAL(pressed()), this, SLOT( sz_kh()));//��ץ���
	connect(but_M1_B6, SIGNAL(pressed()), this, SLOT( sz_kh()));//��ץ�ɿ�
	connect(but_M1_B7, SIGNAL(pressed()), this, SLOT( sz_xz()));//��ץ����
	connect(but_M1_B8, SIGNAL(pressed()), this, SLOT( sz_xz()));//��ץ����
	
	connect(but_M2_A1, SIGNAL(pressed()), this, SLOT( zb_tq()));//֧��̧��
	connect(but_M2_A2, SIGNAL(pressed()), this, SLOT( zb_zd()));//֧��֧��
	connect(but_M2_A3, SIGNAL(pressed()), this, SLOT( zb_sp()));//֧��ˮƽ
	connect(but_M2_A4, SIGNAL(pressed()), this, SLOT( zb_sq()));//֧������
	connect(but_M2_A5, SIGNAL(pressed()), this, SLOT( zb_wz()));//֧��΢֧
	connect(but_M2_A6, SIGNAL(pressed()), this, SLOT( sb_qg()));//�ֱ�ǰ��
	connect(but_M2_A7, SIGNAL(pressed()), coordShow, SLOT( changeValue()));
	connect(but_M2_A7, SIGNAL(pressed()), but_M2_A7, SLOT( setPress()));
	connect(but_M2_A7, SIGNAL(released()), but_M2_A7, SLOT( setRelease()));
	//connect(but_M2_A7, SIGNAL(pressed()), this, SLOT( xxxxxx()));
	//connect(but_M2_A8, SIGNAL(pressed()), this, SLOT( xxxxxx()));

	connect(but_M2_B1, SIGNAL(pressed()), this, SLOT( sb_qz()));//�ֱ�ȫչ
	connect(but_M2_B2, SIGNAL(pressed()), this, SLOT( sb_sq()));//�ֱ�����
	connect(but_M2_B3, SIGNAL(pressed()), this, SLOT( sb_qs()));//�ֱ�ǰ��
	connect(but_M2_B4, SIGNAL(pressed()), this, SLOT( sb_bz()));//�ֱ۰�չ
	//connect(but_M2_B5, SIGNAL(pressed()), this, SLOT( xxxxxx()));
	//connect(but_M2_B6, SIGNAL(pressed()), this, SLOT( xxxxxx()));
	//connect(but_M2_B7, SIGNAL(pressed()), this, SLOT( xxxxxx()));
	//connect(but_M2_B8, SIGNAL(pressed()), this, SLOT( xxxxxx()));
	
	
	
	
	
	connect(but_M3_A1, SIGNAL(pressed()), this, SLOT( jjChange()));//��������
	connect(but_M3_A2, SIGNAL(pressed()), this, SLOT( jjChange()));//������С
	connect(but_M3_A3, SIGNAL(pressed()), this, SLOT( zmControl()));//��������
	
	connect(but_M3_B1, SIGNAL(pressed()), this, SLOT( setCH1()));//CH1ȫ��
	connect(but_M3_B2, SIGNAL(pressed()), this, SLOT( setCH2()));//CH3ȫ��
	connect(but_M3_B3, SIGNAL(pressed()), this, SLOT( setCH3()));//CH2ȫ��
	connect(but_M3_B4, SIGNAL(pressed()), this, SLOT( setCH4()));//CH4ȫ��
	connect(but_M3_B5, SIGNAL(pressed()), this, SLOT( setCHAll()));//�ۺ���ʾ
	
	connect(but_M1, SIGNAL(pressed()), this, SLOT( setM1()));//
	connect(but_M2, SIGNAL(pressed()), this, SLOT( setM2()));//
	connect(but_M3, SIGNAL(pressed()), this, SLOT( setM3()));//
	//connect(but_M4, SIGNAL(pressed()), this, SLOT( setM4()));//
	//connect(but_M5, SIGNAL(pressed()), this, SLOT( setM5()));//
				
	connect(but_asg1, SIGNAL(pressed()), this, SLOT( asgChange()));  //�ֱ��ٶȼ����С
	connect(but_asg2, SIGNAL(pressed()), this, SLOT( asgChange()));	 //�ֱ��ٶȼ�������
	connect(but_rsg1, SIGNAL(pressed()), this, SLOT( rsgChange()));  //�г��ٶȼ����С
	connect(but_rsg2, SIGNAL(pressed()), this, SLOT( rsgChange()));  //�г��ٶȼ�������
	
	connect(but_asg1, SIGNAL(released()), this, SLOT(asgChange()));  //ȡ���ֱ��ٶȼ����С
	connect(but_asg2, SIGNAL(released()), this, SLOT(asgChange()));  //ȡ���ֱ��ٶȼ�������
	connect(but_rsg1, SIGNAL(released()), this, SLOT(rsgChange()));  //ȡ���г��ٶȼ����С
	connect(but_rsg2, SIGNAL(released()), this, SLOT(rsgChange()));  //ȡ���г��ٶȼ�������
	
	connect(but_M1_A1, SIGNAL(released()), this, SLOT( xb_fy()));
	connect(but_M1_A2, SIGNAL(released()), this, SLOT( xb_fy()));
	connect(but_M1_A3, SIGNAL(released()), this, SLOT( sw_fy()));
	connect(but_M1_A4, SIGNAL(released()), this, SLOT( sw_fy()));
	connect(but_M1_A5, SIGNAL(released()), this, SLOT( xj_fy()));
	connect(but_M1_A6, SIGNAL(released()), this, SLOT( xj_fy()));
	connect(but_M1_A7, SIGNAL(released()), this, SLOT( zb_fy()));
	connect(but_M1_A8, SIGNAL(released()), this, SLOT( zb_fy()));

	connect(but_M1_B1, SIGNAL(released()), this, SLOT( db_fy()));
	connect(but_M1_B2, SIGNAL(released()), this, SLOT( db_fy()));
	connect(but_M1_B3, SIGNAL(released()), this, SLOT( db_xz()));
	connect(but_M1_B4, SIGNAL(released()), this, SLOT( db_xz()));
	connect(but_M1_B5, SIGNAL(released()), this, SLOT( sz_kh()));
	connect(but_M1_B6, SIGNAL(released()), this, SLOT( sz_kh()));
	connect(but_M1_B7, SIGNAL(released()), this, SLOT( sz_xz()));
	connect(but_M1_B8, SIGNAL(released()), this, SLOT( sz_xz()));
	
	connect(but_M3_A1, SIGNAL(released()), this, SLOT( jjChange()));
	connect(but_M3_A2, SIGNAL(released()), this, SLOT( jjChange()));
	
}

//��������
Mainframe::~Mainframe()
{
	// no_use3d delete mywid;
	//delete mycompass;
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

	//receiveThread->exit() ;
	//delete receiveThread;  
   // receiveThread = NULL;
    delete [] backdata;
    delete [] commanddata;
    delete [] backjoy;
}


void Mainframe::changeVideo(int ch)//�л���Ƶ
{
	switch(ch)
	{
		case 0:
			setCHAll();
			break;
		case 1:
			setCH1();
			break;
		case 2:
			setCH3();
			break;
		case 3:
			setCH2();
			break;
		case 4:
			setCH4();
			break;

	}
}
void Mainframe::updateModel()  //����ģʽ
{
	switch(modelflag)
	{
		case 0:
			//��ʾģʽ1�ϵ����а�ť
			but_M1_A1->show();
			but_M1_A2->show();
			but_M1_A3->show();
			but_M1_A4->show();
			but_M1_A5->show();
			but_M1_A6->show();
			but_M1_A7->show();
			but_M1_A8->show();
			but_M1_B1->show();
			but_M1_B2->show();
			but_M1_B3->show();
			but_M1_B4->show();
			but_M1_B5->show();
			but_M1_B6->show();
			but_M1_B7->show();
			but_M1_B8->show();
			//����������ť
			but_M2_A1->hide();
			but_M2_A2->hide();
			but_M2_A3->hide();
			but_M2_A4->hide();
			but_M2_A5->hide();
			but_M2_A6->hide();
			but_M2_A7->hide();
			but_M2_A8->hide();
			but_M2_B1->hide();
			but_M2_B2->hide();
			but_M2_B3->hide();
			but_M2_B4->hide();
			//but_M2_B5->hide();
			//but_M2_B6->hide();
			//but_M2_B7->hide();
			//but_M2_B8->hide();
	
			but_M3_A1->hide();
			but_M3_A2->hide();
			but_M3_A3->hide();
			but_M3_A4->hide();
			but_M3_A5->hide();
			but_M3_A6->hide();
			but_M3_A7->hide();
			but_M3_A8->hide();
			but_M3_B1->hide();
			but_M3_B2->hide();
			but_M3_B3->hide();
			but_M3_B4->hide();
			but_M3_B5->hide();
			but_M3_B6->hide();
			but_M3_B7->hide();
			but_M3_B8->hide();
			commanddata[8]&=0xf0;//����ֱ�ӿ���ģʽ
			commanddata[3]&=0xf8;	   //״̬λ��0
			commanddata[5]&=0xf8;	   //״̬λ��0
			but_M2_A1->resetValue();
			but_M2_A2->resetValue();
			but_M2_A3->resetValue();
			but_M2_A4->resetValue();
			but_M2_A5->resetValue();
			but_M2_A6->resetValue();
			but_M2_A7->resetValue();
			but_M2_A8->resetValue();
			
			but_M2_B1->resetValue();
			but_M2_B2->resetValue();
			but_M2_B3->resetValue();
			but_M2_B4->resetValue();
			label->setText("M1:���ؽڿ���ģʽ");

			//update();
			break;
		case 1:
			//��ʾģʽ2�ϵ����а�ť
			but_M2_A1->show();
			but_M2_A2->show();
			but_M2_A3->show();
			but_M2_A4->show();
			but_M2_A5->show();
			but_M2_A6->show();
			but_M2_A7->show();
			but_M2_A8->show();
			but_M2_B1->show();
			but_M2_B2->show();
			but_M2_B3->show();
			but_M2_B4->show();
			
			but_M1_B5->show();
			but_M1_B6->show();
			but_M1_B7->show();
			but_M1_B8->show();			
			
			//but_M2_B5->show();
			//but_M2_B6->show();
			//but_M2_B7->show();
			//but_M2_B8->show();
			//����������ť
			but_M1_A1->hide();
			but_M1_A2->hide();
			but_M1_A3->hide();
			but_M1_A4->hide();
			but_M1_A5->hide();
			but_M1_A6->hide();
			but_M1_A7->hide();
			but_M1_A8->hide();
			but_M1_B1->hide();
			but_M1_B2->hide();
			but_M1_B3->hide();
			but_M1_B4->hide();
			//but_M1_B5->hide();
			//but_M1_B6->hide();
			//but_M1_B7->hide();
			//but_M1_B8->hide();
	
			but_M3_A1->hide();
			but_M3_A2->hide();
			but_M3_A3->hide();
			but_M3_A4->hide();
			but_M3_A5->hide();
			but_M3_A6->hide();
			but_M3_A7->hide();
			but_M3_A8->hide();
			but_M3_B1->hide();
			but_M3_B2->hide();
			but_M3_B3->hide();
			but_M3_B4->hide();
			but_M3_B5->hide();
			but_M3_B6->hide();
			but_M3_B7->hide();
			but_M3_B8->hide();
			label->setText("M2:Ԥ��λģʽ");
			//update();
			break;
		case 2:
			//��ʾģʽ3�ϵ����а�ť
			but_M3_A1->show();
			but_M3_A2->show();
			but_M3_A3->show();
			but_M3_A4->show();
			but_M3_A5->show();
			but_M3_A6->show();
			but_M3_A7->show();
			but_M3_A8->show();
			but_M3_B1->show();
			but_M3_B2->show();
			but_M3_B3->show();
			but_M3_B4->show();
			but_M3_B5->show();
			but_M3_B6->show();
			but_M3_B7->show();
			but_M3_B8->show();
			//����������ť
			but_M2_A1->hide();
			but_M2_A2->hide();
			but_M2_A3->hide();
			but_M2_A4->hide();
			but_M2_A5->hide();
			but_M2_A6->hide();
			but_M2_A7->hide();
			but_M2_A8->hide();
			but_M2_B1->hide();
			but_M2_B2->hide();
			but_M2_B3->hide();
			but_M2_B4->hide();
			//but_M2_B5->hide();
			//but_M2_B6->hide();
			//but_M2_B7->hide();
			//but_M2_B8->hide();
	
			but_M1_A1->hide();
			but_M1_A2->hide();
			but_M1_A3->hide();
			but_M1_A4->hide();
			but_M1_A5->hide();
			but_M1_A6->hide();
			but_M1_A7->hide();
			but_M1_A8->hide();
			but_M1_B1->hide();
			but_M1_B2->hide();
			but_M1_B3->hide();
			but_M1_B4->hide();
			but_M1_B5->hide();
			but_M1_B6->hide();
			but_M1_B7->hide();
			but_M1_B8->hide();
			label->setText("M3:����ͷ����ģʽ");
			//update();
			break;
		case 3:
			label->setText("M4:��ͼ��ʾģʽ");
			//update();
			break;
		case 4:
			label->setText("M5:�ۺϿ���ģʽ");
			//update();
			break;
	}
}
//��ť��Ӧ�ۺ���
void Mainframe::setM1()//����Ϊģʽ1
{
	but_M1->setValue(true);
	but_M2->resetValue();
	but_M3->resetValue();
	but_M4->resetValue();
	but_M5->resetValue();
	modelflag=0;
	updateModel();
}
void Mainframe::setM2()//����Ϊģʽ2
{
	but_M2->setValue(true);
	but_M1->resetValue();
	but_M3->resetValue();
	but_M4->resetValue();
	but_M5->resetValue();
	modelflag=1;
	updateModel();
}
void Mainframe::setM3()//����Ϊģʽ3
{
	but_M3->setValue(true);
	but_M1->resetValue();
	but_M2->resetValue();
	but_M4->resetValue();
	but_M5->resetValue();
	modelflag=2;
	updateModel();	
}
void Mainframe::setM4()//����Ϊģʽ4
{
	but_M4->setValue(true);
	but_M1->resetValue();
	but_M2->resetValue();
	but_M3->resetValue();
	but_M5->resetValue();
	modelflag=3;
	updateModel();
}
void Mainframe::setM5()//����Ϊģʽ5
{
	but_M5->setValue(true);
	but_M1->resetValue();
	but_M2->resetValue();
	but_M3->resetValue();
	but_M4->resetValue();
	modelflag=4;
	updateModel();
}

void Mainframe::xbUp()//С������
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[4]&=0x7f;//BIT7��0
	commanddata[4]&=0x8f;//BIT 4 5 6 λ��0
	commanddata[4]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ�
	but_M1_A1->setValue(true);
}
void Mainframe::xbDown()//С���¸�
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[4]|=0x80;//BIT7��1
	commanddata[4]&=0x8f;//BIT 4 5 6 λ��0
	commanddata[4]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ�
	but_M1_A2->setValue(true);
}
void Mainframe::swUp()//��������
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[4]&=0xf7;//BIT3��0 
	commanddata[4]&=0xf8;//ǰ��λ��0
	commanddata[4]|=((char)(myarms->value())); //BIT 0 1 2 λ���ٶ�
	but_M1_A3->setValue(true);	
}
void Mainframe::swDown()//�����¸�
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[4]|=0x08;//BIT3��1
	commanddata[4]&=0xf8;//ǰ��λ��0
	commanddata[4]|=((char)(myarms->value())); //BIT 0 1 2 λ���ٶ�
	but_M1_A4->setValue(true);
}
void Mainframe::xjUp()//�������
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[8]&=0x3f;//BIT7 6 ��0 0
	commanddata[8]|=0x80;//BIT7 6 ��1 0
	but_M1_A5->setValue(true);
}
void Mainframe::xjDown()//����¸�
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[8]&=0x3f;//BIT7 6 ��0 0
	commanddata[8]|=0x40;//BIT7 6 ��1 0
	but_M1_A6->setValue(true);	
}
void Mainframe::zbDown()//֧���¸�
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[5]|=0x08;//BIT3��1
	commanddata[5]&=0xf8;//ǰ��λ��0
	commanddata[5]|=((char)myarms->value()); //BIT 0 1 2 λ���ٶ�	
	but_M1_A7->setValue(true);	
}
void Mainframe::zbUp()//֧������
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[5]&=0xf7;//BIT3��0
	commanddata[5]&=0xf8;//ǰ��λ��0
	commanddata[5]|=((char)myarms->value()); //BIT 0 1 2 λ���ٶ�
	but_M1_A8->setValue(true);		
}
		
void Mainframe::dbUp()//�������
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[3]&=0xf7;//BIT3��0
	commanddata[3]&=0xf8;//ǰ��λ��0
	commanddata[3]|=((char)myarms->value()); //BIT 0 1 2 λ���ٶ�	
	but_M1_B1->setValue(true);	
}
void Mainframe::dbDown()//����¸�
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[3]|=0x08;//BIT3��1
	commanddata[3]&=0xf8;//ǰ��λ��0
	commanddata[3]|=((char)myarms->value()); //BIT 0 1 2 λ���ٶ�	
	but_M1_B2->setValue(true);
}
void Mainframe::dbleft()//�������
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[3]|=0x80;//BIT7��1
	commanddata[3]&=0x8f;//BIT 4 5 6 λ��0
	commanddata[3]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
	but_M1_B3->setValue(true);
}
void Mainframe::dbright()//�������
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[3]&=0x7f;//BIT7��0
	commanddata[3]&=0x8f;//BIT 4 5 6 λ��0
	commanddata[3]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
	but_M1_B4->setValue(true);
}
void Mainframe::szClose()//��ץ���
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[7]|=0x80;//BIT7��1
	commanddata[7]&=0x8f;//BIT 4 5 6 λ��0
	commanddata[7]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ� 
	but_M1_B5->setValue(true);
}
void Mainframe::szOpen()//��ץ�ɿ�
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[7]&=0x7f;//BIT7��0
	commanddata[7]&=0x8f;//BIT 4 5 6 λ��0
	commanddata[7]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ�
	but_M1_B6->setValue(true);
}
void Mainframe::szright()//��ץ����
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[5]|=0x80;//BIT7��1
	commanddata[5]&=0x8f;//BIT 4 5 6 λ��0
	commanddata[5]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ�
	but_M1_B7->setValue(true);
}
void Mainframe::szleft()//��ץ����
{
	if(commanddata[8]&0x0e)//�������ģʽ�����£����˳�
		return;
	commanddata[5]&=0x7f;//BIT7��0
	commanddata[5]&=0x8f;//BIT 4 5 6 λ��0
	commanddata[5]|=(((char)(myarms->value())<<4)); //BIT 4 5 6 λ���ٶ�
	but_M1_B8->setValue(true);
}
	
void Mainframe::zb_tq()//֧��̧��
{
	commanddata[3]&=0xf8;	   
	commanddata[8]&=0xf0;	   //��־��Ϊֱ�ӿ���								
	if((commanddata[5]&0x07)==0x01)//�жϸ�״̬�Ƿ�����
	{
		commanddata[5]&=0xf8;	   //״̬λ��0
		but_M2_A1->resetValue();
	}
	else//��״̬û����
	{
		commanddata[8]|=0x08;
		commanddata[5]&=0xf8;	   //״̬λ��0
		commanddata[5]|=0x01;
		but_M2_A1->setValue(true);
		but_M2_A2->resetValue();
		but_M2_A3->resetValue();
		but_M2_A4->resetValue();
		but_M2_A5->resetValue();
		but_M2_A6->resetValue();
		but_M2_B1->resetValue();
		but_M2_B2->resetValue();
		but_M2_B3->resetValue();
		but_M2_B4->resetValue();
	}		
}
void Mainframe::zb_zd()//֧��֧��
{
	commanddata[3]&=0xf8;	   //״̬λ��0	
	commanddata[8]&=0xf0;	   //��־��Ϊֱ�ӿ���						
	if((commanddata[5]&0x07)==0x02)//�жϸ�״̬�Ƿ�����
	{
		commanddata[5]&=0xf8;	   //״̬λ��0
		but_M2_A2->resetValue();
	}		   
	else//��״̬û����
	{
		commanddata[8]|=0x08;
		commanddata[5]&=0xf8;	   //״̬λ��0
		commanddata[5]|=0x02;
		but_M2_A1->resetValue();
		but_M2_A2->setValue(true);
		but_M2_A3->resetValue();
		but_M2_A4->resetValue();
		but_M2_A5->resetValue();
		but_M2_A6->resetValue();
		but_M2_B1->resetValue();
		but_M2_B2->resetValue();
		but_M2_B3->resetValue();
		but_M2_B4->resetValue();
	}					
}
void Mainframe::zb_sp()//֧��ˮƽ
{
	commanddata[3]&=0xf8;	   //״̬λ��0	
	commanddata[8]&=0xf0;	   //��־��Ϊֱ�ӿ���						
	if((commanddata[5]&0x07)==0x04)//�жϸ�״̬�Ƿ�����
	{
		commanddata[5]&=0xf8;	   //״̬λ��0
		but_M2_A3->resetValue();
	}		   
	else//��״̬û����
	{
		commanddata[8]|=0x08;
		commanddata[5]&=0xf8;	   //״̬λ��0
		commanddata[5]|=0x04;
		but_M2_A1->resetValue();
		but_M2_A2->resetValue();
		but_M2_A3->setValue(true);
		but_M2_A4->resetValue();
		but_M2_A5->resetValue();
		but_M2_A6->resetValue();
		but_M2_B1->resetValue();
		but_M2_B2->resetValue();
		but_M2_B3->resetValue();
		but_M2_B4->resetValue();
	}	
}
void Mainframe::zb_sq()//֧������
{
	commanddata[3]&=0xf8;	   //״̬λ��0	
	commanddata[8]&=0xf0;	   //��־��Ϊֱ�ӿ���						
	if((commanddata[5]&0x07)==0x03)//�жϸ�״̬�Ƿ�����
	{
		commanddata[5]&=0xf8;	   //״̬λ��0
		but_M2_A4->resetValue();
	}		   
	else//��״̬û����
	{
		commanddata[8]|=0x08;
		commanddata[5]&=0xf8;	   
		commanddata[5]|=0x03;
		but_M2_A1->resetValue();
		but_M2_A2->resetValue();
		but_M2_A3->resetValue();
		but_M2_A4->setValue(true);
		but_M2_A5->resetValue();
		but_M2_A6->resetValue();
		but_M2_B1->resetValue();
		but_M2_B2->resetValue();
		but_M2_B3->resetValue();
		but_M2_B4->resetValue();
	}	
}
void Mainframe::zb_wz()//֧��΢֧
{
	commanddata[3]&=0xf8;	   //״̬λ��0	
	commanddata[8]&=0xf0;	   //��־��Ϊֱ�ӿ���						
	if((commanddata[5]&0x07)==0x05)//�жϸ�״̬�Ƿ�����
	{
		commanddata[5]&=0xf8;	   //״̬λ��0
		but_M2_A5->resetValue();
	}		   
	else//��״̬û����
	{
		commanddata[8]|=0x08;
		commanddata[5]&=0xf8;	   
		commanddata[5]|=0x05;
		but_M2_A1->resetValue();
		but_M2_A2->resetValue();
		but_M2_A3->resetValue();
		but_M2_A4->resetValue();
		but_M2_A5->setValue(true);
		but_M2_A6->resetValue();
		but_M2_B1->resetValue();
		but_M2_B2->resetValue();
		but_M2_B3->resetValue();
		but_M2_B4->resetValue();
	}	
}
void Mainframe::sb_qg()//�ֱ�ǰ��
{
	commanddata[4]&=0xf8;//ǰ��λ��0
	if((commanddata[3]&0x07)==0x04)//�жϸ�״̬�Ƿ�����
	{
		commanddata[8]&=0xf0; //��־��Ϊֱ�ӿ���
		commanddata[3]&=0xf8; //״̬λ��0
		commanddata[5]&=0xf8; //״̬λ��0
		but_M2_A6->resetValue();
	}
	else//��״̬û����
	{
		commanddata[8]|=0x0c;
		commanddata[3]&=0xf8; //״̬λ��0
		commanddata[3]|=0x04; //��ץǰ�۲�
		commanddata[5]&=0xf8; //״̬λ��0
		but_M2_A1->resetValue();
		but_M2_A2->resetValue();
		but_M2_A3->resetValue();
		but_M2_A4->resetValue();
		but_M2_A5->resetValue();
		but_M2_A6->setValue(true);
		but_M2_B1->resetValue();
		but_M2_B2->resetValue();
		but_M2_B3->resetValue();
		but_M2_B4->resetValue();
	}	
}


void Mainframe::sb_qz()//�ֱ�ȫչ
{
	commanddata[4]&=0xf8;//ǰ��λ��0
	if((commanddata[3]&0x07)==0x05)//�жϸ�״̬�Ƿ�����
	{
		commanddata[8]&=0xf0; //��־��Ϊֱ�ӿ���
		commanddata[3]&=0xf8; //״̬λ��0
		commanddata[5]&=0xf8; //״̬λ��0
		but_M2_B1->resetValue();
	}
	else//��״̬û����
	{
		commanddata[8]|=0x0c;
		commanddata[3]&=0xf8; //״̬λ��0
		commanddata[3]|=0x05; //��ץȫչ��
		commanddata[5]&=0xf8; //״̬λ��0
		commanddata[5]|=0x05;
		but_M2_A1->resetValue();
		but_M2_A2->resetValue();
		but_M2_A3->resetValue();
		but_M2_A4->resetValue();
		but_M2_A5->resetValue();
		but_M2_A6->resetValue();
		but_M2_B1->setValue(true);
		but_M2_B2->resetValue();
		but_M2_B3->resetValue();
		but_M2_B4->resetValue();
	}
	
}
void Mainframe::sb_sq()//�ֱ�����
{
	commanddata[4]&=0xf8;//ǰ��λ��0
	if((commanddata[3]&0x07)==0x03)//�жϸ�״̬�Ƿ�����
	{
		commanddata[8]&=0xf0; //��־��Ϊֱ�ӿ���
		commanddata[3]&=0xf8; //״̬λ��0
		commanddata[5]&=0xf8; //״̬λ��0
		but_M2_B2->resetValue();
	}
	else//��״̬û����
	{
		commanddata[8]|=0x0c;
		commanddata[3]&=0xf8; //״̬λ��0
		commanddata[3]|=0x03; //��ץ����
		commanddata[5]&=0xf8; //״̬λ��0
		commanddata[5]|=0x03; 
		but_M2_A1->resetValue();
		but_M2_A2->resetValue();
		but_M2_A3->resetValue();
		but_M2_A4->resetValue();
		but_M2_A5->resetValue();
		but_M2_A6->resetValue();
		but_M2_B1->resetValue();
		but_M2_B2->setValue(true);
		but_M2_B3->resetValue();
		but_M2_B4->resetValue();
	}	
}
void Mainframe::sb_qs()//�ֱ�ǰ��
{
	commanddata[4]&=0xf8;//ǰ��λ��0
	if((commanddata[3]&0x07)==0x02)//�жϸ�״̬�Ƿ�����
	{
		commanddata[8]&=0xf0; //��־��Ϊֱ�ӿ���
		commanddata[3]&=0xf8; //״̬λ��0
		commanddata[5]&=0xf8; //״̬λ��0
		but_M2_B3->resetValue();
	}
	else//��״̬û����
	{
		commanddata[8]|=0x0c;
		commanddata[3]&=0xf8; //״̬λ��0
		commanddata[3]|=0x02; //��ץǰץȡ
		commanddata[5]&=0xf8; //״̬λ��0
		commanddata[5]|=0x05;
		but_M2_A1->resetValue();
		but_M2_A2->resetValue();
		but_M2_A3->resetValue();
		but_M2_A4->resetValue();
		but_M2_A5->resetValue();
		but_M2_A6->resetValue();
		but_M2_B1->resetValue();
		but_M2_B2->resetValue();
		but_M2_B3->setValue(true);
		but_M2_B4->resetValue();
	}	
}
void Mainframe::sb_bz()//�ֱ۰�չ
{
	commanddata[4]&=0xf8;//ǰ��λ��0
	if((commanddata[3]&0x07)==0x01)//�жϸ�״̬�Ƿ�����
	{
		commanddata[8]&=0xf0; //��־��Ϊֱ�ӿ���
		commanddata[3]&=0xf8; //״̬λ��0
		commanddata[5]&=0xf8; //״̬λ��0
		but_M2_B4->resetValue();
	}
	else//��״̬û����
	{
		commanddata[8]|=0x0c;
		commanddata[3]&=0xf8; //״̬λ��0
		commanddata[3]|=0x01; //��ץ��չ��
		commanddata[5]&=0xf8; //״̬λ��0
		commanddata[5]|=0x05;
		but_M2_A1->resetValue();
		but_M2_A2->resetValue();
		but_M2_A3->resetValue();
		but_M2_A4->resetValue();
		but_M2_A5->resetValue();
		but_M2_A6->resetValue();
		but_M2_B1->resetValue();
		but_M2_B2->resetValue();
		but_M2_B3->resetValue();
		but_M2_B4->setValue(true);
	}	
}

void Mainframe::jjUp()//��������
{
	focflag=1;
	if(myfocaldis<31)
		myfocaldis+=1;
	commanddata[10]&=0xe0;//ǰ��λ������
	commanddata[10]|=((char)myfocaldis);
	but_M3_A1->setValue(true);
}
void Mainframe::jjDown()//������С
{
	focflag=2;
	if(myfocaldis>0)
		myfocaldis-=1;
	commanddata[10]&=0xe0;//ǰ��λ������
	commanddata[10]|=(char)myfocaldis;
	but_M3_A2->setValue(true);
}

void Mainframe::zmControl()//��������
{
	if(lightShow->getValue()==false)//û���� ����
	{
		commanddata[9]|=0xe0;
		lightShow->setValue(true);
		but_M3_A3->setValue(true);
	}
	else//�Ѿ����� ���
	{
		commanddata[9]&=0x1f;
		lightShow->setValue(false);
		but_M3_A3->resetValue();
	}	
}
	
void Mainframe::setCH1()//CH1ȫ��
{
	//��̨����ͷ��ʾ
	commanddata[10]&=0x1f;
	but_M3_B1->setValue(true);
	but_M3_B2->resetValue();
	but_M3_B3->resetValue();
	but_M3_B4->resetValue();
	but_M3_B5->resetValue();
	videoFlagShow->setValue(1);
}
void Mainframe::setCH3()//CH3ȫ��
{
	//�г�����ͷ��ʾ
	commanddata[10]&=0x1f;
	commanddata[10]|=0x40;	

	
	but_M3_B1->resetValue();
	but_M3_B2->resetValue();
	but_M3_B3->setValue(true);
	but_M3_B4->resetValue();
	but_M3_B5->resetValue();	
	videoFlagShow->setValue(2);
}
void Mainframe::setCH2()//CH2ȫ��
{
	//��ץǰ������ͷ��ʾ
	commanddata[10]&=0x1f;
	commanddata[10]|=0x20;
	but_M3_B1->resetValue();
	but_M3_B2->setValue(true);
	but_M3_B3->resetValue();
	but_M3_B4->resetValue();
	but_M3_B5->resetValue();
	videoFlagShow->setValue(3);
}
void Mainframe::setCH4()//CH4ȫ��
{
	//��ץ��������ͷ��ʾ
	commanddata[10]&=0x1f;
	commanddata[10]|=0x60;
	but_M3_B1->resetValue();
	but_M3_B2->resetValue();
	but_M3_B3->resetValue();
	but_M3_B4->setValue(true);
	but_M3_B5->resetValue();
	videoFlagShow->setValue(4);
}
void Mainframe::setCHAll()//�ķ�����ʾ
{
	//����ͷ�ۺ���ʾ
	commanddata[10]&=0x1f;//����λ��0
	commanddata[10]|=0x80;
	but_M3_B1->resetValue();
	but_M3_B2->resetValue();
	but_M3_B3->resetValue();
	but_M3_B4->resetValue();
	but_M3_B5->setValue(true);
	videoFlagShow->setValue(0);
}
void Mainframe::setCHFull()//ȫ����ʾ
{
	//�ж��������Ƿ���
}
//�г��ٶȼ���ı�
void Mainframe::rsgChange()
{
	if((((backjoy[5]&0x05)==0x04)||(but_rsg2->pressedFlag))&&((backjoy[5]&0x09)==0x00)&&(!but_rsg1->pressedFlag))//j1
	{				
		runapeedflag=1;
		if((myruns->value())<7)
			myruns->setValue((myruns->value())+1);
		but_rsg2->setValue(true);
	}
	else if((((backjoy[5]&0x09)==0x08)||(but_rsg1->pressedFlag))&&((backjoy[5]&0x05)==0x00)&&(!but_rsg2->pressedFlag))//j1
	{
		runapeedflag=2;
		if((myruns->value())>1)
			myruns->setValue((myruns->value())-1);
		but_rsg1->setValue(true);
	}
	else
	{
		but_rsg1->resetValue();
		but_rsg2->resetValue();
		runapeedflag=0;
	}
}
//�ֱ��ٶȼ���ı�
void Mainframe::asgChange()
{
	if((((backjoy[5]&0x05)==0x05)||(but_asg2->pressedFlag))&&((backjoy[5]&0x09)!=0x09)&&(!but_asg1->pressedFlag))//j1
	{				
		armspeedflag=1;
		if((myarms->value())<7)
			myarms->setValue((myarms->value())+1);
		but_asg2->setValue(true);
	}
	else if((((backjoy[5]&0x09)==0x09)||(but_asg1->pressedFlag))&&((backjoy[5]&0x05)!=0x05)&&(!but_asg2->pressedFlag))//j1
	{
		armspeedflag=2;
		if((myarms->value())>1)
			myarms->setValue((myarms->value())-1);
		but_asg1->setValue(true);
	}
	else
	{
		but_asg1->resetValue();
		but_asg2->resetValue();
		armspeedflag=0;
	}
}

//С�۸���
void Mainframe::xb_fy()
{
	if((((backjoy[0]&0x01)==0x01)||(but_M1_A1->pressedFlag))&&((backjoy[0]&0x02)!=0x02)&&(!but_M1_A2->pressedFlag))
	{
		xbUp();//С������
	}
	else if((((backjoy[0]&0x02)==0x02)||(but_M1_A2->pressedFlag))&&((backjoy[0]&0x01)!=0x01)&&(!but_M1_A1->pressedFlag))
	{
		xbDown();//С���¸�
	}
	else
	{
		commanddata[4]&=0x8f;//BIT 4 5 6 λ��0
		but_M1_A1->resetValue();
		but_M1_A2->resetValue();
	}
}
//������
void Mainframe::sw_fy()
{
	if((((backjoy[0]&0x04)==0x04)||(but_M1_A3->pressedFlag))&&((backjoy[0]&0x08)!=0x08)&&(!but_M1_A4->pressedFlag))
	{
		swUp();//��������
	}
	else if((((backjoy[0]&0x08)==0x08)||(but_M1_A4->pressedFlag))&&((backjoy[0]&0x04)!=0x04)&&(!but_M1_A3->pressedFlag))
	{
		swDown();//�����¸�
	}
	else
	{
		commanddata[4]&=0xf8;//ǰ��λ��0
		but_M1_A3->resetValue();
		but_M1_A4->resetValue();
	}	
}
//�������
void Mainframe::xj_fy()
{
	if((((backjoy[0]&0x10)==0x10)||(but_M1_A5->pressedFlag))&&((backjoy[0]&0x20)!=0x20)&&(!but_M1_A6->pressedFlag))
	{
		xjUp();//�������
	}
	else if((((backjoy[0]&0x20)==0x20)||(but_M1_A6->pressedFlag))&&((backjoy[0]&0x10)!=0x10)&&(!but_M1_A5->pressedFlag))
	{
		xjDown();//����¸�
	}
	else
	{
		commanddata[8]&=0x3f;//BIT7 6 ��0 0	
		but_M1_A5->resetValue();
		but_M1_A6->resetValue();
	}	
}
//֧�۸���
void Mainframe::zb_fy()
{
	if((((backjoy[0]&0x40)==0x40)||(but_M1_A7->pressedFlag))&&((backjoy[0]&0x80)!=0x80)&&(!but_M1_A8->pressedFlag))
	{
		zbDown();//֧���¸�
	}
	else if((((backjoy[0]&0x80)==0x80)||(but_M1_A8->pressedFlag))&&((backjoy[0]&0x40)!=0x40)&&(!but_M1_A7->pressedFlag))
	{
		zbUp();//֧������
	}
	else
	{
		commanddata[5]&=0xf8;//ǰ��λ��0
		but_M1_A7->resetValue();
		but_M1_A8->resetValue();
	}	
}
//��۸���
void Mainframe::db_fy()
{
	if((((backjoy[1]&0x01)==0x01)||(but_M1_B1->pressedFlag))&&((backjoy[1]&0x02)!=0x02)&&(!but_M1_B2->pressedFlag))
	{
		dbUp();//�������
	}
	else if((((backjoy[1]&0x02)==0x02)||(but_M1_B2->pressedFlag))&&((backjoy[1]&0x01)!=0x01)&&(!but_M1_B1->pressedFlag))
	{
		dbDown();//����¸�
	}
	else
	{
		commanddata[3]&=0xf8;//ǰ��λ��0
		but_M1_B1->resetValue();
		but_M1_B2->resetValue();
	}	
}
//�����ת
void Mainframe::db_xz()
{
	if((((backjoy[1]&0x04)==0x04)||(but_M1_B3->pressedFlag))&&((backjoy[1]&0x08)!=0x08)&&(!but_M1_B4->pressedFlag))
	{
		dbleft();//�������
	}
	else if((((backjoy[1]&0x08)==0x08)||(but_M1_B4->pressedFlag))&&((backjoy[1]&0x04)!=0x04)&&(!but_M1_B3->pressedFlag))
	{
		dbright();//�������
	}
	else
	{
		commanddata[3]&=0x8f;//BIT 4 5 6 λ��0
		but_M1_B3->resetValue();
		but_M1_B4->resetValue();
	}	
}
//��ץ����
void Mainframe::sz_kh()
{
	if((((backjoy[1]&0x10)==0x10)||(but_M1_B5->pressedFlag))&&((backjoy[1]&0x20)!=0x20)&&(!but_M1_B6->pressedFlag))
	{
		szClose();//��ץ���
	}
	else if((((backjoy[1]&0x20)==0x20)||(but_M1_B6->pressedFlag))&&((backjoy[1]&0x10)!=0x10)&&(!but_M1_B5->pressedFlag))
	{
		szOpen();//��ץ�ɿ�
	}
	else
	{
		commanddata[7]&=0x8f;//BIT 4 5 6 λ��0
		but_M1_B5->resetValue();
		but_M1_B6->resetValue();
	}	
}
//��ץ��ת
void Mainframe::sz_xz()
{
	if((((backjoy[1]&0x40)==0x40)||(but_M1_B7->pressedFlag))&&((backjoy[1]&0x80)!=0x80)&&(!but_M1_B8->pressedFlag))
	{
		szright();//��ץ����
	}
	else if((((backjoy[1]&0x80)==0x80)||(but_M1_B8->pressedFlag))&&((backjoy[1]&0x40)!=0x40)&&(!but_M1_B7->pressedFlag))
	{
		szleft();//��ץ����
	}
	else
	{
		commanddata[5]&=0x8f;//BIT 4 5 6 λ��0
		but_M1_B7->resetValue();
		but_M1_B8->resetValue();
	}	
}
//����ı�
void Mainframe::jjChange()
{
	if((((backjoy[0]&0x01)==0x01)||(but_M3_A1->pressedFlag))&&((backjoy[0]&0x02)!=0x02)&&(!but_M3_A2->pressedFlag))
	{
		jjUp();//��������
	}
	else if((((backjoy[0]&0x02)==0x02)||(but_M3_A2->pressedFlag))&&((backjoy[0]&0x01)!=0x01)&&(!but_M3_A1->pressedFlag))
	{
		jjDown();//������С
	}
	else
	{
		focflag=0;
		but_M3_A1->resetValue();
		but_M3_A2->resetValue();
	}	
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
		// no_use3d mywid->updateview_y(mywid->getangle_h()-0.1);
	}
	else if(verticalflag==2)
	{
		// no_use3d mywid->updateview_y(mywid->getangle_h()+0.1);
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
			if(myfocaldis<31)
				myfocaldis+=1;
			commanddata[10]&=0xe0;//ǰ��λ������
			commanddata[10]|=(char)myfocaldis;			
			focsp=0;	
		}
		
	}
	else if(focflag==2)
	{
		focsp++;
		if(focsp==6)
		{
			if(myfocaldis>0)
				myfocaldis-=1;
			commanddata[10]&=0xe0;//ǰ��λ������
			commanddata[10]|=(char)myfocaldis;			
			focsp=0;	
		}
	}
	else
	{
		focsp=0;
	}		
	if(horizontalflag==1)
	{
		// no_use3d mywid->updateview_xz(mywid->getangle_v()+0.1);
	}
	else if(horizontalflag==2)
	{
		// no_use3d mywid->updateview_xz(mywid->getangle_v()-0.1);
	}	
	//��������
	//senddata=NULL;
	//senddata.append((char)0xa5);
	//senddata.append((char)0xa0);
	commanddata[12]=0xa5;
	commanddata[12]+=0xa0;
	for(int i=0;i<12;i++)
	{
		commanddata[12]+=commanddata[i];
	}
	//senddata.append(commanddata,13);
	
	//serialport->write(senddata);
}

//��Ӧ������
void Mainframe::disposejoy(QByteArray joy)
{
	unsigned char key_0,key_1,key_2,key_3,key_4,key_5,key_6,key_7,key_8,key_9,key_10,key_11;
	unsigned char tem=0;
	key_0=(unsigned char)joy.at(0);
	key_1=(unsigned char)joy.at(1);
	key_2=(unsigned char)joy.at(2);
	key_3=(unsigned char)joy.at(3);
	key_4=(unsigned char)joy.at(4);
	key_5=(unsigned char)joy.at(5);
	key_6=(unsigned char)joy.at(6);
	key_7=(unsigned char)joy.at(7);
	key_8=(unsigned char)joy.at(8);
	key_9=(unsigned char)joy.at(9);
	key_10=(unsigned char)joy.at(10);
	key_11=(unsigned char)joy.at(11);
	
	if((key_5&0x02)==0x02 && key_0==0 && key_1==0 && key_2==0 && key_3==0 && key_4==0)//�ı�ģʽ
	{
		if((key_5&0x01)==0x01)
		{
			if(modelflag==0)
				setM3();
			else if(modelflag==1)
				setM1();
			else if(modelflag==2)
				setM2();
		}
		else
		{
			if(modelflag==0)
				setM2();
			else if(modelflag==1)
				setM3();
			else if(modelflag==2)
				setM1();
		}
		backjoy[5]=key_5;//���ݰ�ť
	}
	else 
	{
		tem=backjoy[5];
		backjoy[5]=key_5;	
		if(key_5!=tem)
		{
			if((key_5&0x0d)!=(tem&0x0d))
			{
				if(((key_5&0x0c)==0x04)||((key_5&0x0c)==0x08)||((tem&0x0c)==0x04)||((tem&0x0c)==0x08))
				{
					if(((key_5&0x01)==0)&&((tem&0x01)==0))//shift���ϴκͱ��ζ�û����
					{
						rsgChange();
					}
					else if(((key_5&0x01)==0x01)&&((tem&0x01)==0x01))//shift���ϴκͱ��ζ�����
					{
						asgChange();
					}
					else
					{
						rsgChange();
						asgChange();
					}
				}
			}
			//if((backjoy[5]&0x10)==0x10)//g1 ������
			//{
			//}
			//if((backjoy[5]&0x20)==0x20)//g2 �������俪��
			//{
			//}
			
		}	
	}
	
	if(key_0!=backjoy[0])//key_a
	{
		tem=backjoy[0];
		backjoy[0]=key_0;
		switch(modelflag)
		{
			case 0:
				if((tem&0x03)!=(key_0&0x03))
				{
					xb_fy();
				}
				if((tem&0x0c)!=(key_0&0x0c))
				{
					sw_fy();
				}			
				if((tem&0x30)!=(key_0&0x30))
				{
					xj_fy();
				}			
				if((tem&0xc0)!=(key_0&0xc0))
				{
					zb_fy();
				}			
				break;
			case 1:
				if((key_1&0x0f)!=0)
					break;
				switch(key_0)
				{
					case 0x01:
						zb_tq();//֧��̧��
						break;
					case 0x02:
						zb_zd();//֧��֧��		
						break;				
					case 0x04:
						zb_sp();//֧��ˮƽ
						break;
					case 0x08:
						zb_sq();//֧������
						break;											
					case 0x10:
						zb_wz();//֧��΢֧
						break;
					case 0x20:
						sb_qg();//�ֱ�ǰ��
						break;
					//case 0x40:
					//case 0x80:
						//break;	
					default:
						break;											
				}
				break;
			case 2:
				if(((key_0&0x04)==0x04)&&((tem&0x04)==0x00))
					zmControl();//��������
				if((key_0&0x03)!=(tem&0x03))//���󽹾�
				{
					jjChange();
				}
				break;
		}
	}
	if(key_1!=backjoy[1])//key_b
	{
		tem=backjoy[1];
		backjoy[1]=key_1;
		switch(modelflag)
		{
			case 0:
				if((tem&0x03)!=(key_1&0x03))
				{
					db_fy();
				}
				if((tem&0x0c)!=(key_1&0x0c))
				{
					db_xz();
				}			
				if((tem&0x30)!=(key_1&0x30))
				{
					sz_kh();
				}			
				if((tem&0xc0)!=(key_1&0xc0))
				{
					sz_xz();
				}
				break;
			case 1:
				switch(key_1)
				{
					case 0x01:
						 sb_qz();//�ֱ�ȫչ
						break;
					case 0x02:
						sb_sq();//�ֱ�����
						break;
					case 0x04:
						sb_qs();//�ֱ�ǰ��
						break;
					case 0x08:
						sb_bz();//�ֱ۰�չ
						break;
					default:
						commanddata[4]&=0xf8;//ǰ��λ��0
						break;
				}
				if((tem&0x30)!=(key_1&0x30))
				{
					sz_kh();
				}			
				if((tem&0xc0)!=(key_1&0xc0))
				{
					sz_xz();
				}																					
				break;
			case 2:
				switch(key_1)
				{
					case 0x01://��̨����ͷ��ʾ
						setCH1();//CH1ȫ��
						break;
					case 0x02://�г�����ͷ��ʾ
						setCH2();//CH3ȫ��
						break;
					case 0x04://��ץǰ������ͷ��ʾ
						setCH3();//CH2ȫ��
						break;	
					case 0x08://��ץ��������ͷ��ʾ
						setCH4();//CH4ȫ��
						break;		
					case 0x10://����ͷ�ۺ���ʾ
						setCHAll();//�ۺ���ʾ
						break;	
				}			
				break;
			}
	}	

	if(key_2!=backjoy[2])//key_e 
	{
		tem=backjoy[2];
		backjoy[2]=key_2;
		if((key_5&0x01)==0x01)//shift������
		{	
			if((commanddata[3]&0x07)==0x06||(commanddata[3]&0x07)==0x07)//�������3Dģʽ��
			{
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[8]&=0xf0;
				commanddata[3]&=0xf8;	   //״̬λ��0 ȡ��3Dģʽ
			}
			if((key_2&0x01)==0x01)//��̨����ͷ��ʾ
			{
				setCH1();//CH1ȫ��
			}
			if((key_2&0x02)==0x02)//�г�����ͷ��ʾ
			{
				setCH3();//CH3ȫ��	
			}
			if((key_2&0x04)==0x04)//��ץǰ������ͷ��ʾ
			{
				setCH2();//CH2ȫ��
			}
			if((key_2&0x08)==0x08)//��ץ��������ͷ��ʾ
			{
				setCH4();//CH4ȫ��
			}
			if((key_2&0x10)==0x10)//�ķ�����ʾ��������ͷ		
			{
				setCHAll();//�ۺ���ʾ
			}			
		}
		else//shift��û����
		{
			if((key_2&0x0f)==0x01&&(backjoy[0]==0)&&(backjoy[1]==0)&&((key_3&0x03)==0))//Y��ǰ
			{
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	//״̬λ��0
				if(coordShow->getValue())
					commanddata[3]|=0x07;	//3dģʽ�������
				else
					commanddata[3]|=0x06;	//3dģʽ�ѿ�����	
				commanddata[4]&=0xf8;//ǰ��λ��0
				commanddata[6]&=0xf7;//BIT3��0
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[6]|=((char)myarms->value());//���ٶ�λ      //BIT 0 1 2 λ���ٶ�
				but_M2_A1->resetValue();
				but_M2_A2->resetValue();
				but_M2_A3->resetValue();
				but_M2_A4->resetValue();
				but_M2_A5->resetValue();
				but_M2_A6->resetValue();
				but_M2_B1->resetValue();
				but_M2_B2->resetValue();
				but_M2_B3->resetValue();
				but_M2_B4->resetValue();
			}
			else if((key_2&0x0f)==0x02&&(backjoy[0]==0)&&(backjoy[1]==0)&&((key_3&0x03)==0))//Y���
			{
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	//״̬λ��0
				if(coordShow->getValue())
					commanddata[3]|=0x07;	//3dģʽ�������
				else
					commanddata[3]|=0x06;	//3dģʽ�ѿ�����		
				commanddata[4]&=0xf8;//ǰ��λ��0			
				commanddata[6]|=0x08;//BIT3��1
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[6]|=(char)myarms->value();//���ٶ�λ      //BIT 4 5 6 λ���ٶ�	
				but_M2_A1->resetValue();
				but_M2_A2->resetValue();
				but_M2_A3->resetValue();
				but_M2_A4->resetValue();
				but_M2_A5->resetValue();
				but_M2_A6->resetValue();
				but_M2_B1->resetValue();
				but_M2_B2->resetValue();
				but_M2_B3->resetValue();
				but_M2_B4->resetValue();
			}
			else if((key_2&0x0f)==0x04&&(backjoy[0]==0)&&(backjoy[1]==0)&&((key_3&0x03)==0))//X����
			{
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	//״̬λ��0
				if(coordShow->getValue())
					commanddata[3]|=0x07;	//3dģʽ�������
				else
					commanddata[3]|=0x06;	//3dģʽ�ѿ�����	
				commanddata[4]&=0xf8;//ǰ��λ��0
				commanddata[6]|=0x80;//BIT7��1
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[6]|=((char)myarms->value()<<4);//���ٶ�λ      //BIT 0 1 2 λ���ٶ�
				but_M2_A1->resetValue();
				but_M2_A2->resetValue();
				but_M2_A3->resetValue();
				but_M2_A4->resetValue();
				but_M2_A5->resetValue();
				but_M2_A6->resetValue();
				but_M2_B1->resetValue();
				but_M2_B2->resetValue();
				but_M2_B3->resetValue();
				but_M2_B4->resetValue();
			}
			else if((key_2&0x0f)==0x08&&(backjoy[0]==0)&&(backjoy[1]==0)&&((key_3&0x03)==0))//X����
			{
				
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	//״̬λ��0
				if(coordShow->getValue())
					commanddata[3]|=0x07;	//3dģʽ�������
				else
					commanddata[3]|=0x06;	//3dģʽ�ѿ�����	
				commanddata[4]&=0xf8;//ǰ��λ��0				
				commanddata[6]&=0x7f;//BIT7��0
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[6]|=((char)myarms->value()<<4);//���ٶ�λ      //BIT 4 5 6 λ���ٶ�
				but_M2_A1->resetValue();
				but_M2_A2->resetValue();
				but_M2_A3->resetValue();
				but_M2_A4->resetValue();
				but_M2_A5->resetValue();
				but_M2_A6->resetValue();
				but_M2_B1->resetValue();
				but_M2_B2->resetValue();
				but_M2_B3->resetValue();
				but_M2_B4->resetValue();
			}
			else
			{
				if((commanddata[3]&0x07)==0x06||(commanddata[3]&0x07)==0x07)//�������3Dģʽ��
				{
					commanddata[4]&=0xf8;//ǰ��λ��0
					commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
					commanddata[8]&=0xf0;
					commanddata[3]&=0xf8;	   //״̬λ��0 ȡ��3Dģʽ
				}
				if(hide_flag&&key_2==0x10&&videoflag==false)//3D��2D�л�
				{
					
					// no_use3d mywid->setGeometry(104*w,453*h,259*w,143*h);
					mywid_2d->setDis(false);
					hide_flag=false;
				}
				else if(key_2==0x10&&videoflag==false)
				{
					// no_use3d mywid->setGeometry(104*w,653*h,259*w,143*h);
					mywid_2d->setDis(true);
					
					hide_flag=true;
				}
			}			
		}
	}

	if(key_3!=backjoy[3])//key_f
	{
		tem=backjoy[3];
		backjoy[3]=key_3;
		if((key_5&0x01)==0x01)//shift������
		{
			if((commanddata[3]&0x07)==0x06||(commanddata[3]&0x07)==0x07)//�������3Dģʽ��
			{
				commanddata[8]&=0xf0;
				commanddata[3]&=0xf8;	    //״̬λ��0 ȡ��3Dģʽ
				commanddata[4]&=0xf8;		//ǰ��λ��0
			}
			if((key_3&0x03)==0x01)
			{
				verticalflag=1;				
			}
			else if((key_3&0x03)==0x02)
			{
				verticalflag=2;
			}
			else
			{
				verticalflag=0;
			}
			
			if((key_3&0x0c)==0x04)
			{
				horizontalflag=1;
			}
			else if((key_3&0x0c)==0x08)
			{
				horizontalflag=2;
			}
			else
			{
				horizontalflag=0;
			}
			if((key_3&0x10)==0x10)//�Ŵ�3dģ��
			{
				ctrsizeflag=2;
			}
			else
			{
				ctrsizeflag=0;
			}
			but_M3_A1->resetValue();
			but_M3_A2->resetValue();
		}
		else//shift��û����
		{
			horizontalflag=0;
			verticalflag=0;
			if((key_3&0x03)==0x01&&(backjoy[0]==0)&&(backjoy[1]==0)&&((backjoy[2]&0x0f)==0))//z��������
			{
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	   //״̬λ��0
				if(coordShow->getValue())
					commanddata[3]|=0x07;	//3dģʽ�������
				else
					commanddata[3]|=0x06;	//3dģʽ�ѿ�����		
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[4]&=0xf7;//BIT3��0							
				commanddata[4]&=0xf8;//ǰ��λ��0
				commanddata[4]|=((char)myarms->value());//���ٶ�λ	
				but_M2_A1->resetValue();
				but_M2_A2->resetValue();
				but_M2_A3->resetValue();
				but_M2_A4->resetValue();
				but_M2_A5->resetValue();
				but_M2_A6->resetValue();
				but_M2_B1->resetValue();
				but_M2_B2->resetValue();
				but_M2_B3->resetValue();
				but_M2_B4->resetValue();
			}
			else if((key_3&0x03)==0x02&&(backjoy[0]==0)&&(backjoy[1]==0)&&((backjoy[2]&0x0f)==0))//z��������
			{
				commanddata[8]&=0xf0;
				commanddata[8]|=0x04;
				commanddata[5]&=0xf8;
				commanddata[3]&=0xf8;	   //״̬λ��0
				if(coordShow->getValue())
					commanddata[3]|=0x07;	//3dģʽ�������
				else
					commanddata[3]|=0x06;	//3dģʽ�ѿ�����	
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[4]|=0x08;	   //��־��1
				commanddata[4]&=0xf8;//ǰ��λ��0
				commanddata[4]|=((char)myarms->value());//���ٶ�λ
				but_M2_A1->resetValue();
				but_M2_A2->resetValue();
				but_M2_A3->resetValue();
				but_M2_A4->resetValue();
				but_M2_A5->resetValue();
				but_M2_A6->resetValue();
				but_M2_B1->resetValue();
				but_M2_B2->resetValue();
				but_M2_B3->resetValue();
				but_M2_B4->resetValue();
			}
			else if((commanddata[3]&0x07)==0x06||(commanddata[3]&0x07)==0x07)//�������3Dģʽ��
			{
				commanddata[8]&=0xf0;
				commanddata[3]&=0xf8;	   //״̬λ��0 ȡ��3Dģʽ
				commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
				commanddata[4]&=0xf8;//ǰ��λ��0
			}
			
			if((key_3&0x0c)==0x04)//���󽹾�
			{
				jjUp();
			}
			else if((key_3&0x0c)==0x08)//��С����
			{
				jjDown();
			}
			else
			{
				but_M3_A1->resetValue();
				but_M3_A2->resetValue();
				focflag=0;
			}
			
			if((key_3&0x10)==0x10)//��С3Dģ��
			{
				ctrsizeflag=1;
			}
			else
			{
				ctrsizeflag=0;
			}
		}
	}

	if(key_4!=backjoy[4])//key_hm
	{
		tem=backjoy[4];
		backjoy[4]=key_4;
		if((key_4&0x1f)==0x01)//h1
		{
			setM1();
			//modelflag=0;
			//updateModel();
		}
		else if((key_4&0x1f)==0x02)
		{
			setM2();
			//modelflag=1;
			//updateModel();
		}
		else if((key_4&0x1f)==0x04)
		{
			setM3();
			//modelflag=2;
			//updateModel();
		}
		else if((key_4&0x1f)==0x08)
		{
			//Ԥ����ģʽ
		}
		else if((key_4&0x1f)==0x10)
		{
			//Ԥ����ģʽ
		}
		
		
		if((key_4&0xe0)==0x20)//�߿�
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
		if(((key_4&0x40)==0x40)&&((tem&0x40)==0))//����
		{
 			zmControl();//��������
		}
		if(((key_4&0x80)==0x80)&&((tem&0x80)==0))//һ��ͼ��Ŵ�
		{

			if(videoflag)
			{
				//avideo->setPosition(0);
				if(hide_flag==false)
					// no_use3d mywid->setGeometry(104*w,453*h,259*w,143*h);
				videoflag=false;
			}
			else
			{
				//avideo->setPosition(1);
				if(hide_flag==false)
					// no_use3d mywid->setGeometry(104*w,653*h,259*w,143*h);
				videoflag=true;
			}	
		}
	}
	
	if(key_6!=backjoy[6])//��̨������ת
	{
		signed char speed=(signed char)key_6;
		//ȡ��3ά����
		commanddata[8]&=0xf0;
		commanddata[3]&=0xf8;	   //״̬λ��0
		commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
		commanddata[4]&=0xf8;//ǰ��λ��0
		commanddata[5]&=0xf8;//ǰ��λ��0		
		speed=speed/10;
		if(speed==0)//��תֹͣ
		{
			commanddata[6]&=0x8f;//BIT 4 5 6 λ��0	
		}
		else
		if(speed < 0)//��̨����
		{
			speed=-speed;
			if(speed>7)
				speed=7;
			commanddata[6]|=0x80;//BIT7��1
			commanddata[6]&=0x8f;//BIT 4 5 6 λ��0
			commanddata[6]|=(unsigned char)(speed<<4);      //BIT 4 5 6 λ���ٶ�
		}	
		else
		if(speed>0)//��̨����
		{
			
			if(speed>7)
				speed=7;
			commanddata[6]&=0x7f;//BIT7��0
			commanddata[6]&=0x8f;//BIT 4 5 6 λ��0
			commanddata[6]|=(unsigned char)(speed<<4);      //BIT 4 5 6 λ���ٶ�		
		}
		backjoy[6]=key_6;		
	}
	
	if(key_7!=backjoy[7])//��̨���¸���
	{
		commanddata[8]&=0xf0;
		commanddata[3]&=0xf8;	   //״̬λ��0
		commanddata[6]&=0x88;//BIT 4 5 6 λ��0 BIT 0 1 2 λ��0
		commanddata[4]&=0xf8;//ǰ��λ��0
		commanddata[5]&=0xf8;//ǰ��λ��0	
		signed char speed=(signed char)key_7;
		speed=speed/10;
		
		if(speed==0)//��̨����ֹͣ
		{
			commanddata[6]&=0xf8;//BIT 0 1 2 λ��0	
		}
		else	
		if(speed<0)//��̨�¸�
		{
			speed=-speed;
			if(speed>7)
				speed=7;
			commanddata[6]&=0xf7;//BIT3��0
			
			commanddata[6]&=0xf8;//BIT 0 1 2 λ��0
			commanddata[6]|=(unsigned char)speed;      //BIT 0 1 2 λ���ٶ�		
		}
		else	
		if(speed>0)//��̨����
		{
			if(speed>7)
				speed=7;
			commanddata[6]|=0x08;//BIT3��1
			commanddata[6]&=0xf8;//BIT 0 1 2 λ��0
			commanddata[6]|=(unsigned char)speed;      //BIT 0 1 2 λ���ٶ�
		}
		backjoy[7]=key_7;
	}

	if(key_8!=backjoy[8]||key_9!=backjoy[9])//�г�����
	{		
		signed char x=(signed char)key_8;
		signed char y=(signed char)key_9;
		
		int ls=((y+x/3)/3)*myruns->value();
		int rs=((y-x/3)/3)*myruns->value();

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
			commanddata[0]&=0x10;
		else if(ls==0&&rs<0)
		{
			commanddata[0]&=0x10;
			commanddata[0]|=0x02;
		}
		else if(ls==0&&rs>0)
		{
			commanddata[0]&=0x10;
			commanddata[0]|=0x01;				
		}
		else if(ls<0&&rs==0)
		{
			commanddata[0]&=0x10;
			commanddata[0]|=0x08;			
		}
		else if(ls<0&&rs<0)
		{
			commanddata[0]&=0x10;
			commanddata[0]|=0x0A;			
		}
		else if(ls<0&&rs>0)
		{
			commanddata[0]&=0x10;
			commanddata[0]|=0x09;				
		}
		else if(ls>0&&rs==0)
		{
			commanddata[0]&=0x10;
			commanddata[0]|=0x04;				
		}
		else if(ls>0&&rs<0)
		{
			commanddata[0]&=0x10;
			commanddata[0]|=0x06;				
		}
		else if(ls>0&&rs>0)
		{
			commanddata[0]&=0x10;
			commanddata[0]|=0x05;				
		}
		commanddata[1]=ABS_value(ls);
		commanddata[2]=ABS_value(rs);
		backjoy[8]=key_8;
		backjoy[9]=key_9;			
	}
	if(key_10!=backjoy[10])//���1��ѹ
	{
		mybattery_4->setValue(backjoy[10]);
		backjoy[10]=key_10;
	}
	if(key_11!=backjoy[11])//���2��ѹ
	{
		mybattery_5->setValue(backjoy[11]);
		backjoy[11]=key_11;
	}
}


//��Ӧ�����˵�����
void Mainframe::readyRead(QByteArray str)
{	
	//mutexflag.lock(); //���������� 
	//busyflag=true;
	//mutexflag.unlock(); //����������
	//indicatorlight->setLightOn();
	
	if(backdata[0]!=str.at(1))//�����ٶ�
	{
		backdata[0]=str.at(1);
		//myspeed->setValue_1((signed int)((signed char)backdata[0])*2); //�°���������ٶȷ���
	}
	if(backdata[1]!=str.at(2))//�ҵ���ٶ�
	{
		backdata[1]=str.at(2);
		//myspeed->setValue(-(signed int)((signed char)backdata[1])*2);
	}
	unsigned char a=(unsigned char)(str.at(0));
	switch(a)
	{
		case 0x80:
			if(backdata[2]!=str.at(3))//������ת�Ƕ�
			{
				backdata[2]=str.at(3);
				// no_use3d mywid->dabiRotate(backdata[2]*2);
				mywid_2d->setValue_7(backdata[2]*2);
			}
			if(backdata[3]!=str.at(4))//��צ��ת�Ƕ�
			{
				backdata[3]=str.at(4);
				// no_use3d mywid->shouwanRotate(-backdata[3]*2);
				mywid_2d->setValue_6(backdata[3]*2);
			}
			if(backdata[4]!=str.at(5))//��צץ�ֿ��
			{
				backdata[4]=str.at(5);
				// no_use3d mywid->shouzhuaMediate(-backdata[4]*2);
				mywid_2d->setValue_5(backdata[4]*2);
			}
			if(backdata[5]!=str.at(6))//�ڱ�ģʽ����??????????
			{
				backdata[5]=str.at(6);
			}
			if(backdata[6]!=str.at(7))//��ص�ѹ1
			{
				backdata[6]=str.at(7);
				mybattery->setValue(backdata[6]*2);
			}															
			break;
		case 0x81:
			if(backdata[7]!=str.at(3))//��۸����Ƕ�
			{
				backdata[7]=str.at(3);
				// no_use3d mywid->dabiPitch(backdata[7]*2-180);
				mywid_2d->setValue_1(backdata[7]*2);
			}
			if(backdata[8]!=str.at(4))//��̨�����Ƕ�
			{
				backdata[8]=str.at(4);
				// no_use3d mywid->yuntaiPitch(backdata[8]*2+180);
				mywid_2d->setValue_4(backdata[8]*2);
			}
			if(backdata[9]!=str.at(5))//ǰ֧�۽Ƕ�
			{
				backdata[9]=str.at(5);
				// no_use3d mywid->zhibiPitch(backdata[9]*2);
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
				mybattery_1->setValue(backdata[11]);
			}				
			break;
		case 0x82:
			if(backdata[12]!=str.at(3))//С�۸����Ƕ�
			{
				backdata[12]=str.at(3);
				// no_use3d mywid->xiaobiPitch(backdata[12]*2+187);
				mywid_2d->setValue_2(backdata[12]*2);
			}
			if(backdata[13]!=str.at(4))//��̨��ת�Ƕ�
			{
				backdata[13]=str.at(4);
				// no_use3d mywid->yuntaiRotate(backdata[13]*2);
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
				mybattery_2->setValue(backdata[16]);
			}			
			break;
			//
		case 0x83:
			if(backdata[17]!=str.at(3))//��ؽڽǶ�
			{
				backdata[17]=str.at(3);
				// no_use3d mywid->shouwanPitch(backdata[17]*2-3);
				mywid_2d->setValue_3(backdata[17]*2);
			}
			if(backdata[18]!=str.at(4))//����ͷ�����Ƕ�
			{
				backdata[18]=str.at(4);
				// no_use3d mywid->qianjinxiangjiPitch(backdata[18]*2);
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
				mybattery_3->setValue(backdata[21]);
			}			
			break;
	}
	//mutexflag.lock(); //���������� 
	//busyflag=false;
	//mutexflag.unlock(); //���������� 	
}

//�ı�ģ�͵Ĵ�С
void Mainframe::changmodelsize(int flag)
{
	if(flag==1)
	{
		sizeCtr3d->setValue((sizeCtr3d->getValue())-1);
	}
	else if(flag==3)
	{
		sizeCtr3d->setValue((sizeCtr3d->getValue())+1);
	}
	else if(flag==2)
	{
		// no_use3d mywid->updatesize(3.0);
	}
}

//�������»���
void Mainframe::paintEvent(QPaintEvent *)
{
	QPainter painter(this);	
	painter.setRenderHint(QPainter::Antialiasing);
	painter.scale(width()/800.0,height()/600.0);
	switch(modelflag)
	{
		case 0:
		case 1:
		case 2:
			painter.drawPixmap ( 0, 0, 800,600,pix);
			break;			
		case 3:
			painter.drawPixmap ( 0, 0, 800,600,pix1);
			break;			
		case 4:
			painter.drawPixmap ( 0, 0, 800,600,pix2);
			break; 			
							
	}
	painter.end();
}
void Mainframe::keyPressEvent(QKeyEvent *k)
{
	if(k->key()==Qt::Key_A)
	{
		setM1();
	}
	if(k->key()==Qt::Key_S)
	{
		setM2();
	}
	if(k->key()==Qt::Key_D)
	{
		setM3();
	}
	if(k->key()==Qt::Key_Escape)
	{
		this->close();
	}	
}
//void Mainframe::on_horizontalSlider_valueChanged(int v)
//{
	//mywid->shouzhuaMediate(v);
//}









