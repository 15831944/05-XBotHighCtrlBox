
#ifndef GLViewWIDGET_H
#define GLViewWIDGET_H

#include <QTime>
#include <QGLWidget>
#include <QVector3D>
#include "qglpainter.h"

class GLViewWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLViewWidget(QWidget *parent = 0, bool inde=false);//���캯������ʼ����
	~GLViewWidget();								   //�����������ͷ��ڴ�ռ�
    QGLCamera *camera() const;						   //��������ͷ����������ָ�� ����constΪ�˷�ֹ�޸ĳ�Ա��������÷�const��Ա������

	void autoRotate(QRect &rect);                      //�Զ���ת����
	bool autoRotate() const{return m_autorotate;}		//�ж��Ƿ������Զ���ת
	void setAutoRotate(bool autorotate){m_autorotate=autorotate;}//�����Ƿ��Զ���ת
	virtual void resetAutoRotate(){setAutoRotate(true);}		//����Ϊ�Զ���ת

	QPointF eyeXY() const{return camera()->eye().toPointF();}//��������ͷ��XY���ꣿ
	
	void setEyeXY(QPointF eye);		//��������ͷ��XY���ꣿ
	virtual void resetEyeXY();		//����ͷ�����λ��
	qreal eyeZ() const{return camera()->eye().z();}//��������ͷ��Z���ꣿ
	void setEyeZ(qreal eyeZ);		//��������ͷ��Z����
	virtual void resetEyeZ();		//����ͷ��Z�����λ��

	QPointF eyeCenterXY() const{return camera()->center().toPointF();}//��������ͷ��׼��XY����������
	void setEyeCenterXY(QPointF eye);								  //��������ͷ��׼���XY����������
	virtual void resetEyeCenterXY();								  //��λ����ͷ��׼���XY���������
	qreal eyeCenterZ() const{return camera()->center().z();}		  //��������ͷ��׼���Z����
	void setEyeCenterZ(qreal eyeZ);									  //��������ͷ��׼���Z����
	virtual void resetEyeCenterZ();								      //��λ����ͷ��׼���Z����

	qreal angle() const;                                              //��ȡ����Ƕ�
	virtual void setAngle(qreal a);									  //���ó���Ƕ�
	virtual void resetAngle(){setAngle(0);}							  //��λ����Ƕ�

	int rotInterval() const{return m_rotinterval;}					  //��ȡ�Զ�ѡװ�ļ������
	//void setRotInterval(int interval);							  //�����Զ���ת�ļ������
	//virtual void resetRotInterval(){setRotInterval(100);}			  //��λ�������Ϊ100�ȣ�
	

	qreal rotepX() const{return m_rotepX;}							  //��ȡ��ת�����X����?
	void setRotepX(qreal a){m_rotepX = a;}						  	  //������ת�����X������
	virtual void resetRotepX(){setRotepX(0);}						  //��λ��ת�����X����
	qreal rotepY() const{return m_rotepY;}
	void setRotepY(qreal a){m_rotepY = a;}
	virtual void resetRotepY(){setRotepY(1);}
	qreal rotepZ() const{return m_rotepZ;}
	void setRotepZ(qreal a){m_rotepZ = a;}
	virtual void resetRotepZ(){setRotepZ(0);}

public Q_SLOTS:														//���¶���ۺ���
    void cameraChanged();											//����ͷλ�øı�ĺ���
	void moveView(QVector3D delta);									//��Ұ�ƶ�
	void scaleView(qreal scale);									//��Ұ����
	void rorateView(qreal anglex, qreal angley, qreal anglez);		//��Ұ��ת
	//void start();	//start rotate
	//void stop();

protected:
	//void timerEvent(QTimerEvent *event);
	//void showEvent (QShowEvent*);

	bool m_indesigner;		//�Ƿ��ڻ����У�
	bool m_autorotate;		//�Ƿ��Զ���ת
	int m_timerid;			//��ʱ������������
	int m_rotinterval;		//��ת�����������
	qreal m_rotepX;			//��x����ת�Ķ���
	qreal m_rotepY;			//��y����ת�Ķ���
	qreal m_rotepZ;			//��z����ת�Ķ���

protected:
	void initializeGL();	//��ʼ��GL
	void paintGL();			//GL�ػ�

	virtual void resizeGL(int w, int h);          	//	GL���ڱ仯ʱ����
    virtual void initializeGL(QGLPainter *painter); //
    virtual void earlyPaintGL(QGLPainter *painter);
    virtual void paintGL(QGLPainter *painter) = 0;

private:
    QGLCamera *m_camera;	//����һ��˽�е�����ͷ��

};

#endif
