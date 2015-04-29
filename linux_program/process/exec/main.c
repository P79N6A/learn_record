/*
 * 调用执行程序
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
	char *const ps_argv[] ={"ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL};
	char *const ps_envp[] ={"PATH=/bin:/usr/bin", "TERM=console", NULL};
	
	//execl("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
	//execv("/bin/ps", ps_argv);
	//execle("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL, ps_envp);
	execve("/bin/ps", ps_argv, ps_envp);
	//execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
	//execvp("ps", ps_argv);
	/* exec只有错误返回值，只要返回了一定是出错了，否则直接执行另个程序那边　*/
	perror("exec ps");
	exit(1);
}
