#!/usr/bin/env python3
# coding=utf-8
# by orientlu

from collections import deque

def serch(lines, pattern, history=5):
    previous_lines = deque(maxlen=history)
    for line in lines:
        if pattern in line:
            yield line, previous_lines
        previous_lines.append(line)

if __name__ == '__main__':
    with open(r'./test.txt') as f:
        for pline, previous in serch(f, "python", 5):
            print(pline, end='')
            print(previous)
        print(pline, end='')
        print("-"*20)
