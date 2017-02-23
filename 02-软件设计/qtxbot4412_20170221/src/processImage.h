/********************************************************************************
������processImage.cppʵ��ͼ����ʾ������YUV2RGBThread�߳�
���ߣ�������
���ڣ�2017-01-11
��ע��processImage.cpp����YUV2RGBThread�࣬ʵ��ͼ��Ĳɼ���ת��
********************************************************************************/

#ifndef PROCESSIMAGE_H
#define PROCESSIMAGE_H

#include <QtGui>
#include "YUV2RGBThread.h"


//����Ҫ�ı�����ͷ���ڴ�Сʱ��ֻ��Ҫ�޸����������������ɡ�
//ʵ����ֻ��Ҫ�޸�Label�ĳߴ缴�ɣ���Ȼ�����ת���������û��ͼ��
#define Win_width  682
#define Win_height 430

class ProcessImage : public QWidget
{
    Q_OBJECT
public:
    ProcessImage(QWidget *parent=0);
    ~ProcessImage();

private:
    QPainter *painter;
    QLabel *label;
    QImage *frame;
	QImage* imgScaled;
    //QPixmap *frame;
    QTimer *timer;
	YUV2RGBThread * cameraThread;
	//unsigned char image[width*height*2];
	uchar *pp;


private slots:
    void paintEvent(QPaintEvent *);



};

#endif
