//queue ͷ�ļ�
#ifndef _QUEUE_DEF_2015
#define _QUEUE_DEF_2015

#include "list.h"

typedef List Queue;

//���г�ʼ��
void queue_init(Queue *pqueue);

//���м���
//���뵽����β��
void queue_add(Queue *pqueue, int data);

//������
//�Ӷ�����ǰ��ȡ��һ����
int queue_out(Queue *pqueue);

//���ٶ���
void queue_destroy(Queue *pqueue);

//��ӡ����
void queue_print(Queue *pqueue);

//�����Ƿ��
int queue_isEmpty(Queue *pqueue);

#endif

