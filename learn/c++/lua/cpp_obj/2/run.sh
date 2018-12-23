#!/bin/bash
# by orientlu

g++ -Wall -fPIC --shared -o student.so  l_student.cpp  -llua
lua ./test.lua
