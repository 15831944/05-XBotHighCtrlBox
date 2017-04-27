#ifndef CHAIN_H
#define CHAIN_H
#include <stdlib.h>		
#include "stm32f10x.h"
#include "STM32_UsartDriver.h"

#define DATATYPE uint8_t
//˫��ѭ������Ľṹ��
typedef struct CHAIN
{
	DATATYPE data;
	struct CHAIN *last;
	struct CHAIN *next;	
} chain;


//����֪�ڵ�����һ���ڵ�
void insertAfter(DATATYPE,chain *p);


//����֪�ڵ�ǰ����һ���ڵ�
void insertBefore(DATATYPE,chain *p);


//ɾ����̽ڵ㣬��p�ĺ�һ���ڵ�
bool deleteAfter(chain *head,chain *p);


//ɾ��ǰһ���ڵ㣬��p��ǰһ���ڵ�
bool deleteBefore(chain *head,chain *p);


//ɾ���ڵ㱾��
bool deletSelf(chain *head,chain *p);


//����һ��˫��ѭ������
chain * creatChain(uint16_t len);	 


//ɾ��һ��˫��ѭ������
void deleteChain(chain *head);

//bool receiveData(USART_data_t* p_usart_data, uint8_t* pRXD_DATA);

#endif
