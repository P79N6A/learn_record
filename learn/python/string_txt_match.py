#!/usr/bin/env python
# coding=utf-8
# by orientlu

import re
import os

line = 'asdf fjdk; afed, fjek,asdf, foo'
# 指定分隔符 + 若干空格
ret = re.split(r'[;,\s]\s*', line)
print(ret)


filename = 'spam.txt'
print(filename.endswith('txt'))
print(filename.startswith('txt'))
print(filename.startswith('spam'))
print(filename.find('am'))

filename = os.listdir('.')
ret = [name for name in filename if name.endswith(('.c', '.txt'))]
print(ret)


text = 'i am luchaodong'
ret = text.replace('luchaodong', 'orientlu')
print(text, "-->", ret)

text = 'Today is 11/27/2012. PyCon starts 3/13/2013.'
ret = re.sub(r'(\d+)/(\d+)/(\d+)', r'\3-\1-\2', text)
print(text, "-->", ret)

s = '{name} has {n} messages.'
ret = s.format(name='Guido', n=37)
print(ret)



