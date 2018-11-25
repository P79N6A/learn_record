/*************************************************************************
 > File Name: test.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Thu 22 Nov 2018 08:24:22 PM CST
 ************************************************************************/
#include<iostream>
#include <vector>
#include <unistd.h> // timeval
#include <sys/time.h> //gettimeofday
#include <chrono> // time
#include <iomanip> // cout　设置输出精度

using namespace std;

int main()
{
    cout << "Vector test" << endl;
    vector<int> v;
    for (int i=0; i < 10; ++i) {
        v.push_back(i);
    }
    for(int i=0; i < 10; ++i) {
        cout << v[i] << " ";
    }
    cout << endl;

    cout << "Time test" << endl;
    std::chrono::steady_clock::time_point t1, t2;
    std::chrono::duration<double> time_span;

    t1 = std::chrono::steady_clock::now();
    cout << "sleep 1s" << endl;
    sleep(1);
    t2 = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout <<fixed<<setprecision(9)<< "It take "<< time_span.count() << endl;

    cout << "Get us" << endl;
    t1 = std::chrono::steady_clock::now();
    std::chrono::microseconds us = std::chrono::duration_cast< std::chrono::microseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );

    t2 = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << us.count() << std::endl;
    std::cout <<fixed<<setprecision(9)<< "It take "<< time_span.count() << endl;


    cout << "Get ms" << endl;
    std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    std::cout << ms.count() << std::endl;


    cout << "Get us via timeval" << endl;
    t1 = std::chrono::steady_clock::now();
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long int tus = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
    t2 = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    cout << tus << endl;
    std::cout <<fixed<<setprecision(9)<< "It take "<< time_span.count() << endl;
    long span_us = time_span.count() * 1000 * 1000 * 1000;
    cout << span_us << "ns" << endl;
    return 0;
}
