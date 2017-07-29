#!/usr/bin/env python
# coding=utf-8
# by orientlu

a = {
    'x' : 1,
    'y' : 2,
    'z' : 3
}

b = {
    'w' : 10,
    'x' : 11,
    'y' : 2
}

print("a keys %s" %a.keys())
print("b keys %s" %b.keys())
print("a&b keys %s"%(a.keys() & b.keys()))
print("a-b keys %s"%(a.keys() - b.keys()))
# value no unque
print("a&b items %s"%(a.items() & b.items()))

