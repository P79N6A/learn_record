/*************************************************************************
 > File Name: test.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Thu 22 Nov 2018 08:24:22 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v;
    for (int i=0; i < 10; ++i) {
        v.push_back(i);
    }
    for(int i=0; i < 10; ++i) {
        cout << v[i] << " ";
    }
    return 0;
}
