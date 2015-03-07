/* define list */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int (*COMPARE)(void*, void*);


//define the node of list
typedef struct _node
{
	void *data;
	struct _node *next;
}Node;

//define a list's pointers struct
typedef struct _linkedList
{
	Node *head;
	Node *tail;
	Node *current;
	unsigned int length;
}LinkedList;


void initializeList(LinkedList*);
void addHead(LinkedList*, void*);
void addTail(LinkedList*, void*);
void deleteNode(LinkedList*, void*);
Node *getNode(LinkedList*, COMPARE, void*);
void displayLinekedList(LinkedList*);

int compare(void*, void*);

int main()
{
	LinkedList thisList; 

	//初始化结构体
	
	
	return 0;
}

/**
 * 初始化定义的链表结构体成员
*/
void initializeList(LinkedList *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
	length = 0;
}


void addHead(LinkedList *list, void *info)
{
	Node *newNode = (Node*) malloc(sizeof(Node));
	newNode->data = info;

	if (list->head == NULL)
	{
		list->tail = newNode;
		newNode->next = NULL;
	}
	else
	{
		newNode->next = lis->head;
	}
	list->head = newNode;
	++length;
}


void addTail(LinkedList *list, void *info)
{
	Node *newNode = (Node*) malloc(sizeof(Node));
	newNode->data = info;
	newNode->next = NULL;

	if (list->head == NULL)
	{
		list->head = newNode;
	}
	else
	{
		list->tail->next = newNode;
	}
	list->tail = newNode;
	++length;
}


void deleteNode(LinkedList *list, void *info)
{
	
}


Node *getNode(LinkedList *list, COMPARE compare, void *info)
{

}

void displayLinekedList(LinkedList *list)
{

}



