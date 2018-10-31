/*************************************************************************
 > File Name: min_heap.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Tue 30 Oct 2018 04:52:30 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
#include<functional>

using namespace std;

void print_list(string title, vector<int> &list)
{
    cout << title << ": ";
    for (auto i = list.begin(); i != list.end(); ++i)
        cout << *i << " ";
    cout << endl;
}

bool min_compare(int left, int right)
{
    if (left < right)
        return true;
    else
        return false;
}

// 向下维护heap
void fix_heap_down(vector<int> &heap, int index, int size, function<bool(int, int)> compare)
{
    auto node_index = index * 2 + 1;// default left node index
    while (node_index < size) {

        // set min/max node
        if (node_index + 1 < size && compare(heap[node_index + 1], heap[node_index])) // right node is min_heap
            node_index += 1;

        if (compare(heap[index], heap[node_index]))
            break;// done

        // swap
        int value = heap[index];
        heap[index] = heap[node_index];
        heap[node_index] = value;

        index = node_index;
        node_index = index * 2 + 1;// default left node index
    }
}

//从最底向上建heap
void build_heap(vector<int> &heap, function<bool(int,int)> compare)
{
    // last node index is : size / 2 - 1
    int size = heap.size();
    for (auto i = size/2 - 1; i >= 0; --i) {
        fix_heap_down(heap, i, size, compare);
    }
}

void push_heap(vector<int> &heap, int value)
{
    heap.push_back(value);
    build_heap(heap, min_compare);
}

bool pop_heap(vector<int> &heap, int &value)
{
    if (heap.empty()) return false;
    value = heap[0];
    heap[0] = *(heap.end() - 1);
    heap.pop_back();
    build_heap(heap, min_compare);
}

void heap_sort(vector<int> &heap, function<bool(int, int)>compare)
{
    if (heap.size() <= 0) return;

    auto size = heap.size();
    build_heap(heap, compare);
    for (auto i = heap.size() - 1; i > 0; --i) {
        int tmp = heap[i];
        heap[i] = heap[0];
        heap[0] = tmp;
        fix_heap_down(heap, 0, --size, compare);
    }
}

#include <queue>
template<class T> void print_queue(T& q)
{
    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
}

void test_stl_priority_queue(void)
{
    cout << "--- " << __func__ << " ---" << endl;

    priority_queue<int> q;
    for (int n : {1,8,5,6,3,4,0,9,7,2})
        q.push(n);
    print_queue(q);

    priority_queue<int, vector<int>, greater<int> > q2;
    for (int n : {1,8,5,6,3,4,0,9,7,2})
        q2.push(n);
    print_queue(q2);

    auto cmp = [](int l, int r) {return l < r; };
    priority_queue<int, vector<int>, decltype(cmp)> q3(cmp);
    for (int n : {1,8,5,6,3,4,0,9,7,2})
        q3.push(n);
    print_queue(q3);
}
// stl 算法 ： partial_sort
// 数据量比较多时，无法使用 partial_sort, 内存不够
// 获取topN, 优先队列n，循环读取所有，小于堆顶丢弃，大于弹出堆顶替换，最后剩余就是topN

int main(void)
{
    vector<int> heap = {99, 5, 36, 7 , 22, 17, 92, 12, 2, 19, 25,28,1,46};
    //vector<int> heap = {};
    print_list("before", heap);
    build_heap(heap, min_compare);
    cout << "expect heap: " << "1 2 17 5 19 28 46 12 7 22 25 99 36 92" << endl;
    print_list("after build", heap);

    //heap_sort(heap, min_compare);
    //print_list("after sort", heap);

    int value;
    do {
        pop_heap(heap, value);
        cout << value << endl;
    } while (!heap.empty());

    cout << "remain : "  << heap.size() << endl;

    test_stl_priority_queue();
}

