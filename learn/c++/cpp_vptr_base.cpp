/*************************************************************************
 > File Name: cpp_vptr_base.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Sat 24 Nov 2018 06:26:50 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

namespace  xxx {

class Simple {
public:
    Simple()  { m_i = 11; }
    ~Simple() {}
    void aa(void) { return; }
    static void bb(void) { return; }
//private:
    int m_i;
    static int m_static_val;
};
int Simple::m_static_val = 12;

class Simple2 : public Simple {
public:
    Simple2() { m_i = 22; m_2i = 33; }

    int m_i;
    int m_2i;
};

class Base {
public:
    Base() { cout << "Base" << endl; m_base1 = 1;}
    virtual ~Base() {}
    virtual void  BaseFun1(void) { cout << "BaseFun1" << endl; }
    virtual void  BaseFun2(void) { cout << "BaseFun2" << endl; }
    virtual void  BaseFun3(void) { cout << "BaseFun3" << endl; }
    virtual int GetVal(void) { return m_base1; }
    virtual int GetVal1(void) { return m_base1; }

    void  BaseFun4(void) { cout << "BaseFun4" << endl; }

//private:
    int m_base1;
};

class Base2 {
public:
    Base2() { cout << "Base2" << endl; m_base2 = 2;}
    virtual ~Base2() {}
    virtual void  BaseAFun1(void) { cout << "Base2Fun1" << endl; }
    virtual void  BaseAFun2(void) { cout << "Base2Fun2" << endl; }
//private:
    int m_base2;
};


class A : public virtual Base {

public:
    A() { cout << "A" << endl; m_base1 = 2; m_a1 = 33; }
    virtual void A1() { cout << "A1" << endl; }
    void A2() { cout << "A2" << endl; }
    virtual void BaseFun1(void) { cout << "BaseFun1_fromA" << endl; }
    virtual int GetVal(void) {return m_base1; }
    virtual ~A() {}
//private:
    int m_base1;
    int m_a1;
};

class AA : public  Base, public Base2 {
public:
    AA() { cout << "AA" << endl; m_base1 = 3; m_a1 = 33; }
    virtual void AA1() { cout << "A1" << endl; }
    void A2() { cout << "A2" << endl; }
    virtual void BaseFun1(void) { cout << "BaseFun1_fromA" << endl; }
    virtual void  BaseAFun2(void) { cout << "Base2Fun2_fromA" << endl; }
    virtual int GetVal(void) {return m_base1; }
    virtual ~AA() {}
//private:
    int m_base1;
    int m_a1;
};

class B : public virtual Base {
public:
    B() { cout << "B" << endl; }
    virtual void B1() { cout << "B1" << endl; }
    //virtual void BaseFun1(void) { cout << "BaseFun1_fromB" << endl; }
    virtual ~B() {}
};

class C : public A, public B {
public:
    virtual void BaseFun3(void) { cout << "BaseFun3_fromC" << endl; }
    void c1() { cout << "C1" << endl; }
//private:
    int m_base1;
    int m_c1;
    int m_c2;
};

}
using namespace xxx;

typedef void(*func_t)(void);
typedef void(**vptr_t)(void);
typedef void(***pvptr_t)(void);

int main()
{
    Simple sp;
    cout << "Simple obj addr : " << reinterpret_cast<Simple*>(&sp) << endl;
    cout << "Simple.m_i addr : " << reinterpret_cast<int *>(&sp.m_i) << endl;
    cout << "Simple.m_static_val : " <<reinterpret_cast<int*>(&sp.m_static_val) << endl;
    cout << "--------------" << endl;
    Simple2 sp2;

    Base base;
    cout << "Base obj addr : " << reinterpret_cast<Base*>(&base) << endl;
    cout << "Base.m_base1 addr : " <<reinterpret_cast<int*>(&base.m_base1) << endl;
    cout << "Pointer len : " << sizeof(void(*)(void)) << endl;
    // class_addr(vptr_addr)->vptr(pfun_addr)->*pfun
    //void (**vptr)(void) =reinterpret_cast<void(**)(void)>(*((void(***)(void))&base));
    //void (*pfun)(void) = (void(*)(void))*(vptr + 2); //　前面是保存析构，最后是info
    vptr_t vptr = *(pvptr_t)(&base);
    func_t pfun = (func_t)*(vptr+2);
    pfun();
    cout << "-----" << endl;

    A  a;
    cout << "a " << a.GetVal() << endl;
    cout << "a " << a.GetVal1() << endl;
    cout << "a " << a.Base::GetVal() << endl;
    a.BaseFun1();
    a.BaseFun2();

    AA aa;
    cout << "-----" << endl;
    C c;
    c.BaseFun3();
    // 如果A 和Ｂ不是virtual继承，以下会报错的。
    c.BaseFun1();
    c.BaseFun2();

    cout << "end" << endl;
    return 0;
}

