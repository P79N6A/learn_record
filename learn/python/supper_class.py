#!/usr/bin/env python
# coding=utf-8

class A:
    def __init__(self):
        print("Enter A")
        super(A, self).__init__()
        print("Leave A")

class B:
    def __init__(self):
        print("Enter B")
        #super(B, self).__init__()
        print("Leave B")

class CA(A):
    def __init__(self):
        print("Enter CA")
        super(CA,self).__init__()
        print("Leave CA")


class CAA(CA, A):
    def __init__(self):
        print("Enter CAA")
        super(CAA,self).__init__()
        print("Leave CAA")

class CB(B):
    def __init__(self):
        print("Enter CB")
        B.__init__(self)
        print("Leave CB")


class CBB(CB, B):
    def __init__(self):
        print("Enter CBB")
        CB.__init__(self)
        B.__init__(self)
        print("Leave CBB")


if __name__ == "__main__":
    print("- New Object CAA")
    caa = CAA()
    print("- New Object CBB")
    cbb = CBB()

