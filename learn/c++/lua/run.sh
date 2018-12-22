#!/bin/bash
# by orientlu

#echo "------ > lua_1"
#g++ ./lua_1.cpp -llua -o bin_lua_1  &&  ./bin_lua_1

## cpp 加载运行lua脚本
#echo "-------> cpp call lua"
#g++ ./cpp_call_lua.cpp  -llua -ldl -o bin_cpp_call_lua && ./bin_cpp_call_lua

## lua 加载 cpp 编译的so
echo "--------> lua reuqire cpp_so"
g++ -O2 -Wall -fPIC -W -Waggregate-return -Wcast-align  -Wshadow -Wwrite-strings -pedantic  --shared -o mylualib.so mylualib.cpp   -llua
lua ./lua_call_cpp.lua


echo "--------> cpp register cpp lib, lua call"
g++ ./lua_call_cpp.cpp  ./mylualib.cpp -llua -ldl -o lua_call_cpp_1
./lua_call_cpp_1
