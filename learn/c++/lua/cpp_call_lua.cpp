/*************************************************************************
 > File Name: test_lua.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Fri 14 Dec 2018 04:06:13 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <memory>
#include <functional>
using namespace std;

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

class LuaGuard {
public:
    LuaGuard(std::shared_ptr<lua_State> L)
    : m_L(L) {
        if (std::shared_ptr<lua_State> sl = m_L.lock()) {
            m_top = lua_gettop(sl.get());
            cout << "record top " << m_top << endl;
        }
    }
    ~LuaGuard() {
        if (std::shared_ptr<lua_State> sl = m_L.lock()) {
        cout << lua_gettop(sl.get()) << endl;
        lua_settop(sl.get(), m_top);
        cout << "recover top " << m_top << endl;
        }
    }

private:
    LuaGuard() = delete;
    LuaGuard(const LuaGuard&) = delete;
    LuaGuard& operator=(const LuaGuard&) = delete;

    std::weak_ptr<lua_State> m_L;
    int m_top;
};

class LuaHelper  {
    friend class LuaGuard;
public:
    LuaHelper(const string &lua_scrpit)
    : m_lua(luaL_newstate(), [](lua_State*L){ lua_close(L); }) {
        luaL_openlibs(m_lua.get());
        luaL_dofile(m_lua.get(), lua_scrpit.c_str());
        //luaL_loadfile(m_lua.get(), lua_scrpit.c_str());
        //lua_pcall(m_lua.get(), 0, 0, 0);
        //should dofile
    }
    virtual ~LuaHelper() {};

private:
    LuaHelper() = delete;
    LuaHelper(const LuaHelper&) = delete;
    LuaHelper& operator=(const LuaHelper&) = delete;

protected:
    std::shared_ptr<lua_State> m_lua;
};

class LuaMath : public LuaHelper {
public:
    LuaMath(const string &lua_scrpit)
    : LuaHelper(lua_scrpit) {}

    int Add(int x, int y);
};

int LuaMath::Add(int x, int y) {
    int sum;
    // stack protect
    LuaGuard g(m_lua);
    // 操作对象入栈-> 参数顺序入栈->调用->参数出保存->对象出->执行
    // push lua function
    lua_getglobal(m_lua.get(), "add");
    // push arg
    lua_pushnumber(m_lua.get(), x);
    lua_pushnumber(m_lua.get(), y);
    // call, two arg, one return
    cout << "Top before call " << lua_gettop(m_lua.get()) << endl;
    lua_call(m_lua.get(), 2, 1);
    cout << "Top after call " << lua_gettop(m_lua.get()) << endl;
    // after call fun, push return at top
    sum = (int)lua_tonumber(m_lua.get(), -1);

    return sum;
}

int main()
{
    LuaMath lua_math("./test.lua");
    cout << "--> cpp call" << endl;
    cout << lua_math.Add(1, 2) << endl;

    return 0;
}
