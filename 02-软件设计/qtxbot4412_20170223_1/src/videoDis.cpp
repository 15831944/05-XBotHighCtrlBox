#include "videoDis.h"

VideoDis::VideoDis( QWidget * parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{
	//setupUi(this);
	
	mold=1;

	type=false;
	lockFlag=false;
	changeFlag=false;
	positionFlag=5;
	setPosition(0);
	last=QPoint(0,0);
	backPoint=QPoint(0,0);
	
	cameraProcess = new ProcessImage(this);
	//cameraProcess->setGeometry(59,0,682*w,430*h);
	
	//count=0;
	//timer= new QTimer(this);
	//timer->setInterval(1000);//һ��֮�����ε��Ϊ˫��
	//connect(timer, SIGNAL(timeout()), this, SLOT(changeCount())); 
}
void VideoDis::setMold(int m)
{
	mold=m;
	update();
}
//void VideoDis::changeCount()
//{
	//this->count++;
	//if(this->count>0)
	//{
		//this->count=0;
		//timer->stop();
	//}
//}
void VideoDis::setType()//�趨����������
{
	type=true;
}
void VideoDis::resetType()//�趨��ƽ̨������������
{
	type=false;
}
void VideoDis::setLock()
{
	lockFlag=true;
}

void VideoDis::resetLock()
{
	lockFlag=false;
}


void VideoDis::setPosition(int p)
{
	if(p==positionFlag)
	{
		return;
	}
	positionFlag=p;	
	if(positionFlag==1)//ȫ��Ļ��ʾ
	{
		this->setGeometry(0,24,800,576);
		cameraProcess->setGeometry(0,0,800,576);
	}
	else if(p==0)
	{
		this->setGeometry(80,32,640,416);
		cameraProcess->setGeometry(0,0,640,416);
	}
}
//void VideoDis::mouseDoubleClickEvent ( QMouseEvent * e)
//{

	//if(e->buttons()==Qt::LeftButton)
	//{

	    //if((width()>700)&&(height()<380))//�����ۺ���ʾ����
	    //{
	    	//if(e->globalPos().x()<400)
	    		//emit mouseChange(1);//��ʾƽ̨����
	    	//else
	    		//emit mouseChange(2);//��ʾ��������飩����
    	//}
    	//else if((width()<700)&&(height()>380))
    	//{

    		//if(type)
    		//{
    			//if(lockFlag)//����
					//return;
   			//}

    		//emit mouseChange(3);// ȫ����ʾ
   		//}
   		//else if((width()>700)&&(height()>500))
   		//{
   			//emit mouseChange(4);// �˳�ȫ����ʾ
  		//}
	//}		
//}

void VideoDis::mouseMoveEvent(QMouseEvent *e)
{

	if (!(e->buttons() & Qt::LeftButton))
    	return;
    int x=e->x()-last.x();
    int y=e->y()-last.y();

    if(changeFlag==false&&(x>60||x<-60))//���򻬶���Ļ�л���Ƶ
    {
    	if((last.x()<width()/2)&&(last.y()<height()/2))//��ʾCH1
    		emit mouseChange(1);
    	else if((last.x()>width()/2)&&(last.y()<height()/2))//��ʾCH1
    		emit mouseChange(2);
    	else if((last.x()<width()/2)&&(last.y()>height()/2))//��ʾCH1
    		emit mouseChange(3);
    	else if((last.x()>width()/2)&&(last.y()>height()/2))//��ʾCH1
    		emit mouseChange(4);	
    	changeFlag=true;
   	}
   	else if(changeFlag==false&&(y>160||y<-160))//���򻬶���Ƶ�ķ�����ʾ
   	{
   		emit mouseChange(0);// �ķ�����ʾ
   		changeFlag=true;
  	}
}

void VideoDis::mousePressEvent(QMouseEvent *e)
{
	last = e->pos();
	changeFlag=false;
}
//void VideoDis::mouseReleaseEvent ( QMouseEvent * e)//����ɿ��¼�
//{
	//if(lockFlag&&type)//�������Ҵ�����������
		//emit sendXY(e->globalPos().x(),e->globalPos().y());
//}

//void VideoDis::paintEvent(QPaintEvent *)
//{
	//QPainter painter(this);
	//painter.setBrush(QColor(40,40,40));
	//painter.setPen(Qt::NoPen);
	//QFont m_digitFont;
    //m_digitFont.setPointSize(12);
    //painter.setFont (m_digitFont);
	//if(width()>700)
	//{
		//painter.drawRect(0,0,800,24);
		//QPen Pen(QColor(0,255,255));
    	//painter.setPen(Pen);
    	//if(positionFlag==2)
    	//{
	    	//if(type)
	    	//{
	    		//if(mold==1)
					//painter.drawText( QPointF(10,18), "����ͼ��");
				//else if(mold==2)
					//painter.drawText( QPointF(10,18), "���ͼ��");	    		
    		//}
			//else
				//painter.drawText( QPointF(10,18), "ƽ̨ͼ��");
   		//}
	//}
//}
void VideoDis::stopVideo()
{
	//myAvideo->stop();
}
void VideoDis::startVideo()
{
	//myAvideo->start();
}

