//栈操作定义

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

//#define STACK_DEBUG

//初始化
void stack_init(Stack *stack)
{
	assert(stack != NULL);
	list_init(stack);
}


//加入数据
void stack_push(Stack *stack, int data)
{
	assert(stack != NULL);
	list_insert_head(stack, data);
}

//取出最后入栈数据
//栈空返回NULL
int stack_pop(Stack *stack)
{
	assert(stack != NULL);
	int data ;
	if ( list_delete_head(stack, &data) == 1)
		return data;
	else
		return (int)NULL;
}
void  stack_print(Stack *stack)
{
	list_print(stack);
}

void stack_destroy(Stack *stack)
{
	list_destroy(stack);
}

#ifdef STACK_DEBUG
int main()
{

	Stack stack;
	int info;
	stack_init(&stack);

	stack_push(&stack, 1);
	stack_push(&stack, 2);
	stack_push(&stack, 3);
	stack_push(&stack, 4);
	stack_push(&stack, 5);
	stack_push(&stack, 6);
	stack_push(&stack, 7);
	stack_push(&stack, 8);
	stack_push(&stack, 9);
	stack_push(&stack, 10);
	stack_push(&stack, 11);
	stack_push(&stack, 12);

	stack_print(&stack);


	info = stack_pop(&stack);
	printf("pop : %d\n", info);
	
	info = stack_pop(&stack);
	printf("pop : %d\n", info);
	
	info = stack_pop(&stack);
	printf("pop : %d\n", info);

	
	stack_print(&stack);
	
	stack_destroy(&stack);
	return 0;
}

#endif 
