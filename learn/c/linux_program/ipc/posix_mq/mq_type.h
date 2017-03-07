/*************************************************************************
	> File Name: mq_type.h
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Tue 07 Mar 2017 11:46:43 AM CST
 ************************************************************************/

#ifndef _MQ_TYPE_H
#define _MQ_TYPE_H

struct mq_msg_t {
	int id;
	char des[128];
};
#endif
