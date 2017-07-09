/*************************************************************************
> File Name: main.cpp
> Author: orientlu
> Mail: lcdsdream@126.com
> Created Time: Fri 07 Jul 2017 06:54:12 AM PDT
************************************************************************/

#include<iostream>
#include<string>
#include"message.pb.h"

using namespace std;

int main(int argc, char *argv[])
{
	printf("=============================== This is simple test =================================\n");
	LogonRespMessage logonResp;
	logonResp.set_logonresult(LOGON_RESULT_SUCCESS);
	UserInfo *userInfo = logonResp.mutable_userinfo();
	userInfo->set_acctid(2);
	userInfo->set_name("Tester");
	userInfo->set_status(OFFLINE);

	int length = logonResp.ByteSize();
	char *buf = new char[length];
	logonResp.SerializeToArray(buf, length);

	LogonRespMessage logonResp2;
	logonResp2.ParseFromArray(buf, length);
	printf("LogonResult = %d, UserInfo->acctID = %ld,\
	UserInfo->name = %s, UserInfo->status = %d\n",\
	logonResp2.logonresult(),logonResp2.userinfo().acctid(),logonResp2.userinfo().name().c_str(),logonResp2.userinfo().status());
	delete [] buf;
	return 0;
}
