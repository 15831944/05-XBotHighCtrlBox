

/*****************************************************
˵����������ѭ��˳���
���ߣ�������
���ڣ�2016-12-12
��ע����Ҫ���ڶԴ������ݽ��ղ�ת�����ã�
��Ϊ����������һ��һ���ַ����յģ�����Ҫ������֡����ʱ��
��Ҫ�õ�һ��������߶���ת�棬Ȼ�����ݱ��浽���յ����ݽṹ�С�
�ӵĳ��� = ����֡�ĳ��� + 1	����Ϊѭ�����е�front���������

*****************************************************/
#ifndef CYQUEUE_H
#define CYQUEUE_H

#define QUEUESIZE  21
typedef unsigned char ElemType;

typedef struct 
{
	ElemType data[QUEUESIZE];  //�������Ԫ��
	int front,rear;   //��ͷ�Ͷ�β
}SqQueue;


class CyQueue
{
public:
	CyQueue();
	void ClearQueue();
	int EnQueue(ElemType x);  //���
	int DeQueue(ElemType &x);   //����
	int GetHead(ElemType &x);   //��ȡͷԪ��
	int IsEmpty();    //�ж�Ϊ��
	int IsFull();  //�ж϶���

public:
	SqQueue qu;

};


#endif