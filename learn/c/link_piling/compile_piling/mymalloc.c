/*************************************************************************
 > File Name: mymalloc.c
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Thu 14 Sep 2017 09:42:25 AM CST
 ************************************************************************/
#ifdef COMPILELINK

#include<stdio.h>
#include<malloc.h>

void *mymalloc(size_t size)
{
	void *ptr = malloc(size);
	printf("[debug] malloc size %d\n", (int)size);
	return ptr;
}

void myfree(void *ptr)
{
	free(ptr);
	printf("[debug] free %p\n", ptr);
}

#endif
