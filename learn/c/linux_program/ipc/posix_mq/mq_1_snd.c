/*************************************************************************
	> File Name: mq_1.c
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

int main(int argc, char *argv[])
{
	mqd_t des;
	struct mq_attr arr;
	struct mq_attr narr;

	arr.mq_maxmsg = 9; // my ubuntu max is 10, default
	arr.mq_msgsize = 256;
	des = mq_open("/mq_test", O_WRONLY | O_CREAT/*| O_EXCL*/, 0666, &arr);
	if (des == -1) {
		perror("open error");
		exit(-1);
	}

	if (mq_getattr(des, &arr) != -1) {
		printf("mq flag : %ld\n", arr.mq_flags);
		printf("mq maxmsg : %ld\n", arr.mq_maxmsg);
		printf("mq maxsize : %ld\n", arr.mq_msgsize);
	}

	// can't modify maxmsg after create
	narr = arr;
	narr.mq_maxmsg = 8;
	if (mq_setattr(des, &narr, &arr) == -1) {
		perror("error set attr");
		exit(-1);
	}
	printf("Try to set maxmsg -> 9\n");
	if (mq_getattr(des, &arr) != -1) {
		printf("mq flag : %ld\n", arr.mq_flags);
		printf("mq maxmsg : %ld\n", arr.mq_maxmsg);
		printf("mq maxsize : %ld\n", arr.mq_msgsize);
	}

	int count = atoi(argv[1]);
	struct mq_msg_t msg;
	int i = 0;
	for (i = 0; i < count; ++i) {
		msg.id = i;
		sprintf(msg.des, "this is id %d msg\n", msg.id);
		printf("SEND : %s", msg.des);
		mq_send(des, (const char *)&msg, sizeof(struct mq_msg_t), i);
	}

	// delete mq from system
	//mq_unlink("/mq_test");

	mq_close(des);
	printf("--------- Snd process quit\n");
}
