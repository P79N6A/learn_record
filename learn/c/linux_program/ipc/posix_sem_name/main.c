/*************************************************************************
	> File Name: main.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Mon 13 Mar 2017 03:41:57 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */


#define NBUFF    10
#define SEM_MUTEX   "/mutex"
#define SEM_NEMPTY  "/nempty"
#define SEM_NSTORED "/nstored"

static const int nitems = 20; // read only by producer and consumer
struct {
	int buf[NBUFF];
	sem_t *mutex, *nempty, *nstored;
} shared;

void *produce(void*), *consume(void*);

int main(void)
{
	pthread_t tid_produce, tid_consume;
	printf("Start\n");

	shared.mutex = sem_open(SEM_MUTEX, O_CREAT | O_EXCL, 0666, 1);
	shared.nempty = sem_open(SEM_NEMPTY, O_CREAT | O_EXCL, 0666, NBUFF);
	shared.nstored = sem_open(SEM_NSTORED, O_CREAT | O_EXCL, 0666, 0);

	pthread_create(&tid_produce, NULL, produce, "producer");
	pthread_create(&tid_consume, NULL, consume, "consumer");

	pthread_join(tid_produce, NULL);
	pthread_join(tid_consume, NULL);

	sem_unlink(SEM_MUTEX);
	sem_unlink(SEM_NEMPTY);
	sem_unlink(SEM_NSTORED);

	printf("End\n");
	return 0;
}


void *produce(void *arg)
{
	int i;
	for (i = 0; i < nitems; ++i) {
		sem_wait(shared.nempty); // use 1
		sem_wait(shared.mutex);
		shared.buf[i % NBUFF] = i;
		printf("Producer Buff[%d] = %d\n", i, shared.buf[i % NBUFF]);
		sem_post(shared.mutex);
		sem_post(shared.nstored);// new 1
	}
	return NULL;
}


void *consume(void *arg)
{
	int i;
	for (i = 0; i < nitems; ++i) {
		sem_wait(shared.nstored);
		sem_wait(shared.mutex);
		printf("-- Comsumer Buff[%d] = %d\n", i, shared.buf[i % NBUFF]);
		sem_post(shared.mutex);
		sem_post(shared.nempty);
	}
	return NULL;
}

