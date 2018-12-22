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
    cout << "lua call cpp fun, start" << endl;
    // argc
    int n = lua_gettop(L);
    int sum = 0;
    cout << "Stack Top, in fun begining is " << lua_gettop(L) << endl;

    for (int i = 0; i < n; ++i) {
        //sum += lua_tonumber(L, i+1);
        // check,is number, return number, otherwise, error
        sum += luaL_checknumber(L, i+1);
    }

    cout << "Stack Top, after get all args is " << lua_gettop(L) << endl;

    // push return values
    lua_pushnumber(L, sum); // first value
    lua_pushnumber(L, n);
    // 返回lua时会自动清理栈上返回结果下的其他内容
    // 所以在push时不需要做清理
    cout << "Stack Top, after push return is " << lua_gettop(L) << endl;

    // mean has return 2 value
    return 2;
}

static const luaL_Reg m_lib[] = {
    {"c_add", add},
    {NULL, NULL} // END
};

// lua 中 require "xxx"
// 对应调用 luaopen_xxx()
int luaopen_mylualib(lua_State* L) {
    cout << "open mylualib" << endl;

    luaL_newlib(L, m_lib);
    // 1 value return :  m_lib,
    return 1;
}
