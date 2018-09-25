/*************************************************************************
 > File Name: dynamic.c
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Tue 25 Sep 2018 07:47:55 PM CST
 ************************************************************************/

#include <stdio.h>
#include "static.h"

void print_papa_said()
{
    print_niuzai_said();
    printf("in dynamic lib, papa said, niu zai is wonderful!\n");
}

