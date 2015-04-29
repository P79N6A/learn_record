/*
 * 互斥锁，操作原子性
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define  NLOOP 5000

int counter;   /*全局变量，共享*/
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;  /*初始化互斥锁*/

void *doit(void *); //进程程序

int main(int argc, char *argv[])
{
	pthread_t tidA, tidB;

	pthread_create(&tidA, NULL, doit, NULL);
	pthread_create(&tidB, NULL, doit, NULL);

	/*等待线程结束，释放*/
	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);


	return 0;
}

void *doit(void *vptr)
{
	int i, val;

	/*
	 * Each thread fetches, prints, and increments the counter NLOOP times.
	 * Ther value of the counter should increase monotonically.
	*/

	for (i = 0; i < NLOOP; ++i)
	{
		pthread_mutex_lock(&counter_mutex);

		val = counter;
		printf("%x %d \n", (unsigned int)pthread_self(), val+1);
		counter = val + 1;
		pthread_mutex_unlock(&counter_mutex);
	}
	return NULL;
}

