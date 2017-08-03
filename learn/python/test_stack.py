#!/usr/bin/env python
# coding=utf-8
# by orientlu

import inspect

def get_fun_name():
    # stack top is myself
    print(inspect.stack()[0][3])
    # the name who call me
    return inspect.stack()[1][3]

def print_stack():
    print("current stack:")
    for s in inspect.stack():
        print(s)

class aa:
    def fun_lcd(self):
        print(get_fun_name())
        print_stack()


if __name__ == "__main__":
    a = aa()
    a.fun_lcd()
