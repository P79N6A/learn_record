/*************************************************************************
 > File Name: std_sort.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Fri 24 Aug 2018 04:54:02 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


// 1 为何 sort(s, e, compare_greater_obj) 不需要后带括号，因为他是定义的对象了。
// sort 传递一个函数对象，  sort(s, e,type())
//// 定义了一个对象，       sort(s, e, obj)
struct CompareGreater {
    bool operator()(const int &left, const int &right)
    {
        return left > right;
    }
} compare_greater_obj;

class CompareLess {
    public:
        bool operator()(const int &left, const int &right)
        {
            return left < right;
        }
} ;

class CompareGreaterEqual {
    public:
        bool operator()(const int &left, const int &right)
        {
            return left >= right;
        }
} ;

class CompareGreaterP {
    public:
        bool operator()(const int* left, const int* right)
        {
            return *left > *right;
        }
};

class CompareGreaterEqualP {
    public:
        bool operator()(const int* left, const int* right)
        {
            return *left >= *right;
        }
};

struct TestObj {
    TestObj(int a) : m_val(a) 
    {
        //printf("TestObj constructor val : %d\n", m_val);
    }
    TestObj(const TestObj &a) : m_val(a.m_val)
    {
        //printf("TestObj constructor copy val : %d\n", m_val);
    }
    int m_val;
};

class CompareTestGreater {
    public:
        bool operator()(const TestObj &left, const TestObj &right)
        {
            return left.m_val > right.m_val;
        }
};

class CompareTestGreaterEqual {
    public:
        bool operator()(const TestObj &left, const TestObj &right)
        {
            return left.m_val >= right.m_val;
        }
};


class CompareTestGreaterP {
    public:
        bool operator()(const TestObj *left, const TestObj *right)
        {
            return left->m_val > right->m_val;
        }
};

class CompareTestGreaterEqualP {
    public:
        bool operator()(const TestObj *left, const TestObj *right)
        {
            return left->m_val >= right->m_val;
        }
};


int main(int argc, char *argv[])
{
    cout << "-----------------------------" << endl;
    cout << "--> sort for type int" << endl;
    vector<int> a{1,2,3,4,9,5,6,2};

    sort(a.begin(), a.end());
    cout << "sort, default : ";
    for (int s : a)
        cout << s;
    cout << endl;

    sort(a.begin(), a.end(), greater<int>());
    cout << "sort, std::greater : ";
    for (int s : a)
        cout << s;
    cout << endl;

    sort(a.begin(), a.end(), compare_greater_obj);
    sort(a.begin(), a.end(), CompareGreater());
    cout << "sort, self def greater : ";
    for (int s : a)
        cout << s;
    cout << endl;

    sort(a.begin(), a.end(), CompareLess());
    cout << "sort, self def less : ";
    for (int s : a)
        cout << s;
    cout << endl;

    cout << endl;
    cout << "--> sort for type int (cmp(x,x) return true)" << endl;
    vector<int> b(16, 3);
    cout << "Input : ";
    for (int s : b)
        cout << s;
    cout << "; ";
    sort(b.begin(), b.end(), CompareGreaterEqual());
    cout << "Output : ";
    for (int s : b)
        cout << s;
    cout << endl;
    vector<int> c(17, 3);
    cout << "Input : ";
    for (int s : c)
        cout << s;
    cout << "; ";
    sort(c.begin(), c.end(), CompareGreaterEqual());
    cout << "Output : ";
    for (int s : c)
        cout << s;
    cout << endl;
    cout << "***** After Compare_greater_equal and cout >= 17(end - first >= 16) (----- output is error)" << endl << endl;

    cout << "--> sort for type int*" << endl;
    vector<int *> verPInt;
#ifdef CORE1
    for (int i = 0; i < 17; i++) { // >= 17 will coredump when greaterequal
#else
    for (int i = 0; i < 16; i++) {
#endif
        int *pInt = new (nothrow) int;
        if (pInt == NULL) {
            cout << "new error " << __LINE__ << endl;
            goto final;
        }
#ifdef CORE1
        *pInt = 1;
#else
        *pInt = i;
#endif
        verPInt.push_back(pInt);
    }
    cout << "sort, self define greater : " << endl;
    sort(verPInt.begin(), verPInt.end(), CompareGreaterP());
    for (vector<int *>::iterator iter = verPInt.begin(); iter != verPInt.end(); ++iter) {
        cout << **iter;
    }
    cout << endl;

    cout << "sort, self define greaterequal (if vectro<int*>.size()>=17 and all element equal, will coredump test : -DCORE1) : " << endl;
    sort(verPInt.begin(), verPInt.end(), CompareGreaterEqualP());
    for (vector<int *>::iterator iter = verPInt.begin(); iter != verPInt.end(); ++iter) {
        cout << **iter;
    }
    cout << endl;


    // c++ 编译器禁止 goto 后不允许申明新变量，为了测试
    // 编译时加上参数跳过  -fpermissive
    cout << endl << endl <<  "-----------------------------" << endl;
    cout << "--> sort for TestObj" << endl;
    vector<TestObj> verTestObj;
    for (int i = 0; i < 17; ++i) {
        //verTestObj.push_back(TestObj(i));
        verTestObj.push_back(TestObj(1));
    }
    cout << "sort, self define greater : " << endl;
    // not define <
    // sort(verTestObj.begin(), verTestObj.end());
    sort(verTestObj.begin(), verTestObj.end(), CompareTestGreater());
    for(TestObj &obj : verTestObj) {
        cout << obj.m_val;
    }
    cout << endl;

    cout << "sort, self define greater_equal (output error): " << endl;
    sort(verTestObj.begin(), verTestObj.end(), CompareTestGreaterEqual());
    for(TestObj &obj : verTestObj) {
        cout << obj.m_val;
    }
    cout << endl;

    cout << endl << "---> sort for <TestObj *>" << endl;
    vector<TestObj *> verTestObjP;
#ifdef CORE2
    for (int i = 0; i < 17; ++i) {// count >=16 and element equal, will coredump
        TestObj *p = new (nothrow) TestObj(2);
#else
    cout << "指针和直接对象,构造函数调用的次数差别很大" << endl;
    for (int i = 0; i < 17; ++i) {
        TestObj *p = new (nothrow) TestObj(i);
#endif
        if (p == NULL) {
            cout << "new error " << __LINE__ << endl;
            goto final;
        }
        verTestObjP.push_back(p);
    }
    cout << "sort, greater : "<< endl;
    sort(verTestObjP.begin(), verTestObjP.end(), CompareTestGreaterP());
    for (vector<TestObj*>::iterator iter = verTestObjP.begin(); iter != verTestObjP.end(); ++iter) {
        cout << (*iter)->m_val;
    }
    cout << endl;
    cout << "sort, self define greaterequal (if vectro<int*>.size()>=17 and all element equal, will coredump test : -DCORE2) : " << endl;
    sort(verTestObjP.begin(), verTestObjP.end(), CompareTestGreaterEqualP());
    for (vector<TestObj*>::iterator iter = verTestObjP.begin(); iter != verTestObjP.end(); ++iter) {
        cout << (*iter)->m_val;
    }
    cout << endl;
    cout << endl << "Test end" << endl;
    cout << "delete 时候报错core，是测试过程堆栈搞傻,把参数个数调低就不会（１７以下）" << endl;
final:
    for (vector<int *>::iterator iter = verPInt.begin(); iter != verPInt.end(); ++iter) {
        delete *iter;
        *iter = NULL;
    }
    for (vector<TestObj*>::iterator iter = verTestObjP.begin(); iter != verTestObjP.end(); ++iter) {
        delete *iter;
        *iter = NULL;
    }
    return 0;
}
