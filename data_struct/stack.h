//栈操作定义
#ifndef _STACK_DEF_2015_
#define _STACK_DEF_2015_

#include "list.h"

//数据类型 int
typedef List Stack;

//初始化
void stack_init(Stack *stack);

//加入数据
void stack_push(Stack *stack, int data);

//取出最后入栈数据
//栈空返回NULL
int stack_pop(Stack *stack);

void stack_print(Stack *stack);

void stack_destroy(Stack *stack);
#endif
