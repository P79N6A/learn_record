/*************************************************************************
 > File Name: malloc.h
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Thu 14 Sep 2017 09:41:10 AM CST
 ************************************************************************/

#ifndef _MALLOC_H
#define _MALLOC_H

#define malloc(size) mymalloc(size)
#define free(ptr) myfree(ptr)
void *mymalloc(size_t size);
void myfree(void *ptr);
#endif
