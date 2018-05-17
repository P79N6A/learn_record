/*************************************************************************
	> File Name: time33.cpp
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Sun 13 May 2018 08:55:59 PM PDT
 ************************************************************************/

#include<iostream>
#include<stdint.h>
#include<assert.h>
#include<stdio.h>

//djb hash functional
//time33
//
uint32_t time33(char const *str, int len)
{
	assert(str != NULL);
	assert(len >= 0);
	unsigned long hash = 0;
	for (int i = 0; i < len; ++i) {
		// hash = hash * 33 + str[i]
		// *33 = (32 + 1)
		hash = hash + (hash << 5) + str[i];
	}
	return hash;
}

int main()
{
	const char* aa = "jkfdlsjafkl";
	uint32_t hash_ = time33(aa, sizeof(aa));
	std::cout <<  hash_ << std::endl;
	return 0;
}
