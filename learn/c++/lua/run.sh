#!/bin/bash
# by orientlu

echo "------ > lua_1"
g++ ./lua_1.cpp -llua -o bin_lua_1  &&  ./bin_lua_1

echo "-------> cpp call lua"
g++ ./cpp_call_lua.cpp  -llua -ldl -o bin_cpp_call_lua && ./bin_cpp_call_lua

