#!/usr/bin/env python
# coding=utf-8
# by orientlu

def frange(start, stop, incrament):
    x = start
    print('frange start')
    while x < stop:
        yield x
        x += incrament
    print('frange end')


if __name__ == '__main__':
    c = frange(1, 5, 1)
    for n in c:
        print(n)

    print(next(c))
