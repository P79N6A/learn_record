/*************************************************************************
 > File Name: insert.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Tue 30 Oct 2018 02:07:02 PM CST
 ************************************************************************/

#include <iostream>
#include <cstddef>
#include <vector>
#include <string>

using namespace std;

void sort_inset(vector<int>::iterator b, vector<int>::iterator e)
{
    if (b >= e ) return;

    for(auto i = b + 1; i != e; ++i) {
        int value = *i;
        for (auto j = i - 1; i >= b; --j) {
            if (*j > value) *(j+1) = *j;
            else {
                *(j+1) = value;
                break;
            }
        }
    }
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
    sort_inset(list.begin(), list.end());
    print_list("after", list);

    vector<int> list1 =  {1};
    print_list("before", list1);
    sort_inset(list1.begin(), list1.end());
    print_list("after", list1);

    vector<int> list2 =  {};
    print_list("before", list2);
    sort_inset(list2.begin(), list2.end());
    print_list("after", list2);

    return 0;
}
