//���ԣ�����main
//lcd 20150312

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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
void list_init(List *list)
{
	assert(list != NULL);

	list->head = NULL;
	list->end = NULL;
	list->current = NULL;
	list->length = 0;
}

//����ͷ����Ԫ��
void list_insert_head(List *list, int info)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("Malloc faile\n");
		return;
	}
	newNode->info = info;
	newNode->link = list->head;
	
	list->head = newNode;
	if (list->end == NULL) list->end = newNode; //���б�
	
	++list->length;
}

//����β����Ԫ��
void list_insert_end(List *list, int info)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("Malloc faile\n");
		return;
	}
	newNode->info = info;
	newNode->link = NULL;

	if (list->end == NULL) 
		list->head = newNode;
	else 
		list->end->link = newNode;

	list->end = newNode;
	++list->length;
}

//��������
void list_destroy(List *list)
{
	assert(list != NULL);

	while (list->head != NULL)
	{	
		list->current = list->head;
		list->head = list->head->link; //next one
		free(list->current);
	}

	list->end = NULL;
	list->current = NULL;
	list->length = 0;
}


//������
size_t list_length(const List *list)
{
	return list->length;
}

//�����ӡ
void list_print(List *list)
{
	assert(list != NULL);
	list->current = list->head;
	printf("List-head-->");
	while(list->current != NULL)
	{
		printf("%d --->", list->current->info);
		list->current = list->current->link; //nextONE
	}

	printf("NULL\n");
}


//������
void list_reverse(List *list)
{
	Node *next;
	Node *r = NULL;
	Node *current = list->head;
	
	assert(list != NULL);
	
	list->head = list->end;
	list->end = current;
	
	while(current != NULL)
	{
		next = current->link; //next one
		current->link = r;
		r = current;
		current = next;
	}

}

//�������
//�з��� 1�� �޷���-1
//��Ӧ�ڵ��ַ������current��
int list_find(List *list, int info)
{
	int isfind = -1;
	assert(list != NULL);

	list->current = list->head;
	while (list->current != NULL)
	{
		if (list->current->info != info)
		{
			list->current = list->current->link;
		}
		else
		{
			isfind = 1;
			break;
		}
	}

	return isfind;
}

//��Ҫ�����Ϻ���
//��current�ڵ�������ڵ�
void list_insert_after(List *list, int info)
{
	Node *newNode = NULL;
	
	assert(list != NULL && list->current != NULL);	
	
	newNode = (Node *)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("Malloc faile\n");
		return;
	}
	newNode->info = info;
	newNode->link = list->current->link;

	list->current->link = newNode;
	if (list->current == list->end) list->end = newNode;
	++list->length;
}

//�滻current�ڵ�info
void list_insert_at(List *list, int info)
{
	assert(list != NULL && list->current != NULL);

	list->current->info = info;
}

//ɾ��currentָ�����Ľڵ�
int list_deltet_after(List *list, int *delete_info)
{
	Node *next = NULL;

	assert(list != NULL && list->current != NULL);

	if ( (next = list->current->link) != NULL)
	{
		list->current->link = next->link;
		if (next == list->end) list->end = list->current;
		*delete_info = next->info;
		free(next);
		--list->length;
		return 1;
	}
	else
	{
		printf("try to delete NULL\n");
		return -1;
	}
}

//ɾ�����һ���ڵ�
int list_delete_end(List *list, int *delete_info)
{
	assert(list != NULL);
	list->current = list->head;
	
	if (list->current == NULL)
	{
		printf("list is empty\n");
		return -1;
	}
	else if (list->head == list->end)
	{
		*delete_info = list->end->info;
		free(list->end);
		list->head = NULL;
		list->end = NULL;
	}
	else
	{
		while (list->current->link != list->end) list->current = list->current->link;
		
		*delete_info = list->end->info;
		free(list->end);
		list->current->link = NULL;
		list->end = list->current;
	}

	--list->length;
	return 1;
}

//ɾ����һ���ڵ�
int list_delete_head(List *list, int *delete_info)
{	
	Node *temp;
	assert(list != NULL);
	if (list->head == NULL)
	{
		printf("list is empty");
		return -1;
	}
	else
	{
		temp = list->head;
		list->head = list->head->link;

		if (temp == list->end) list->end = list->head;

		*delete_info = temp->info;
		free(temp);
		--list->length;
	}
	return 1;
}

int main()
{
//for text list
	List list;
	int a;

	list_init(&list);

	list_insert_head(&list, 2);
	list_insert_head(&list, 1);
	list_insert_end(&list, 3);

	list_print(&list);
	printf("length %d\n", list_length(&list));
	
	list_reverse(&list);
	list_print(&list);
	printf("length %d\n", list_length(&list));

	list_insert_end(&list, 4);
	list_insert_end(&list, 5);
	list_insert_end(&list, 6);

	if (list_find(&list, 6) == 1)
	{
		list_insert_after(&list, 7);
		list_deltet_after(&list, &a);
		printf("Delete %d\n", a);
	}
	else
	{
		printf("no\n");
	}
	list_print(&list);
	printf("length %d\n", list_length(&list));

	list_delete_head(&list, &a);
	printf("Delete %d\n", a);
	list_print(&list);
	printf("length %d\n", list_length(&list));
	
	list_delete_end(&list, &a);
	printf("Delete %d\n", a);
	list_print(&list);
	printf("length %d\n", list_length(&list));
	
	list_destroy(&list);
	list_print(&list);
	printf("length %d\n", list_length(&list));
	
	return 0;	
}


