#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <qdatetime.h>
#include <qtimer.h>
#include "ui_mainframe.h"
#include "model.h"
#include "compass.h"
#include "roll.h"
#include "pitch.h"
#include "speed.h"
#include "battery.h"
#include "signalshow.h"
#include "speedgrade.h"
#include "ctrsize.h"
#include "focaldis.h"
#include "mythreadport.h"
#include "select.h"
#include "modle_2d.h"

extern QMutex mutexflag;
extern bool busyflag;	//������ɱ�־
class Mainframe : public QDialog, public Ui::mainframe
{
	Q_OBJECT
	public:
		Mainframe( QWidget * parent = 0, Qt::WindowFlags f = 0 );
		~Mainframe();
		Compass *mycompass;
		Roll *myroll;
		Pitch *mypitch;
		Speed *myspeed;
		mymodel *mywid;
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
		FocalDis *myfocaldis;
		Selectfalg *myselect;
		Modle_2d *mywid_2d;
	private slots:
		//void setA(int);//������
		//void setB(int);//������
		//void setC(int);//������
		//void setD(int);//������
		
		void readyRead(QByteArray);
		void disposejoy(QByteArray);
		void hidemenu();
		void changmodelsize(int);
		void sendcommand();
		void showmyself();
	protected:
		void paintEvent(QPaintEvent *event);
	private:
	    ReceiveThread *receiveThread;   //�����߳�
	    bool mouseOK;
		double w;
		double h;
		QTimer *timer;
		QPoint last;
		int winposflag;
		unsigned char *backdata;//�������� ���������ݱ���
		QByteArray senddata;
		char *commanddata;
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
		int modelflag;    	//ģʽ��־

		unsigned char *backjoy;	//��������
		
		QPixmap pix;
		QPixmap pix1;
		QPixmap pix2;

};
 //#endif
#endif