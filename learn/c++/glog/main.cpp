/*************************************************************************
 > File Name: main.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Sat 17 Nov 2018 11:23:43 PM CST
 ************************************************************************/

#include<iostream>
#include <glog/logging.h>
#include <gflags/gflags.h>
using namespace std;

void YourFailureFunction()
{
     printf("my \"coredump\"\n");
    // 推出前执行一些
    // exit(1); // 不主动退出，会执行coredump
}

int main(int argc,char* argv[])
{
    //设置log 地址
    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "Hello,GOOGLE! INFO";
    LOG(WARNING) << "Hello,GOOGLE! WARNING";
    LOG(ERROR) << "Hello,GOOGLE! ERROR";
    //LOG(FATAL) << "Hello,GOOGLE! FATAL"; // will coredump

    //CHECK(false) << "glog check falsed!"; // will coredump

    // -DNDEBUG when compile
    DLOG(WARNING) << "Hello, World! is dlog, when ndebug not define";

    google::InstallFailureFunction(&YourFailureFunction);
    LOG(FATAL) << "Hello,GOOGLE! FATAL, trigger my failurefunction";

    printf("end\n");
    return 0;
}
