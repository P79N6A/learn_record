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


//�����ʼ��
void list_init(List *list);

//����ͷ����Ԫ��
void list_insert_head(List *list, int info);

//����β����Ԫ��
void list_insert_end(List *list, int info);

//��������
void list_destroy(List *list);

//������
size_t list_length(const List *list);

//�����ӡ
void list_print(List *list);

//������
void list_reverse(List *list);

//�������
//�з��� 1�� �޷���-1
//��Ӧ�ڵ��ַ������current��
int list_find(List *list, int info);

//��Ҫ�����Ϻ���
//��current�ڵ�������ڵ�
void list_insert_after(List *list, int info);

//�滻current�ڵ�info
void list_insert_at(List *list, int info);

//ɾ��currentָ�����Ľڵ�
int list_deltet_after(List *list, int *delete_info);

//ɾ�����һ���ڵ�
int list_delete_end(List *list, int *delete_info);

//ɾ����һ���ڵ�
int list_delete_head(List *list, int *delete_info);
#endif
