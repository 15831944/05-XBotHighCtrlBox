/********************************************************************************
������processImage.cppʵ��ͼ����ʾ������YUV2RGBThread�߳�
���ߣ�������
���ڣ�2017-01-11
��ע��processImage.cpp����YUV2RGBThread�࣬ʵ��ͼ��Ĳɼ���ת��
********************************************************************************/


#include <QtGui>
#include "processImage.h"
#include "camera.h"


ProcessImage::ProcessImage(QWidget *parent):QWidget(parent)
{
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    pp = (unsigned char *)malloc(720 * 576/*QWidget::width()*QWidget::height()*/* 3 * sizeof(char));
    //1201 painter = new QPainter(this);
    frame = new QImage(pp,720,576,QImage::Format_RGB888);
   // frame = new QPixmap(640,320);
    label = new QLabel(this);
    label->setGeometry(0,0,Win_width,Win_height);
	//label->resize(Win_width,Win_height);
	imgScaled = new QImage;

	
	cameraThread=new YUV2RGBThread(pp);
	connect(cameraThread,SIGNAL(readySignal()),this,SLOT(update()));  //更新
	cameraThread->start();

    //QHBoxLayout *hLayout = new QHBoxLayout();
    //hLayout->addWidget(label);
    //setLayout(hLayout);
    
    //setWindowTitle(tr("Capture"));
}

ProcessImage::~ProcessImage()
{

}

void ProcessImage::paintEvent(QPaintEvent *e)
{
	//painter = new QPainter(this);

    frame->loadFromData((unsigned char *)pp,/*len*/720*576 * 3 * sizeof(char));


	//缩放显示

	//IgnoreAspectRatio������������KeepAspectRatio�ǵȱ�������
	*imgScaled=frame->scaled(640,416,Qt::IgnoreAspectRatio);

    label->setPixmap(QPixmap::fromImage(*imgScaled,Qt::AutoColor));

}

