/*************************************************************************
 > File Name: main.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 15 Aug 2018 10:55:10 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;
class A {
public:
	A() : a(0) { cout << "default construct"<<  endl; }
	A(const A& n) : a(n.a) {cout << "copy construct"<< endl; }
	~A() {cout << "des" << endl; }
	int a;
};

A f1()
{
	return A();
}

A f2()
{
	A a;
	a.a = 1;
	return a;
}

A f3()
{
	A a;
	a.a = 1;
	A& c = a;
	cout << "f3 return" << endl;
	return c;
}

A f4(A& a)
{
	cout << "f4 return" << endl;
	return a;
}

A& f5(A& a)
{
	return a;
}

// 不直接放回对象，不创建临时对象，但是返回局部变量的引用是错误的
// 函数返回时局部变量已经被销毁
//const A& f6()
//{
//	return A();
//}


//g++ main.cpp -fno-elide-constructors
//g++ main.cpp
int main(void)
{
	cout << "1 --- 直接返回对象" << endl;
	A o1 = f1();
	cout << o1.a << endl;

	cout << "11--- 返回对象，初始化引用" << endl;
	const A& ro4 = f1();
	cout << ro4.a << endl;
	cout << "****" << endl;

	cout << "2--- 返回对象" << endl;
	A o2 = f2();
	cout << o2.a << endl;
	cout << "****" << endl;

	cout << "3--- 通过引用返回对象" << endl;
	A o3 = f3();
	cout << o3.a << endl;
	cout << "****" << endl;

	cout << "4---- 返回传入引用的对象" << endl;
	const A& ro5 = f4(o3);
	cout << ro5.a << endl;
	cout << "****" << endl;

	cout << "5--- 返回传入的对象引用" << endl;
	const A& ro6 = f5(o3);
	cout << ro6.a << endl;
	cout << "****" << endl;

	return  0;
}

