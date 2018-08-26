/*************************************************************************
 > File Name: std_shared_ptr.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Sun 26 Aug 2018 05:03:36 PM CST
 ************************************************************************/

#include<iostream>
#include<memory>

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
