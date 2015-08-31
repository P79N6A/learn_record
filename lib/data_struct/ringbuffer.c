/*************************************************************************
	> File Name: ringbuffer.c
	> Author: luchaodong
	> Mail: luchaodong@meizu.com
	> Created Time: 2015年08月10日 星期一 09时57分52秒
 ************************************************************************/

#define  RING_BUFFER_TEST 1

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef unsigned char uint8;


#define RING_BUFFER_LEN  20 // per unit byte
/*---------------------------------------------------------
* |length : n | data[0]| data[1]| ... | ... |  data[n-1] |
* ---------------------------------------------------------*/
#define RING_BUFFER_DEEP 20 // how many units

static uint8 ring_buffer[RING_BUFFER_DEEP][RING_BUFFER_LEN+1];
static uint8 ring_buffer_head = 0;;
static uint8 ring_buffer_tail = 0;


/*
 * ring_buffer_reset
 * 清除缓冲区数据，恢复初始化
 * */
void ring_buffer_reset( void ) 
{
    uint8 i;
    for (i = 0; i < RING_BUFFER_DEEP; ++i)  ring_buffer[i][0] = 0;
    
    ring_buffer_head = 0;
    ring_buffer_tail = 0;
}


/*
 * ring_buffer_push
 * 数据推入队列中尾部
 * Input
 * @para uint8 *data: 数据指向
 * @para uint8 length：数据长度  
 * */
void ring_buffer_push( uint8 const *data, uint8 length )
{
    if ( data == NULL || length == 0 ) return;
    
    length = ( length > RING_BUFFER_LEN )?RING_BUFFER_LEN : length;
    /**
    * push 很快覆盖了还未发送的缓冲区
    * 保证pop 出去的数据是最旧的　*/
    if (ring_buffer_head == ring_buffer_tail && ring_buffer[ring_buffer_head][0] != 0) {
        ++ring_buffer_tail;
        if (ring_buffer_tail == RING_BUFFER_DEEP) ring_buffer_tail = 0;
    }

    ring_buffer[ring_buffer_head][0] = length;
    memcpy( &ring_buffer[ring_buffer_head][1], data, length );

    ++ring_buffer_head;
    if (ring_buffer_head == RING_BUFFER_DEEP) ring_buffer_head = 0;
}

 /*
  * ring_buffer_pop
  * 从队列首部取出数据
  * Input
  * @para uint8 *data: 取出数据保存地址
  * @para uint8 *length: 取出数据长度
  * Outout
  * 1 get message successful  ： 0 Error 
  * */
uint8 ring_buffer_pop( uint8 *data, uint8 *length )
{
    if ( data == NULL ) return 0;
    if ( ring_buffer[ring_buffer_tail][0] == 0 )  return 0;
    
    *length = ring_buffer[ring_buffer_tail][0];
    ring_buffer[ring_buffer_tail][0] = 0; // clean
    memcpy( data, &ring_buffer[ring_buffer_tail][1], (*length) );
    
    ++ring_buffer_tail;
    if (ring_buffer_tail == RING_BUFFER_DEEP) ring_buffer_tail = 0;
    return 1;
}


/*********************************************************************************/
#if RING_BUFFER_TEST
uint8 counter = 0;

#include <pthread.h>
#include <unistd.h>

void *push_buffer(void* arg)
{
    while (1) {
        uint8 data[12] = "Hello world";
        data[11] = counter++;
        ring_buffer_push(data, 12);
        usleep(500000); //us
   }
}


void *pop_buffer(void* arg )
{
    while (1) {
        uint8 data[6];
        uint8 len;
        uint8 cou;
        if (ring_buffer_pop(data, &len) != 0) {
            cou = data[11];
            data[11] = 0;
            printf("%s%d len:%d\n", data, cou, len);
        } else {
            printf("Buffer empty\n");
        }
        usleep(1000000); //us
    }
}

int main(void)
{
    pthread_t p1, p2;
    pthread_create(&p1, NULL, push_buffer, NULL);
    pthread_create(&p2, NULL, pop_buffer, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return 0;
}

#endif 


