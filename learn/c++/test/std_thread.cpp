/*************************************************************************
 > File Name: std_thread.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Mon 03 Dec 2018 10:28:29 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdexcept>
#include <atomic>
#include <thread>
#include <mutex>

std::mutex mtx;

std::atomic<int> global_counter(0);

void inc_counter(int n) {
    for (int i=0; i<n;++i) ++global_counter; }

void inc_ref(std::atomic<int> &count,  int n) {
    for (int i=0; i<n;++i) ++count; }

struct C : std::atomic<int> {
    C() : std::atomic<int>(0) {}
    void inc_member(int n) {
        for (int i=0; i<n; ++i) fetch_add(1); }
};

void PrintMsg(std::string str) {
    std::cout << str << std::endl;
    sleep(1);
    try {
        std::lock_guard<std::mutex> lck(mtx);
        throw(std::logic_error("throw event"));
    } catch (std::logic_error &e) {
        std::cout << "catch : " << e.what() << std::endl;
    }
    std::lock_guard<std::mutex> lck1(mtx);
}

int main(int argc, char* argv[])
{

{
    std::cout << "--- Test 1" << std::endl;
    std::vector<std::thread> threads;
    for (int i=0; i<10; ++i) {
        threads.push_back(std::thread(inc_counter, 100));
    } // 10 * 100 = 1000

    for (int i=0; i<10; ++i) {
        threads.push_back(std::thread(inc_ref, std::ref(global_counter), 100));
    } // 10 * 100 = 1000 + 1000 = 2000

    C bar;
    for (int i=0; i<10; ++i) {
        threads.push_back(std::thread(&C::inc_member, std::ref(bar), 100));
    }
    for (auto& tr : threads) tr.join();
    std::cout << "global " << global_counter << std::endl;
    std::cout << "bar " << bar << std::endl;
}

{
    std::cout << "--- Test 2" << std::endl;
    std::thread tr(PrintMsg, "threadrun");
    tr.join();
    std::cout << "thread end" << std::endl;
    std::cout << "concurrency " << std::thread::hardware_concurrency() << std::endl;
}
    return 0;
}
