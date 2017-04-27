#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <qdatetime.h>
#include <qtimer.h>
#include "ui_mainframe.h"


#include "roll.h"
#include "pitch.h"
#include "speed.h"
#include "battery.h"
#include "signalshow.h"
#include "speedgrade.h"
#include "ctrsize.h"

#include "modle_2d.h"
#include "light.h"
#include "coord.h"

#include "videoFlag.h"
#include "change3d.h"
#include "videoDis.h"
#include "virtualDisjunctor.h"	//�Զ��尴ť

#include "dataType.h"
#include "serialPortThread.h"
#include "processImage.h"


//���ܿ���
//#define USE_3D


extern QMutex mutexflag;
extern bool busyflag;	//������ɱ�־
class Mainframe : public QDialog, public Ui::mainframe
{
	Q_OBJECT
	public:
		Mainframe( QWidget * parent = 0, Qt::WindowFlags f = 0 );
		~Mainframe();


		
	private slots:		
		void readyRead(QByteArray);
		void disposejoy(QByteArray);
		void changmodelsize(int);
		void sendcommand();
		
		void setM1();//����Ϊģʽ1
		void setM2();//����Ϊģʽ2
		void setM3();//����Ϊģʽ3
		void setM4();//����Ϊģʽ4
		void setM5();//����Ϊģʽ5

		void zb_tq();//֧��̧��
		void zb_zd();//֧��֧��
		void zb_sp();//֧��ˮƽ
		void zb_sq();//֧������
		void zb_wz();//֧��΢֧
		void sb_qg();//�ֱ�ǰ��
		
		
		void sb_qz();//�ֱ�ȫչ
		void sb_sq();//�ֱ�����
		void sb_qs();//�ֱ�ǰ��
		void sb_bz();//�ֱ۰�չ
		
			

		void zmControl();//��������
			
		void setCH1();//CH1ȫ��
		void setCH2();//CH3ȫ��
		void setCH3();//CH2ȫ��
		void setCH4();//CH4ȫ��
		void setCHAll();//�ۺ���ʾ
		void setCHFull();//ȫ����ʾ
		void changeVideo(int);//�л���Ƶ
		void asgChange();
		void rsgChange();
		void jjChange();
		
		void xb_fy();
		void sw_fy();
		void xj_fy();
		void zb_fy();
		void db_fy();
		void db_xz();
		void sz_kh();
		void sz_xz();	
			
	protected:
		void paintEvent(QPaintEvent *event);
		void keyPressEvent(QKeyEvent *event);
		
	private:
		//<����ͷ��ص�������>
		ProcessImage *cameraProcess;
		//</����ͷ��ص�������>
		Roll *myroll;
		Pitch *mypitch;
		Speed *myspeed;
		// no_use3d mymodel *mywid;               //3Dģʽ
		Battery *mybattery;
		Battery *mybattery_1;
		Battery *mybattery_2;
		Battery *mybattery_3;
		Battery *mybattery_4;
		Battery *mybattery_5;
		SignalShow *mysignalshow;
		SpeedGrade *myarms;
		SpeedGrade *myruns;
		CtrSize *myctrsize;
		int myfocaldis;

		Modle_2d *mywid_2d;             
		Light *lightShow;               //��ʶ�������״̬
		Coord *coordShow;               //������ʾ����������ʾһ��������Ŷ���
		
		VideoFlag *videoFlagShow;       //ָʾ��ǰ������ʾ״̬
		Change3d *sizeCtr3d;            //�ı�2Dͼ���С�Ļ��飬�������ڻ���
		VideoDis *avideo;               //����Ƶ����ʾ�ı߿��Ա�ʾ����״̬
		
		VirtualDisjunctor *but_M1;
		VirtualDisjunctor *but_M2;
		VirtualDisjunctor *but_M3;
		VirtualDisjunctor *but_M4;
		VirtualDisjunctor *but_M5;
		
