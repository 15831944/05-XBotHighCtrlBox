#include <QPainter>
#include <QPaintEngine>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <qgraphicsscale3d.h>
#include "glviewwidget.h"
#include <math.h>

GLViewWidget::GLViewWidget(QWidget *parent, bool inde)
	:QGLWidget(parent)
{
	m_indesigner = inde;//�Ƿ��ڻ����У�

	m_camera = new QGLCamera(parent);//ʵ��������ͷ��
	m_rotinterval = 0;				 //������ת�����������Ϊ0
	m_timerid = 0;					 //��ʱʱ��Ϊ0

	QObject::connect(m_camera, SIGNAL(projectionChanged()),
		this, SLOT(cameraChanged()));					//�����źźͲۣ��źţ�ͶӰ�ı�
	QObject::connect(m_camera, SIGNAL(viewChanged()),
		this, SLOT(cameraChanged()));					//�����źźͲۣ��źţ���Ұ�ı�
}

GLViewWidget::~GLViewWidget() //��������,���캯������û�κ�NEW 
{
	//stop();
}

void GLViewWidget::setEyeXY(QPointF eye)//��������ͷxy����
{
	QVector3D pos;						//������ά���ꣿ
	pos = QVector3D(eye);				//�������ݣ�ǿ������ת��
	pos.setZ(camera()->eye().z());		//Z����
	camera()->setEye(pos);				//����
}

void GLViewWidget::setEyeZ(qreal eyeZ)	//��������ͷλ�õ�z���ꣿ
{
	QVector3D pos;					  	//������ά���ꣿ
	pos = QVector3D(camera()->eye().toVector2D(),eyeZ);		//����XY
	camera()->setEye(pos);				//����
}

void GLViewWidget::setEyeCenterXY(QPointF eye)//�����ӵ�xy 
{
	QVector3D pos;
	pos = QVector3D(eye);
	pos.setZ(camera()->center().z());
	camera()->setCenter(pos);
}

void GLViewWidget::setEyeCenterZ(qreal eyeZ)//�����ӵ�z
{
	QVector3D pos;
	pos = QVector3D(camera()->center().toVector2D(),eyeZ);
	camera()->setCenter(pos);
}

void GLViewWidget::resetEyeXY() //��λ����ͷ��
{
	setEyeXY(QPointF(0,0));
}

void GLViewWidget::resetEyeZ()
{
	setEyeZ(0);
}

void GLViewWidget::resetEyeCenterXY()
{
	setEyeCenterXY(QPointF(0,0));
}

void GLViewWidget::resetEyeCenterZ()
{
	setEyeCenterZ(0);
}

//void GLViewWidget::showEvent ( QShowEvent * )
//{
	//if(m_autorotate && !m_indesigner)
		//start();
//}

//void GLViewWidget::start()
//{
	//m_timerid = startTimer(m_rotinterval);
//}

//void GLViewWidget::stop()
//{
	//if(m_timerid){
		//killTimer(m_timerid);
		//m_timerid=0;
	//}
//}

//void GLViewWidget::setRotInterval(int interval)
//{
	//m_rotinterval = interval;
	//if(m_timerid){
		//stop();
		//start();
	//}
//}

//void GLViewWidget::timerEvent(QTimerEvent *event)
//{
	//if(m_timerid!=event->timerId())
		//return;

	//rorateView(m_rotepX, m_rotepY, m_rotepZ);
//}

#define PI 3.14159265

qreal GLViewWidget::angle() const
{
	//rotate around y axis,  angle=acrtan(z/x)
	return atan2(m_camera->eye().x(), m_camera->eye().z())*180/PI;
}

void GLViewWidget::setAngle(qreal a)
{
	rorateView(0, a-angle(), 0);
}

void GLViewWidget::cameraChanged()
{
	// Queue an update for the next event loop.
	update();
}

QGLCamera *GLViewWidget::camera() const
{
	return m_camera;
}

