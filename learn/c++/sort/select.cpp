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

void sort(vector<int>::iterator b, vector<int>::iterator e)
{
    if (b >= e) return;
    for (auto i = b; i != e; ++i) {
        auto min = i;
        for (auto j = i + 1; j != e; ++j) {
            if (*min > *j) min = j;
        }
        int tmp = *i;
        *i = *min;
        *min = tmp;
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
    sort(list.begin(), list.end());
    print_list("after", list);

    vector<int> list1 =  {1};
    print_list("before", list1);
    sort(list1.begin(), list1.end());
    print_list("after", list1);

    vector<int> list2 =  {};
    print_list("before", list2);
    sort(list2.begin(), list2.end());
    print_list("after", list2);

    return 0;
}
