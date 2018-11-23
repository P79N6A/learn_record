/*************************************************************************
 > File Name: main.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 21 Nov 2018 05:27:41 PM CST
 ************************************************************************/

#include "mother.h"
#include "flag.h"

#include <signal.h>
#include <unistd.h>
#include <sys/file.h>
#include <iostream>
#include <fstream>

#include <gflags/gflags.h>
#include <glog/logging.h>



DECLARE_string(flagfile);

static perf_robot::Mother *g_mother = NULL;

static void sigIntHandler(int signum)
{
    if (g_mother) {
        g_mother->StopLoop();
        LOG(INFO) << "SIGINT, Exit...";
    }
    signal(SIGINT, sigIntHandler);
}

static void save_pid(pid_t pid)
{
    std::ofstream out;
    out.open("./perf.pid", std::ios::out | std::ios::trunc);
    out << pid;
    out.close();
}

int main(int argc, char* argv[])
{
    if (FLAGS_flagfile == "") {
        FLAGS_flagfile = "./perf.flag";
    }
    FLAGS_log_dir = "./log";
    FLAGS_minloglevel = 2; // warning
	google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    pid_t _pid = getpid();

    signal(SIGINT, sigIntHandler);

// write to close socket will rasie
#ifdef SIGPIPE
    signal(SIGPIPE, SIG_IGN);
#endif

    g_mother = new perf_robot::Mother();

    int ret = g_mother->Init(_pid);
    if (ret != 0) {
        LOG(ERROR) << "Init error, code : " << ret;
        fprintf(stderr, "Init error, code %d", ret);

    } else {
        save_pid(_pid);
        ret = g_mother->StartLoop();
        if (ret != 0) {
            LOG(ERROR) << "StartLoop error, code : " << ret;
            fprintf(stderr, "StartLoop, code %d", ret);
        }
    }

    delete g_mother;
    return 0;
}
