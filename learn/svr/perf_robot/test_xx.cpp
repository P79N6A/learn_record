/*************************************************************************
 > File Name: test_flag.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Sat 17 Nov 2018 05:07:46 PM CST
 ************************************************************************/

#include<iostream>
#include <gflags/gflags.h>

DECLARE_string(flagfile);

DEFINE_bool(is_test, true, "is test");
DEFINE_string(server_ip, "127.0.0.1","server ip");
DEFINE_int32(server_port, 8888,"server port");


using namespace std;

static bool CheckServerPort(const char *name, int32_t port)
{
    if (port > 1024 && port < 32768) {
        return true;
    }
    printf("Invalid port : %d\n", port);
    return false;
}

int main(int argc, char* argv[])
{
    // set check flag fun
    gflags::RegisterFlagValidator(&FLAGS_server_port, &CheckServerPort);

    //read flag File
    //gflags::ReadFromFlagsFile();
    if (FLAGS_flagfile == "") {
        // before ParseCommandLineFlags
        FLAGS_flagfile = "./perf.flag";
    }

    //parse flag
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    cout << "isTest : " << FLAGS_is_test << endl;
    cout << "ServerIP : "  << FLAGS_server_ip << endl;
    cout << "ServerPort : "  << FLAGS_server_port << endl;

    // set flag
    //string new_port = "1";
    string new_port = "7777";
    cout << "Set port : " <<  new_port << endl;
    gflags::SetCommandLineOption("server_port", new_port.c_str());

    cout << "isTest : " << FLAGS_is_test << endl;
    cout << "ServerIP : "  << FLAGS_server_ip << endl;
    cout << "ServerPort : "  << FLAGS_server_port << endl;
    return 0;
}
