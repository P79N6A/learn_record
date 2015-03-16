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


//链表初始化
void list_init(List *list);

//链表头插入元素
void list_insert_head(List *list, int info);

//链表尾插入元素
void list_insert_end(List *list, int info);

//链表销毁
void list_destroy(List *list);

//链表长度
size_t list_length(const List *list);

//链表打印
void list_print(List *list);

//链表逆
void list_reverse(List *list);

//链表查找
//有返回 1， 无返回-1
//对应节点地址保存在current中
int list_find(List *list, int info);

//需要调用上函数
//在current节点后面插入节点
void list_insert_after(List *list, int info);

//替换current节点info
void list_insert_at(List *list, int info);

//删除current指向后面的节点
int list_deltet_after(List *list, int *delete_info);

//删除最后一个节点
int list_delete_end(List *list, int *delete_info);

//删除第一个节点
int list_delete_head(List *list, int *delete_info);
#endif
