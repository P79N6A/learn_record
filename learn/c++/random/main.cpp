/*************************************************************************
 > File Name: main.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 05 Dec 2018 07:13:30 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#include "true_random.h"

int main()
{
    common::TrueRandom _random;
    cout << _random.GetUint32() << endl;
    cout << _random.GetUint32(1000, 2000) << endl;
    cout << _random.GetUint32(1000, 2000) << endl;
    cout << _random.GetUint32(1000, 2000) << endl;
    cout << _random.GetUint32(1000, 2000) << endl;

    uint32_t buffer[10];
    _random.GetBuffer(buffer, sizeof(buffer));
    for (int i = 0; i < sizeof(buffer) / sizeof(uint32_t); ++i) {
        cout << buffer[i] << endl;
    }

    //common::TrueRandom _random1 = _random;
    //common::TrueRandom _random2(_random);
    common::TrueRandom _random1;
    cout << _random1.GetUint32() << endl;
    cout << _random1.GetUint32(10, 20) << endl;

    return 0;
}
