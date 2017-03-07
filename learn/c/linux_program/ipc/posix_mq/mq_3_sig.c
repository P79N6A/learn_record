/*************************************************************************
	> File Name: mq_3.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Tue 07 Mar 2017 11:06:31 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <signal.h>

#include "mq_type.h"

static struct sigevent sigev;
static struct mq_attr arr;
static struct mq_msg_t msg;
static unsigned prio;
static mqd_t des;

static int count = 0;

void handle_sigusr1(int sig)
{
	// before rcv
	mq_notify(des, &sigev);
	// can write pip, so we can use select/epoll to read 
	while (mq_receive(des, (char *)&msg, arr.mq_msgsize, &prio) >= 0) {
		printf("SIG : prio %d : id %d, %s\n", prio, msg.id, msg.des);
		count++;
	}
}

int main(void)
{
	des = mq_open("/mq_test", O_RDONLY | O_NONBLOCK | O_CREAT, 0666, NULL);
	if (des == -1) {
		perror("open error");
		exit(-1);
	}
	mq_getattr(des, &arr);

	signal(SIGUSR1, handle_sigusr1);

	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	mq_notify(des, &sigev);

	while (count < 3)
		pause();

	mq_unlink("/mq_test");
	mq_close(des);
	printf("--------- Rcv3 process quit\n");
}


