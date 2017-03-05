/*************************************************************************
	> File Name: fifo.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Fri 17 Feb 2017 02:06:07 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define READ_PATH    "./child_write_fifo"
#define WRITE_PATH   "./child_read_fifo"
#define FILE_MODE    (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(void)
{
	pid_t pid;
	// create if no exist
	if ((mkfifo(READ_PATH, FILE_MODE) < 0) && (errno != EEXIST)) {
		printf("Can't create %s", READ_PATH);
	}
	if ((mkfifo(WRITE_PATH, FILE_MODE) < 0) && (errno != EEXIST)) {
		printf("Can't create %s", WRITE_PATH);
		unlink(READ_PATH);
	}


	pid = fork();
	if (pid < 0) {
		printf("Fork failed");
		exit(1);
	}
	if (pid == 0) {
		printf("Child running\n");
		int status = 0;

		// block here , until other process open write
		int pip_read = open(WRITE_PATH, O_RDONLY);
		// block here , until other process open read
		int pip_write = open(READ_PATH, O_WRONLY);

		if (pip_write != -1)
			write(pip_write, "Child write\n", 12);

		// block and wait
		printf("Child read after writed\n");
		if (pip_read != -1)
			read(pip_read, &status, 1);
		printf("Child get status from Parent %d\n", status);

		close(pip_read);
		close(pip_write);
		exit(1);
	} else {
		printf("Parent running\n");

		int pip_write = open(WRITE_PATH, O_WRONLY);
		int pip_read = open(READ_PATH, O_RDONLY);

		char srt[128];

		// block and wait
		if (pip_read != -1)
			read(pip_read, srt, 12);
			printf("Parent get : %s", srt);

		int status = 20;
		if (pip_write != -1)
			write(pip_write, &status, 1);

		waitpid(pid, &status, 0);
		printf("\nChild %d quit %d\n", pid, status);
		printf("The return code is %d\n", WEXITSTATUS(status));

		close(pip_read);
		close(pip_write);

		// if no one open fifo, sys will delete it
		unlink(READ_PATH);
		unlink(WRITE_PATH);
		exit(0);
	}
}