		VirtualDisjunctor *but_M1_A1;
		VirtualDisjunctor *but_M1_A2;
		VirtualDisjunctor *but_M1_A3;
		VirtualDisjunctor *but_M1_A4;
		VirtualDisjunctor *but_M1_A5;
		VirtualDisjunctor *but_M1_A6;
		VirtualDisjunctor *but_M1_A7;
		VirtualDisjunctor *but_M1_A8;
		VirtualDisjunctor *but_M1_B1;
		VirtualDisjunctor *but_M1_B2;
		VirtualDisjunctor *but_M1_B3;
		VirtualDisjunctor *but_M1_B4;
		VirtualDisjunctor *but_M1_B5;
		VirtualDisjunctor *but_M1_B6;
		VirtualDisjunctor *but_M1_B7;
		VirtualDisjunctor *but_M1_B8;
		
		VirtualDisjunctor *but_M2_A1;
		VirtualDisjunctor *but_M2_A2;
		VirtualDisjunctor *but_M2_A3;
		VirtualDisjunctor *but_M2_A4;
		VirtualDisjunctor *but_M2_A5;
		VirtualDisjunctor *but_M2_A6;
		VirtualDisjunctor *but_M2_A7;
		VirtualDisjunctor *but_M2_A8;
		VirtualDisjunctor *but_M2_B1;
		VirtualDisjunctor *but_M2_B2;
		VirtualDisjunctor *but_M2_B3;
		VirtualDisjunctor *but_M2_B4;


		VirtualDisjunctor *but_M3_A1;
		VirtualDisjunctor *but_M3_A2;
		VirtualDisjunctor *but_M3_A3;
		VirtualDisjunctor *but_M3_A4;
		VirtualDisjunctor *but_M3_A5;
		VirtualDisjunctor *but_M3_A6;
		VirtualDisjunctor *but_M3_A7;
		VirtualDisjunctor *but_M3_A8;
		VirtualDisjunctor *but_M3_B1;
		VirtualDisjunctor *but_M3_B2;
		VirtualDisjunctor *but_M3_B3;
		VirtualDisjunctor *but_M3_B4;
		VirtualDisjunctor *but_M3_B5;
		VirtualDisjunctor *but_M3_B6;
		VirtualDisjunctor *but_M3_B7;
		VirtualDisjunctor *but_M3_B8;

		VirtualDisjunctor *but_asg1;
		VirtualDisjunctor *but_asg2;
		VirtualDisjunctor *but_rsg1;
		VirtualDisjunctor *but_rsg2;
		
	    //ReceiveThread *receiveThread;   //�����߳�
	    bool mouseOK;
		double w;
		double h;
		QTimer *timer;
		QPoint last;
		int winposflag;
		
		ReceiveFrame *receiveFrame;          //��������֡������
		SerialPortThread *serialPortThread;  //�������ݽ����߳�
		unsigned char *backdata;      //�������� ���������ݱ��ݣ�Ҳ�������ڱ������ת���Ļ���������
		//QByteArray senddata;        //ֱ��ʹ��commanddata���ͣ�������senddata��ת��
		char *commanddata;            //���͵�����
		
		int ctrsizeflag;
		int verticalflag;
		int horizontalflag;
		int armspeedflag;
		int runapeedflag;
		int armsp;
		int runsp;
		int focflag;
		int focsp;

		bool videoflag;
		bool hide_flag;
		int modelflag;    	         //ģʽ��־ ��Ҫ��ֱ�ӿ��ơ�Ԥ��λ���ƣ�����ͷ����

		unsigned char *backjoy;	     //�������ݣ����ڼ�¼���水��ֵ
		
		QPixmap pix;
		QPixmap pix1;
		QPixmap pix2;
		
		void initComponent();//��ʼ������
		void initData();	 //��ʼ��ȫ�ֱ���
		void initPix();	 	 //��ʼ�����汳��
		void initConnect();	 //��ʼ���źźͲ۵Ĺ���
		void updateModel();  //����ģʽ
		
		void jjUp();//��������
		void jjDown();//������С
		void xbUp();//С������
		void xbDown();//С���¸�
		void swUp();//��������
		void swDown();//�����¸�
		void xjUp();//�������
		void xjDown();//����¸�
		void zbDown();//֧���¸�
		void zbUp();//֧������
		
		void dbUp();//�������
		void dbDown();//����¸�
		void dbleft();//�������
		void dbright();//�������
		void szClose();//��ץ���
		void szOpen();//��ץ�ɿ�
		void szright();//��ץ����
		void szleft();//��ץ����		
};
 //#endif
#endif