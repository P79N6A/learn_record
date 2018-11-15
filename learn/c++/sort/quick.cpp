/*************************************************************************
 > File Name: quick.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Tue 30 Oct 2018 02:07:02 PM CST
 ************************************************************************/

#include <iostream>
#include <cstddef>
#include <vector>
#include <string>

using namespace std;

void qsort(vector<int>::iterator b, vector<int>::iterator e)
{
    if (b >= e) return;
    vector<int>::iterator i = b;
    vector<int>::iterator j = e - 1;
    int value = *i;
    while (i < j) {
        while (*j > value && i < j) --j;

        if (*j < value && i < j) *i++ = *j;

        while (*i <= value && i < j) ++i;

        if (*i >= value && i < j) *j-- = *i;
    }
    *i = value;
    qsort(b, i);
    qsort(i + 1, e);
}

void print_list(string title, vector<int> &list)
{
    cout << title << ": ";
    for (auto i = list.begin(); i != list.end(); ++i)
        cout << *i << " ";
    cout << endl;
}

int main()
{
    vector<int> list =  {1, 5, 6, 3, 2, 4, 10, 9, 10};
    print_list("before", list);
    qsort(list.begin(), list.end());
    print_list("after", list);

    vector<int> list1 =  {1};
    print_list("before", list1);
    qsort(list1.begin(), list1.end());
    print_list("after", list1);

    vector<int> list2 =  {};
    print_list("before", list2);
    qsort(list2.begin(), list2.end());
    print_list("after", list2);

    return 0;
}
