
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

//#define QUEUE_DEBUG

//���г�ʼ��
void queue_init(Queue *pqueue)
{
	assert(pqueue != NULL);
	list_init(pqueue);
}

//���м���
//���뵽����β��
void queue_add(Queue *pqueue, int data)
{
	assert(pqueue != NULL);
	list_insert_end(pqueue, data);
}

//������
//�Ӷ�����ǰ��ȡ��һ����
int queue_out(Queue *pqueue)
{
	int data; 
	assert( pqueue != NULL);
	if (list_delete_head(pqueue, &data) == 1)
		return data;
	else 
		return -1;
}

//���ٶ���
void queue_destroy(Queue *pqueue)
{
	assert( pqueue != NULL);
	list_destroy(pqueue);
}

//��ӡ����
void queue_print(Queue *pqueue)
{
	list_print(pqueue);
}

//�����Ƿ��
int queue_isEmpty(Queue *pqueue)
{
	return (list_length(pqueue) == 0);
}

#ifdef QUEUE_DEBUG

int main()
{
	int data;
	Queue queue;

	queue_init(&queue);

	queue_add(&queue, 1);
	queue_add(&queue, 2);
	queue_add(&queue, 3);
	queue_add(&queue, 4);
	queue_add(&queue, 5);
	queue_add(&queue, 6);
	queue_add(&queue, 7);
	queue_add(&queue, 8);
	queue_add(&queue, 9);
	queue_add(&queue, 10);

	queue_print(&queue);

	while ( !queue_isEmpty(&queue) ) 
	{
		data = queue_out(&queue);
		printf("%d\t", data);
	}

	printf("\n");

	queue_print(&queue);
	queue_destroy(&queue);
	return 0;

}

#endif

