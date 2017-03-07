/*************************************************************************
	> File Name: mq_2.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Tue 07 Mar 2017 11:06:31 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include "mq_type.h"

int main(void)
{
	mqd_t des;
	struct mq_attr arr;

	struct mq_msg_t msg;
	unsigned prio;

	//des = mq_open("/mq_test", O_RDONLY);
	des = mq_open("/mq_test", O_RDONLY | O_CREAT, 0666, NULL);
	if (des == -1) {
		perror("open error");
		exit(-1);
	}
	mq_getattr(des, &arr);

	int i = 0;
	// receive len must set as msgsize !!
	//while (mq_receive(des, (char *)&msg, sizeof(struct mq_msg_t), &prio) != -1) {
	while (mq_receive(des, (char *)&msg, arr.mq_msgsize, &prio) > 0) {
		printf("RCV : prio %d : id %d, %s\n", prio, msg.id, msg.des);

		++i;
		if (i > 12) break;
	}

	// delete mq from system
	mq_unlink("/mq_test");
	mq_close(des);
	printf("--------- Rcv2 process quit\n");
}
