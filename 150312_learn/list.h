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


/*操作函数*/

//链表初始化
//链表存在元素会全部销毁
void list_init(List *list);

//链表头插入元素
void list_insert_head(List *list, int info);

//链表尾插入元素
void list_insert_end(List *list, int info);

//链表销毁
void list_destroy(List *list);

//链表长度
size_t list_length(List *list);

//链表打印
void list_print(List *list);

//链表逆
void list_reverse(List *list);

//链表查找
//有返回 节点地址 ， 无返回-1
Node *list_find(List *list, int info);

//在X节点插入元素
void list_insert_at(Node *ptr_x, int info);

//删除X节点
void list_delete_at(Node *ptr_x);





#endif
