//queue 头文件
#ifndef _QUEUE_DEF_2015
#define _QUEUE_DEF_2015

#include "list.h"

typedef List Queue;

//队列初始化
void queue_init(Queue *pqueue);

//队列加入
//加入到队列尾部
void queue_add(Queue *pqueue, int data);

//出队列
//从队列最前面取出一个数
int queue_out(Queue *pqueue);

//销毁队列
void queue_destroy(Queue *pqueue);

//打印队列
void queue_print(Queue *pqueue);

//队列是否空
int queue_isEmpty(Queue *pqueue);

#endif

