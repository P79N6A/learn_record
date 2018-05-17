/*************************************************************************
	> File Name: main.cpp
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Sun 13 May 2018 07:34:27 PM PDT
 ************************************************************************/

// use token to limit flow 
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>

#define LIMIT_FLOW_MAX_SPEED 50 // 100QPS
#define LIMINT_FLOW_SPEED 10	// 10QPS


int token_bucket = 0;
time_t produce_time = 0;

bool get_token()
{
	if (LIMIT_FLOW_MAX_SPEED != token_bucket) {
		int tokens = 0;
		if (0 == produce_time) {
			produce_time = time(0);
			tokens = LIMINT_FLOW_SPEED;
		} else {
			time_t cur_time = time(0);
			tokens = (cur_time - produce_time) * LIMINT_FLOW_SPEED;
			if (tokens > 0) {
				produce_time = cur_time;
			}
		}

		token_bucket = token_bucket + tokens;
		if (token_bucket > LIMIT_FLOW_MAX_SPEED) {
			token_bucket = LIMIT_FLOW_MAX_SPEED;
		}
	}
	if (token_bucket == 0) {
		return false;
	}
	--token_bucket;
	return true;
}

int main()
{
	get_token();
	usleep(1000000 * 11);
	for (size_t i = 0; i < 111; ++i) {
		if (get_token()) {
			std::cout << "run" << std::endl;
		} else {

			std::cout << "wait" << std::endl;
		}
	}
}
