/*************************************************************************
 > File Name: mylualib.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 19 Dec 2018 12:26:05 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#include "mylualib.h"

static int add(lua_State *L) {
    // argc
    int n = lua_gettop(L);
    int sum = 0;
    cout << "Top, in fun 1" << lua_gettop(L) << endl;

    for (int i = 0; i < n; ++i) {
        sum += lua_tonumber(L, i+1);
    }

    cout << "Top, in fun 2 " << lua_gettop(L) << endl;
    // return values
    lua_pushnumber(L, sum);
    lua_pushnumber(L, n);

    cout << "Top, in fun, return " << lua_gettop(L) << endl;
    // return 2 value
    return 2;
}

static const luaL_Reg m_lib[] = {
    {"c_add", add},
    {NULL, NULL} // END
};

int luaopen_mylualib(lua_State* L) {
    // mylib.add() in lua
    lua_register(L, "mylib", m_lib);
    // 1 value return :  m_lib,
    return 1;
}
