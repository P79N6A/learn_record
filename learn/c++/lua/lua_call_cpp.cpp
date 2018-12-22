/*************************************************************************
 > File Name: lua_call_cpp.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Sun 23 Dec 2018 12:50:00 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#include <lua.hpp>
#include "mylualib.h"

// 在 cpp 中调用lua，lua中调用cpp注册的函数
//

int  main(int argc, char* argv[])
{
    lua_State * L = luaL_newstate();
    if (!L) {
        cout << "luaL_newstate error" << endl;
        return -1;
    }
    // open L vm std lib
    luaL_openlibs(L);

    // load my lua lib
    // mylualib.xxx in lua
    luaL_requiref(L, "mylualib", luaopen_mylualib, 1);

    // load lua script
    luaL_dofile(L, "./lua_call_cpp_no_require.lua");
    cout << lua_tostring(L, -1);
    return 0;
}
