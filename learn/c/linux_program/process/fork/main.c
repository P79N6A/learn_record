/*
 * fork()¡¡º¯Êı²âÊÔ
 */


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0) {
		perror("Fork failed");
		exit(1);
	}
	// fork here
	if (pid == 0) {
		printf("Child\n");

		exit(1);
	} else {
		printf("Parent\n");

		int status = 0;
		waitpid(pid, &status, 0);
		printf("Child %d quit %d\n", pid, status);
		printf("The return code is %d\n",WEXITSTATUS(status));
		exit(0);
	}
}
