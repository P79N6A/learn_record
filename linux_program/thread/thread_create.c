#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t ntid;

void printids(const char *s)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	printf("%s pid %u tid %u (0x%x) \n", 
		s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}

void *thr_fn(void *arg)
{
	printids(arg);
	return NULL;
}

int main(void)
{
	int err;

	/*		    线程ｉｄ，　线程属性，　线程函数入口，　线程参数*/
	err = pthread_create(&ntid, NULL, thr_fn, "New, thread : ");
	if (err != 0)
	{
		fprintf(stderr, "Cant't create thread ;: %s\n", strerror(err));
		exit(1);
	}
	printids("Main thread : ");
	sleep(1);

	return 0;

}
