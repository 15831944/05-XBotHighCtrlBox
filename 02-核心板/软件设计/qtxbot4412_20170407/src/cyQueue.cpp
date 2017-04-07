
/*****************************************************
˵����������ѭ��˳���
���ߣ�������
���ڣ�2016-12-12
��ע����Ҫ���ڶԴ������ݽ��ղ�ת�����ã�
��Ϊ����������һ��һ���ַ����յģ�����Ҫ������֡����ʱ��
��Ҫ�õ�һ��������߶���ת�棬Ȼ�����ݱ��浽���յ����ݽṹ�С�	
�ӵĳ��� = ����֡�ĳ��� + 1	����Ϊѭ�����е�front���������
����ѭ��˳����ж��ԣ�������������������û������ģ���Ϊ����һ��
��������Ч�ġ�
*****************************************************/
#include"cyQueue.h"

CyQueue::CyQueue()
{
	qu.front =0;
	qu.rear=0;

}

void CyQueue::ClearQueue()
{
	qu.front =0;
	qu.rear=0;
}

int CyQueue::EnQueue(ElemType x)
{
	if((qu.rear+1)%QUEUESIZE==qu.front)
		return 0;
	qu.rear=(qu.rear+1)%QUEUESIZE;
	qu.data[qu.rear]=x;
	return 1;
}

int CyQueue::DeQueue(ElemType &x)
{
	if(qu.rear==qu.front)
		return 0;
	qu.front=(qu.front+1)%QUEUESIZE;
	x=qu.data[qu.front];
	return 1;
}

int CyQueue::GetHead(ElemType &x)
{
	if(qu.rear==qu.front)
		return 0;
	x=qu.data[(qu.front+1)%QUEUESIZE];
	return 1;
}

int CyQueue::IsEmpty()
{
	if(qu.rear==qu.front)  //�ӿ�
		return 1;
	else
		return 0;

}

int CyQueue::IsFull()
{
	if((qu.rear+1)%QUEUESIZE==qu.front)  //����
		return 1;
	else 
		return 0;
}