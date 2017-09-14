/*************************************************************************
 > File Name: mymalloc.c
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Thu 14 Sep 2017 09:42:25 AM CST
 ************************************************************************/
#ifdef RUNTIME
#define _GNU_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>

void *malloc(size_t size)
{
	void *(*mallocp)(size_t size);
	char *error;
	// 查找标准库的实现
	mallocp = dlsym(RTLD_NEXT, "malloc");
	if ((error = dlerror()) != NULL) {
		fputs(error, stderr);
		exit(1);
	}
	void *ptr = mallocp(size);
	printf("[debug] malloc size %d\n", (int)size);
	return ptr;
}

void free(void *ptr)
{
	void (*freep)(void *ptr);
	char *error;
	freep = dlsym(RTLD_NEXT, "free");
	if ((error = dlerror()) != NULL) {
		fputs(error, stderr);
		exit(1);
	}
	freep(ptr);
	printf("[debug] free %p\n", ptr);
}

#endif
