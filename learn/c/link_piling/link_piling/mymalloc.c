/*************************************************************************
 > File Name: mymalloc.c
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Thu 14 Sep 2017 09:42:25 AM CST
 ************************************************************************/
#ifdef LINKTIME

#include<stdio.h>
#include<malloc.h>

//std malloc
void *__real_malloc(size_t size);
void __real_free(void *ptr);

void *__wrap_malloc(size_t size)
{
	void *ptr = __real_malloc(size);
	printf("[debug] malloc size %d\n", (int)size);
	return ptr;
}

void __wrap_free(void *ptr)
{
	__real_free(ptr);
	printf("[debug] free %p\n", ptr);
}

#endif
