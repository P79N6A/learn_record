#!/usr/bin/env python
# coding=utf-8
# by orientlu

def sort_insert(my_List, b, e):
    for i in range(b+1, e):
        value = my_list[i]
        for j in range(i-1, b-1, -1):
            if value < my_list[j]:
                my_list[j+1] = my_list[j]
            else:
                my_list[j+1] = value
                break

my_list = [1, 11, 3, 3, 5, 7, 9, 8]
print my_list
sort_insert(my_list, 0, len(my_list))
print my_list


