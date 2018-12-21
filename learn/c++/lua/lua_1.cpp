/*************************************************************************
 > File Name: test_lua.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Fri 14 Dec 2018 04:06:13 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}


int main()
{
    lua_State* L = luaL_newstate();
    if (L == NULL) {
        cout << "new luaL_newstate error" << endl;
        return -1;
    }
    cout << "TOP when init " << lua_gettop(L) << endl;

    // push stack
    lua_pushstring(L, "lua test");
    cout << "TOP after pushstring " << lua_gettop(L) << endl;

    lua_pushnumber(L, 66); // -1
    cout << "TOP after pushnumber " << lua_gettop(L) << endl;


    if (lua_isstring(L, 1)) {
        cout << lua_tostring(L, 1) << endl;
    }
    cout << "TOP after lua_tostring " << lua_gettop(L) << endl;
    if (lua_isnumber(L, 2)) {
        cout << lua_tonumber(L, 2) << endl;
        cout << lua_tonumber(L, -1) << endl;
    }
    cout << "TOP after lua_tonumber " << lua_gettop(L) << endl;

    lua_close(L);
    return 0;
}
