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
#include <error.h>
#include "mq_type.h"

int main(void)
{
	mqd_t des;
	struct mq_attr arr;
	unsigned prio;
	struct mq_msg_t msg;
	struct sigevent sigev;
	sigset_t new_mask;
	int signo;
	int count = 0;

	des = mq_open("/mq_test", O_RDONLY | O_NONBLOCK | O_CREAT, 0666, NULL);
	if (des == -1) {
		perror("open error");
		exit(-1);
	}
	mq_getattr(des, &arr);

	sigemptyset(&new_mask);
	sigaddset(&new_mask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &new_mask, NULL); // blcok sig

	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	mq_notify(des, &sigev);

		while (mq_receive(des, (char *)&msg, arr.mq_msgsize, &prio) >= 0) {
			printf("SIG : prio %d : id %d, %s\n", prio, msg.id, msg.des);
			count++;
		}
	while (count < 3) {
		// block wait sig
		printf("block wait\n");
		sigwait(&new_mask, &signo);
		if (signo == SIGUSR1) {
			// before rcv
			mq_notify(des, &sigev);
			while (mq_receive(des, (char *)&msg, arr.mq_msgsize, &prio) >= 0) {
				printf("SIG : prio %d : id %d, %s\n", prio, msg.id, msg.des);
				count++;
			}
			//if (errno != EAGAIN) perror("rcv error");
		}
	}
	mq_unlink("/mq_test");
	mq_close(des);
	printf("--------- Rcv3 wait process quit\n");
	return 0;
}


