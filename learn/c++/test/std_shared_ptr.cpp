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
        ~TestObj() {printf("TestObj deconstructor val %d\n", m_val);}
        int get() const
        {
            return m_val;
        }
    private:
        int m_val;
};

int main(int argc, char *argv[])
{
    cout << " --- Test one" << endl;
    {

    weak_ptr<int> wptr;
    {
        vector<IntPtr_t> vInt;
        for (auto i = 0; i < 10; ++i) {
            IntPtr_t ptr = make_shared<int>(i);
            vInt.push_back(ptr);
        }
        for (auto iter = vInt.begin(); iter != vInt.end(); ++iter) {
            cout <<  "Pointer : "  << iter->get()  << " Value : " <<*(iter->get()) << " uer countt " << (iter->use_count())<< endl;
        }

        wptr = vInt[4];
        cout << "after wptr " << vInt[4].use_count() << endl;
        IntPtr_t sptr = vInt[4];
        cout << "after sptr " << vInt[4].use_count() << endl;

        if (auto ptr = wptr.lock()) {
            cout << " weak_ptr : " << *ptr << endl;
        }
    }

    if (auto ptr = wptr.lock()) {
        cout << " weak_ptr : " << *ptr << endl;
    } else {
        cout << "vInt expired" << endl;
    }


    }

    cout << " --- Test two" << endl;


    std::shared_ptr<int> iPtr = std::make_shared<int>(1);
    std::cout << *iPtr << std::endl;

    std::shared_ptr<int> iPtr2((new int(2)), self_del);
    std::cout << *iPtr2 << std::endl;

    int *pint = new (std::nothrow) int(3);
    std::cout << pint  << std::endl;
    std::shared_ptr<int> iPtr3(pint, self_del);
    std::cout << pint  << std::endl;
    std::cout << *iPtr3 << std::endl;

    std::shared_ptr<TestObj> testObjPtr = std::make_shared<TestObj>(4);
    std::cout << testObjPtr->get() << std::endl;
    std::shared_ptr<TestObj> testObjPtr2 = testObjPtr;
    std::cout << testObjPtr2->get() << std::endl;

    std::cout << "--- end" << std::endl;



    return 0;
}
