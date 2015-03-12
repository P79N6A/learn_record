#ifndef _LIST_DEF_2015_
#define _LIST_DEF_2015_

#include <stdlib.h>

/* list's node */
typedef struct node
{
	int info;
	struct node *link;
}Node;

/* list's info */
typedef struct list
{
	Node *head;
	Node *end;
	Node *current;
	size_t length;
}List; 


/*��������*/

//�����ʼ��
//�������Ԫ�ػ�ȫ������
void list_init(List *list);

//����ͷ����Ԫ��
void list_insert_head(List *list, int info);

//����β����Ԫ��
void list_insert_end(List *list, int info);

//��������
void list_destroy(List *list);

//������
size_t list_length(List *list);

//�����ӡ
void list_print(List *list);

//������
void list_reverse(List *list);

//�������
//�з��� �ڵ��ַ �� �޷���-1
Node *list_find(List *list, int info);

//��X�ڵ����Ԫ��
void list_insert_at(Node *ptr_x, int info);

//ɾ��X�ڵ�
void list_delete_at(Node *ptr_x);





#endif
