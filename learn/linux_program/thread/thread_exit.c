/*
 *  线程退出操作
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
 *  线程自动return 退出
 */
void *thr_fn1(void *arg)
{
	printf("Thread 1 returning \n");
	return (void*)1;
}


/*
 * 线程自己调用exit退出
 */
void *thr_fn2(void *arg)
{
	printf("Thread 2 exiting\n");
	pthread_exit((void*)2);	
}

void *thr_fn3(void *arg)
{
	while(1)
	{
		printf("Thread 3 writing\n");
		sleep(1);
	}
}

int main(void)
{
	pthread_t tid;
	void *tret;

	pthread_create(&tid, NULL, thr_fn1, NULL);
	/*挂起等待指定线程结束*/
	pthread_join(tid, &tret); 
	printf("Thread 1 exit coide %d\n", (int)tret);

	pthread_create(&tid, NULL, thr_fn2, NULL);
	pthread_join(tid, &tret);
	printf("Thread 2 exit coide %d\n", (int)tret);

	pthread_create(&tid, NULL, thr_fn3, NULL);
	sleep(3);
	/* 其他线程调用cancel结束线程*/
	pthread_cancel(tid);
	pthread_join(tid, &tret);
	printf("Thread 3 exit code :%d\n", (int)tret);

	return 0;
}
