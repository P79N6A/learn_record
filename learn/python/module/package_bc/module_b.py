#!/usr/bin/env python
# coding=utf-8
# by orientlu

import inspect

def module_b_fun():
    print("call {0}".format(inspect.stack()[0][3]))

if __name__ == "__main__":
    moule_b_fun()
