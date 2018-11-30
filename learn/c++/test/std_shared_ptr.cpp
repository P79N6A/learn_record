/*************************************************************************
 > File Name: std_shared_ptr.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Sun 26 Aug 2018 05:03:36 PM CST
 ************************************************************************/

#include<iostream>
#include<memory>
#include <vector>

//auto_prt 和 shared_ptr 的差别

using namespace std;
typedef shared_ptr<int> IntPtr_t;

void self_del(int* ptr)
{
    std::cout << "call selfdef delfun value : " << *ptr << std::endl;
    delete ptr;
}

class TestObj {
public:
    TestObj(int val) : m_val(val) { printf("TestObj constructor val %d \n", m_val); }
    ~TestObj() { printf("TestObj deconstructor val %d\n", m_val);}
    int GetValue() const { return m_val; }
private:
    int m_val;
};

int main(int argc, char *argv[])
{

{
    cout << " -------- Test 1 begin" << endl;
    weak_ptr<int> wptr;
    {
        vector<IntPtr_t> vInt;
        for (auto i = 0; i < 3; ++i) {
            IntPtr_t ptr = make_shared<int>(i);
            vInt.push_back(ptr);
        }
        auto iter = vInt.begin();
        cout <<  "Pointer : "  << iter->get()  << " Value : " <<*(iter->get()) << " UerCount " << (iter->use_count())<< endl;
        cout <<  "Pointer : "  << vInt[1]  << " Value : " <<*(vInt[1]) << " UerCount " << (vInt[1].use_count())<< endl;

        wptr = vInt[2];
        cout << "after wptr, UserCount " << vInt[2].use_count() << endl;
        IntPtr_t sptr = vInt[2];
        cout << "after sptr, UserCount " << vInt[2].use_count() << endl;

        if (auto ptr = wptr.lock()) {
            cout << "Get value by weak_ptr : " << *ptr << endl;
        }
    }

    if (auto ptr = wptr.lock()) {
        cout << " weak_ptr : " << *ptr << endl;
    } else {
        cout << "vInt expired" << endl;
    }
}
    cout << " -------- Test 1 end" << endl;


{
    cout << " -------- Test 2 begin" << endl;
    std::shared_ptr<int> iPtr = std::make_shared<int>(1);
    std::cout << *iPtr << std::endl;

    std::shared_ptr<int> iPtr2((new int(2)), self_del);
    std::cout << *iPtr2 << std::endl;

    int *pint = new (std::nothrow) int(3);
    std::cout << pint  << std::endl;
    std::shared_ptr<int> iPtr3(pint, self_del);
    std::cout << *pint  << std::endl;
    std::cout << *iPtr3 << std::endl;

    std::shared_ptr<TestObj> testObjPtr = std::make_shared<TestObj>(4);
    std::cout << testObjPtr->GetValue() << std::endl;
    std::shared_ptr<TestObj> testObjPtr2 = testObjPtr;
    std::cout << testObjPtr2.get()->GetValue() << std::endl;

}
    cout << " -------- Test 2 end" << endl;

{
    cout << " -------- Test 3 begin" << endl;
    //unique_ptr<TestObj> testObjPtr(new TestObj(5));
    TestObj* raw_ptr = new TestObj(5);
    cout << "RawPtr " << raw_ptr << endl;
    unique_ptr<TestObj> testObjPtr1(raw_ptr);
    cout << "RawPtr " << raw_ptr << " Value " << raw_ptr->GetValue() << endl;
    cout << "uPtr " << testObjPtr1.get() << " Value " << testObjPtr1->GetValue() << endl;

    //unique_ptr<TestObj> testObjPtr2 = testObjPtr1; // compile error
    unique_ptr<TestObj> testObjPtr2 = move(testObjPtr1);
    cout <<  "ptr after move " << testObjPtr1.get() << endl;
    cout << "uPtr " << testObjPtr2.get() << " Value " << testObjPtr2->GetValue() << endl;
}
    cout << " -------- Test 3 end" << endl;

    return 0;
}
