#!/usr/bin/env python
# coding=utf-8

def my_print(str):
    pass
    #print(str)

class Calculator():
    __version__ = 4
    def __init__(self, a, b):
        my_print("cal init")
        self.a = int(a)
        self.b = int(b)

    def __del__(self):
        my_print("cal del")

    def add(self):
        return self.a + self.b

    def add_xx(self):
        # need mock
        pass

    def sub(self):
        return self.a - self.b

    def mul(self):
        return self.a * self.b

    def div(self):
        return self.a / self.b
