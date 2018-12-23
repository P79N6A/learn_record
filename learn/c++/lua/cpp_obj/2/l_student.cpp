/*************************************************************************
 > File Name: l_student.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Sun 23 Dec 2018 03:49:09 PM CST
 ************************************************************************/

#include "l_student.h"
#include <iostream>
#include <string>

#define STUDENT_METATABLE "mt.student"

int l_student_create(lua_State* L) {
    Student **s = (Student**)lua_newuserdata(L, sizeof(Student*));
    *s = new Student;
    // s 的metatable 设置为 全局 mt.student
    luaL_getmetatable(L, STUDENT_METATABLE);
    lua_setmetatable(L, -2);
    return 1;
}

int l_student_getName(lua_State* L) {
    // obj 在 栈底
    // 判断 s是否包含 STUDENT_METATABLE
    Student **s = (Student**)luaL_checkudata(L, 1, STUDENT_METATABLE);
    luaL_argcheck(L, s != NULL, 1, "invalid user data");

    lua_pushstring(L, (*s)->GetName().c_str());
    return 1;
}

int l_student_setName(lua_State* L) {
    // obj 在 栈底
    Student **s = (Student**)luaL_checkudata(L, 1, STUDENT_METATABLE);
    luaL_argcheck(L, s != NULL, 1, "invalid user data");

    luaL_checkstring(L, -1);

    std::string name = lua_tostring(L, -1);
    (*s)->SetName(name);

    return 0;
}

int l_student_gc(lua_State* L) {
    // obj 在 栈底
    Student **s = (Student**)luaL_checkudata(L, 1, STUDENT_METATABLE);
    luaL_argcheck(L, s != NULL, 1, "invalid user data");
    if (*s) {
        delete *s;
    }
    return 0;
}

static const luaL_Reg m_lib[] = {
    {"create", l_student_create},
    {NULL, NULL} // END
};

// 创建一个元表
static const luaL_Reg m_student_metatable[] = {
    {"set", l_student_setName},
    {"get", l_student_getName},
    {"__gc", l_student_gc},
    {NULL, NULL} // END
};

int luaopen_student(lua_State* L) {

    // 设置一个全局表作为 student 的元表
    luaL_newmetatable(L, STUDENT_METATABLE); // push metatable
    lua_pushvalue(L, -1); // push metatable, 下一个设置会pop
    /* now l stack
     *|mt.Student| <-func
     *|mt.Student| <-__index
     * */
    // mt.Student.__index = mt,Student
    lua_setfield(L, -2, "__index"); // set and pop metatable
    luaL_setfuncs(L, m_student_metatable, 0);


    luaL_newlib(L, m_lib); // push m_lib
    return 1;
}
