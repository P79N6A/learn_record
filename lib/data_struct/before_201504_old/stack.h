//ջ��������
#ifndef _STACK_DEF_2015_
#define _STACK_DEF_2015_

#include "list.h"

//�������� int
typedef List Stack;

//��ʼ��
void stack_init(Stack *stack);

//��������
void stack_push(Stack *stack, int data);

//ȡ�������ջ����
//ջ�շ���NULL
int stack_pop(Stack *stack);

void stack_print(Stack *stack);

void stack_destroy(Stack *stack);
#endif
