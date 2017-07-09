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

	TestMessage message1;
	message1.set_id(1);
	message1.set_passwd("orientlu");

	int length = message1.ByteSize();
	char *ByteBuf = new char[length];
	message1.SerializeToArray(ByteBuf, length);
	printf("SerializeToArray length : %d\n", length);

	TestMessage message2;
	message2.ParseFromArray(ByteBuf, length);
	printf("ID = %ld, paswd = %s\n", message2.id(), message2.passwd().c_str());

	delete [] ByteBuf;

	return 0;
}
