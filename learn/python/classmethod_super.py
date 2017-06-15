#!/usr/bin/env python
# coding=utf-8
# by orientlu

class A(object):

    def __init__(self):
        print("A init")
        super().__init__()

    def foo(self, x):
        '''绑定对象'''
        print("A exec foo (%s, %d)" %(self, x))

    @classmethod
    def class_foo(cls, x):
        '''绑定类'''
        print("exec class_foo (%s, %d)" %(cls, x))

    @staticmethod
    def static_foo(x):
        '''没有绑定类，对象'''
        print("exec static_foo (%d)" %(x))

class B(object):

    def foo(self, x):
        '''绑定对象'''
        print("exec foo (%s, %d)" %(self, x))

    @classmethod
    def test_class_foo(cls, x):
        '''绑定类'''
        print("exec test_class_foo -2- (%s, %d)" %(cls, x))

    def test_class_foo(self, x):
        '''后面覆盖前面的同名函数'''
        print("exec test_class_foo -1- (%s, %d)" %(self, x))


class AA(A):

    def __init__(self):
        print("AA Int")

    def foo(self, x):
        '''覆盖了父类函数'''
        print("AA exec foo (%s, %d)" %(self, x))


class C(AA):

    def __init__(self):
        '''子类定义了函数覆盖了父类，通过super调用到父类函数'''
        super().__init__()
        print("C init")

    def c_fun1(self):
        '''子类没有定义的函数，直接调用父类函数'''
        self.foo(1)



if __name__ == "__main__":

    print("***********************************")
    print("-------")
    a = A()
    a.foo(1)
    a.class_foo(1)
    a.static_foo(1)

    print("-------")
    A.foo(a, 1)
    A.class_foo(1)
    A.static_foo(1)

    print("***********************************")
    b = B()
    b.test_class_foo(1)
    # 以下调用出错，因为classmethod被后面的函数所覆盖了
    #B.test_class_foo(1)
    # 实际存在是后面定义的函数
    B.test_class_foo(b, 1)

    print("***********************************")
    c = C()
    c.c_fun1()
