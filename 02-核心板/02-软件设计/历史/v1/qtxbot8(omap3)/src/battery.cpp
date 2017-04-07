#include <QtGui>
#include <cmath>
#include <assert.h>
#include <math.h>
#include "battery.h"
//#include <QPointarray> 
//#define  PI 3.14159265 
using namespace std;
Battery::Battery(QWidget *parent): AbstractMeter(parent)
{
	m_max=255;
	m_min=0;
	m_maximum=255;
	m_minimum=0;
  	//setMinimum(0);
	setValue(0);
	//setValue_1(0);
	setNominal(100);
	setCritical(200);
	
	//setPrefix(QString("min -2"));
	//setSuffix(QString("max +2"));
	m_digitFont.setPointSize(14);
	m_valueFont.setPointSize(18);
    //setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setWindowTitle(tr("Analog Thermometer"));
	//resize(200, 200);
	assert(m_max-m_min != 0);
}

void Battery::initCoordinateSystem(QPainter & painter)
{
		//��򵥵Ľ������ؼ�
        painter.setRenderHint(QPainter::Antialiasing);
        painter.translate(width() / 2, height() / 2);//����ԭ��
        painter.scale(width()/ 22.0, height()/ 120.0);//ͨ��(sx, sy)��������ϵͳ��ʹ�������һ�� ������
}

void Battery::paintBackground(QPainter & painter)
{
	//��򵥵Ľ������ؼ�
	initCoordinateSystem(painter);
    QLinearGradient linearGrad(QPointF(-10, 0.0), QPointF(10, 0));//���ý�����ɫ
	linearGrad.setSpread(QGradient::ReflectSpread);
    linearGrad.setColorAt(1.0, QColor(0,200,150,150));
    linearGrad.setColorAt(0.0, QColor(255,255,255,5));//QColor  ���һ������ָ����͸���� 255Ϊ��͸�� 0Ϊȫ��͸��

    //QLinearGradient linearGrad_1(QPointF(0.0, 0.0), QPointF(0.0, 10));//���ý�����ɫ
	//linearGrad_1.setSpread(QGradient::ReflectSpread);
    //linearGrad_1.setColorAt(1.0, QColor(0,255,150,50));
    //linearGrad_1.setColorAt(0.0, QColor(255,255,255,0));//QColor  ���һ������ָ����͸���� 255Ϊ��͸�� 0Ϊȫ��͸��    
    
	//painter.setBrush(QBrush(linearGrad_1));//���û�ˢΪ����ˢ��
	//painter.setPen(Qt::green);
	//painter.drawRect(-100,-12 ,200, 12);
	
	painter.setBrush(QBrush(linearGrad));//���û�ˢΪ����ˢ��
	painter.setPen(Qt::white);
	painter.drawRect(-6,-58 ,12, 8);
    painter.drawRect(-10,-50 ,20, 100);
	//painter.setPen(QColor(200,200,200));
	//for (int i=-9;i<=10;i++)
	//{
		    //painter.drawLine(i*10,-8, i*10,-5);
			//painter.drawLine(i*10,8, i*10,5);
	//}
	//painter.setPen(QColor(255,0,0));
	//painter.drawLine(0,-11, 0,-2);
	//painter.drawLine(0,11, 0,2);
	//
    //painter.setFont (m_digitFont);
    //painter.setPen(QColor(255,255,255));
    //painter.drawText( QPointF(-135,0), "Min");
    //painter.drawText( QPointF(-150,12), "-2m/s");
    //painter.drawText( QPointF(105,0), "Max");
    //painter.drawText( QPointF(100,12), "+2m/s");
painter.end(); 
}// paintBackground

void Battery::paintEvent(QPaintEvent * )
{
	//��򵥵Ľ������ؼ�
	QPainter painter(this);
    initCoordinateSystem(painter);
    
    QColor color(Qt::green);
    if(m_value<m_nominal)
    	color=Qt::red;
    if(m_value>m_critical)
   		color=Qt::blue;
	double factor =  m_value/ (m_max-m_min);
	int temp = static_cast<int> (100.0 *  factor);
    painter.setPen(Qt::NoPen);
	painter.setBrush(color);
		painter.drawRect(-8,50-temp ,16, temp);

	painter.end(); 
	drawBackground();//���ؼ�����
}// paintEvent