void GLViewWidget::initializeGL()
{
	QGLPainter painter;
	painter.begin();

	// Set the default depth buffer options.����Ĭ�ϵ���Ȼ����ѡ��
	
	glEnable(GL_DEPTH_TEST);//glEnable()��glDisable()��һ�Թ����෴�ĺ���,����glEnable�������Ǵ򿪷������˵�GL���ܡ�
							//glEnable���������Ҫ�ǿ���OPENGL�Ĺ��ܣ��ô����Ǹ�������Ŧ��GL_DEPTH_TEST,��ʾ����Ȳ��ԡ�
	glDepthFunc(GL_LESS);						//���С��ʱ�����Ⱦ��
	//glDepthFunc(GL_GREATER  );
	glDepthMask(GL_TRUE);						//��Ȼ����д
#if defined(QT_OPENGL_ES)						//�������� �������ҽ����������ִ������ĺ�������x��y�������겻ͬ����OpenGL�У�z�������Ǳ���Ϊλ��0.0~1.0�ķ�Χ֮�䡣��
	glDepthRangef(0.0f, 1.0f);	
#else
	glDepthRange(0.0f, 1.0f);  					//������������ִ�д˺���
#endif

	// Set the default blend options. ����Ĭ�ϵĻ��ѡ�
	if (painter.hasOpenGLFeature(QOpenGLFunctions::BlendColor))
		painter.glBlendColor(0, 0, 0, 0);//��ɫ��ϣ�
		
		
		
//��ž�����������һ������ָ��ԴͼԪ��alpha��ȡֵ���㷽�����ڶ�������ָ��Ŀ�괦��alpha�ļ��㷽���� 

//------ 
//�Ҹ�����⣺ 
//����������ȡֵ�����������³���֮һ�� 
//GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, and GL_SRC_ALPHA_SATURATE 
//����GL_ZERO��ʾalphaȡֵΪ0��GL_ONE��ʾ1��GL_DST_COLOR��ʾȡĿ���������ɫֵ��GL_SRC_ALPHA��ʾȡԴ�����alphaֵ�ȵȡ����磺 

//glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
//��ʾ����Ⱦ��ͼ����ӵ�Ŀ������Ҳ����˵Դ��ÿһ�����ص�alpha�������Լ���alpha��Ŀ���ÿһ�����ص�alpha����1���������Ӵ���Խ�࣬���ӵ�ͼԪ��alphaԽ�ߣ��õ��Ľ����Խ������������ں����ڱ�����Ч����

//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
//��ʾ����Ⱦ��ͼ���ںϵ�Ŀ������Ҳ����˵Դ��ÿһ�����ص�alpha�������Լ���alpha��Ŀ���ÿһ�����ص�alpha����1��ȥ��λ��Դ���ص�alpha�� ��˲��۵��Ӷ��ٴΣ������ǲ���ġ�

//��˵ȵȡ��Լ���һ�ԲŻ����ס� 

//��������������ܶ��ؼ�Ч���ĺ��ģ�������������˵��ֻ��Ƥë��Ҫ���������ͱ��뿴�ٷ��ĵ���MSDN����һ����ȫ����ĵ�����Ӣ�ﲻ��ҲҪӲ������ʵ˭�տ�ʼ����ʱ�򶼻�ͷ�ۣ�������Ӣ����Ȼ����������...		
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //��ʾ����Ⱦ��ͼ���ںϵ�Ŀ������Ҳ����˵Դ��ÿһ�����ص�alpha�������Լ���alpha��Ŀ���ÿһ�����ص�alpha����1��ȥ��λ��Դ���ص�alpha�� ��˲��۵��Ӷ��ٴΣ������ǲ���ġ�
	
	if (painter.hasOpenGLFeature(QOpenGLFunctions::BlendEquation))
		painter.glBlendEquation(GL_FUNC_ADD);//ָ����ϲ���
	else if (painter.hasOpenGLFeature(QOpenGLFunctions::BlendEquationSeparate))
		painter.glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_CULL_FACE);
	
	m_camera-> setFarPlane((qreal)10.0f);
	//m_camera-> setEyeSeparation((qreal)0.01); 
	m_camera-> setNearPlane(qreal(1.0f)); 
	m_camera-> setViewSize(QSizeF(0.4,0.4));
	 
	initializeGL(&painter);

}

void GLViewWidget::paintGL()
{
	// Paint the scene contents.��Ⱦ���������ݡ�
	QGLPainter painter;
	
	QGLAbstractSurface *surface=NULL;
	//glLoadIdentity();
	painter.begin();

	// No camera separation, so render the same image into both buffers.û���������,�����������ͬ��ͼ����Ⱦ���塣

	painter.pushSurface(surface);
	
	painter.setEye(QGL::NoEye);
	
	earlyPaintGL(&painter);
	
	painter.setCamera(m_camera);
	
	//gluPerspective(45,1,0,1000);
	//
	//gluLookAt(0,0,10,0,0,0,0,1,0);

	paintGL(&painter);
	
	painter.popSurface();
}

/*!
	\internal�ڲ�
*/
void GLViewWidget::resizeGL(int w, int h)
{
	// Set up the standard viewport for the new window size.�������±�׼��ͼ���ڳߴ硣
	int side = qMin(w, h);
	glViewport((w - side) / 2, (h - side) / 2, side, side);
}

/*!
	Initializes the current GL context represented by \a painter.

	\sa paintGL()
*/
void GLViewWidget::initializeGL(QGLPainter *painter)//����
{
	Q_UNUSED(painter);								//��ֹ����������
}

/*!
	Performs early painting operations just after \a painter
	is initialized but before the camera is set up.  The default
	implementation clears the color buffer and depth buffer.

	This function is typically overridden to draw scene backdrops
	on the color buffer before the rest of the scene is drawn
	by paintGL().

	\sa paintGL()
*/
void GLViewWidget::earlyPaintGL(QGLPainter *painter)//�����ػ�GL����
{
	Q_UNUSED(painter);								//��ֹ����������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

void GLViewWidget::moveView(QVector3D delta)		//�ƶ�������ʵ�������ƶ�����ͷ���ӵ�λ��
{
	m_camera->setEye(m_camera->eye() - delta);
	m_camera->setCenter(m_camera->center() - delta);
}

void GLViewWidget::scaleView(qreal scale)//���ų���
{
/*	qreal fov = m_camera->fieldOfView();
	if (fov != 0.0f)
		m_camera->setFieldOfView(m_camera->fieldOfView() / scale);
	else
		m_camera->setViewSize(m_camera->viewSize() / scale);
*/
	QVector3D viewVector= camera()->eye() - camera()->center();
	qreal zoomMag = viewVector.length();//Ӧ��������ͷ�������������ĵ�ľ���
	qreal zoomIncrement = scale;
	if (!qFuzzyIsNull(zoomIncrement))
	{
		zoomMag = zoomIncrement;
		if (zoomMag < 0.01f)
			zoomMag = 0.01f;
		QRay3D viewLine(camera()->center(), viewVector.normalized());
		camera()->setEye(viewLine.point(zoomMag));
	}
}

void GLViewWidget::rorateView(qreal anglex, qreal angley, qreal anglez)//��ת����
{
/*	QQuaternion q = m_camera->tilt(anglex);
	q *= m_camera->roll(angley);
	q *= m_camera->pan(anglez);
	m_camera->rotateCenter(q);*/
	m_camera->tiltPanRollCenter(anglex, angley, anglez, QGLCamera::TiltRollPan);
}

