#ifndef __MODEL_H__
#define __MODEL_H__
//#include <QTime>
//#include <QGLWidget>
#include <qgraphicsrotation3d.h>
#include <qglabstractscene.h>
//#include <QVector3D>
#include "glviewwidget.h"

class mymodel: public GLViewWidget
{
 Q_OBJECT
 public:
 
 	QPoint last,pos0;
 	
	mymodel(QWidget *parent = 0, bool inde=false);			//���캯��
	~mymodel();												//��������
	void reset();											//�������ã�
	int boxAngle() const{return -zhibiRot.angle();}			//��ȡ����ĽǶ�
	void resetEyeXY();										//��λ����ͷ��XYλ��
	void resetEyeZ();										//��λ����ͷ��Zλ��
	void resetEyeCenterXY();								//��λ�ӵ�XY����
	void resetEyeCenterZ();									//��λ�ӵ��Z����
	virtual void resetAngle(){setAngle(45);}				//���ó������б�Ƕ�Ϊ45��
	double getangle_v(void)
	{
		return vAngle;
	}
	double getangle_h(void)
	{
		return hAngle;
	}	
public Q_SLOTS:
	double getfocalLength(void);
	void luopanRotate(int angle);				//������ת
	void dabiPitch(int angle);					//��۸���
	void dabiRotate(int angle);					//�����ת
	
	void xiaobiPitch(int angle);				//С�۸���
	
	void yuntaiPitch(int angle);				//��̨����
	void yuntaiRotate(int angle);				//��̨��ת
	
	void shouwanPitch(int angle);				//������
	void shouwanRotate(int angle);				//������ת
	
	void zhibiPitch(int angle);					//֧�۸���
	
	void qianjinxiangjiPitch(int angle);		//ǰ���������

	void shouzhuaMediate(int angle);			//��ץ���

	void updateview_xz(double x); 								//�ۺ��������ó�����X����ת�Ƕ�
	void updateview_y(double y);
	void updatesize(double size);

protected:
	void initializeGL(QGLPainter* painter);					//��ʼ��GL
	void paintGL(QGLPainter* painter);						//GL�ػ�
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	//void paintEvent(QPaintEvent *event);
	void wheelEvent(QWheelEvent *e);
private:
	QGraphicsRotation3D luopanRot;
	QGraphicsRotation3D dipanRot; 
	QGraphicsRotation3D zhibiRot;															
	QGraphicsRotation3D dabiRot;
	QGraphicsRotation3D dabixuanzhuanRot;
	QGraphicsRotation3D qianjinxiangjiRot;
	QGraphicsRotation3D xiaobiRot;
	QGraphicsRotation3D shouwanRot;
	QGraphicsRotation3D shouzhuaxuanzhuanRot;
	QGraphicsRotation3D shouzhua1Rot;

	QGraphicsRotation3D shouzhua2Rot;

	QGraphicsRotation3D yuntaifuyanRot;
	QGraphicsRotation3D yuntaixuanzhuanRot;//
	
	QGLAbstractScene *luopan;
	QGLAbstractScene *dipan;							//�洢���� QGLAbstractScene���ʾ�����������QGLSceneNode��ɵ�3 D������
	QGLAbstractScene *zhibi;
	QGLAbstractScene *dabi;
	QGLAbstractScene *dabixuanzhuan;
	QGLAbstractScene *qianjinxiangji;
	QGLAbstractScene *xiaobi;
	QGLAbstractScene *shouwan;
	QGLAbstractScene *shouzhuaxuanzhuan;
	QGLAbstractScene *shouzhua1;

	QGLAbstractScene *shouzhua2;

	QGLAbstractScene *yuntaifuyan;
	QGLAbstractScene *yuntaixuanzhuan;
	
	QGLSceneNode *luopanNode;
	QGLSceneNode *dipanNode;								//���� ������ڵ㣿
	QGLSceneNode *zhibiNode;								//���� ������ڵ㣿
	QGLSceneNode *dabiNode;
	QGLSceneNode *dabixuanzhuanNode;
	QGLSceneNode *qianjinxiangjiNode;
	QGLSceneNode *xiaobiNode;
	QGLSceneNode *shouwanNode;
	QGLSceneNode *shouzhuaxuanzhuanNode;
	QGLSceneNode *shouzhua1Node;

	QGLSceneNode *shouzhua2Node;

	QGLSceneNode *yuntaifuyanNode;
	QGLSceneNode *yuntaixuanzhuanNode;

	double  hAngle;												//�������꾭�ȱ���
	double  vAngle;												//���������γ�ȱ���
	double focalLength;										//���� �����ֱ��
	double  VA;												//�������꾭��
	double  HA;												//���������γ��
												
	
	
};














#endif // __MODEL_H__
