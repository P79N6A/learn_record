/*************************************************************************
	> File Name: lock.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Thu 09 Mar 2017 03:06:28 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

static char f_state[3][12] = {"F_RDLCK", "F_WRLCK", "F_UNLCK"};

int main(void)
{
	int fd = open("./lock_test.out", O_RDWR | O_CREAT, 0644);
	if (fd < 0)
	{
		perror("open error\n");
		exit(-1);
	}

	struct flock flk;
	memset(&flk, 0, sizeof(struct flock));
	flk.l_type = F_RDLCK;
	flk.l_whence = SEEK_SET;
	flk.l_start = 0;
	flk.l_len = 5;

	if (fcntl(fd, F_GETLK, &flk) < 0) {
		exit(-1);
	}
	printf("Get state : before lock %s\n", f_state[flk.l_type]);

	// set read lock, no block
	flk.l_type = F_RDLCK;
	if (fcntl(fd, F_SETLK, &flk) < 0) {
		exit(-1);
	}

	if (fcntl(fd, F_GETLK, &flk) < 0) {
		exit(-1);
	}
	printf("Get state : after lock %s\n", f_state[flk.l_type]);
	printf("--> My lock not lock me\n");

	// now is lock read
	printf("Fork a new process\n\n");
	pid_t pid = fork();
	if (pid < 0) {
		exit(-1);
	} else if (pid == 0) {
		printf("-- Chile runing\n");
		printf("-- Chile block get lock\n");
		flk.l_type = F_WRLCK;
		if (fcntl(fd, F_SETLKW, &flk) < 0) {
			perror("Child set lock error\n");
			exit(-1);
		}
		printf("-- Child set write lock sleep 2\n");
		sleep(2);
		printf("-- Child quit lock releare auto\n\n");
	} else {
		printf("Parent sleep 2s\n");
		sleep(2);
		printf("Parent wakeup and unlock\n");
		flk.l_type = F_UNLCK;
		if (fcntl(fd, F_SETLK, &flk) < 0) {
			perror("parent set error\n");
			exit(-1);
		}
		sleep(1);

		flk.l_type = F_RDLCK;
		// flk.l_type = F_UNLCK; // set this, ocur a error
		// flk.l_type = F_WRLCK;
		if (fcntl(fd, F_GETLK, &flk) < 0) {
			perror("xx parent get lock state error");
			exit(-1);
		}
		printf("Parent get state : %s\n", f_state[flk.l_type]);

		printf("Parent block get lock\n");
		flk.l_type = F_RDLCK;
		if (fcntl(fd, F_SETLKW, &flk) < 0) {
			exit(-1);
		}
		printf("Parent set read lock\n");

			wait();
		printf("Parent quit\n");
	}
	close(fd);
	return 0;
}
