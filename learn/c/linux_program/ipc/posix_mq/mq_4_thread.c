/*************************************************************************
	> File Name: mq_4.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Tue 07 Mar 2017 11:06:31 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <pthread.h>
#include <errno.h>

#include "mq_type.h"

static struct sigevent sigev;
static struct mq_attr arr;
static struct mq_msg_t msg;
static unsigned prio;
static mqd_t des;

static int count = 0;

static void notify_thread(union sigval arg)
{
	mq_notify(des, &sigev);
	// can write pip, so we can use select/epoll to read 
	while (mq_receive(des, (char *)&msg, arr.mq_msgsize, &prio) >= 0) {
		printf("Process: prio %d : id %d, %s\n", prio, msg.id, msg.des);
		count++;
	}
	if (errno != EAGAIN) perror("rcv error");

	pthread_exit(NULL);
}

int main(void)
{
	des = mq_open("/mq_test", O_RDONLY | O_NONBLOCK | O_CREAT, 0666, NULL);
	if (des == -1) {
		perror("open error");
		exit(-1);
	}
	mq_getattr(des, &arr);

	sigev.sigev_notify = SIGEV_THREAD;
	sigev.sigev_value.sival_ptr = NULL;
	sigev.sigev_notify_function = notify_thread;
	sigev.sigev_notify_attributes = NULL;
	mq_notify(des, &sigev);

	while (count < 3)
		pause();

	mq_unlink("/mq_test");
	mq_close(des);
	printf("--------- Rcv4 process quit\n");
	return 0;
}


