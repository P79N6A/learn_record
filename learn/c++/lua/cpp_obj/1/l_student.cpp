/*************************************************************************
 > File Name: l_student.cpp
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Sun 23 Dec 2018 03:49:09 PM CST
 ************************************************************************/

#include "l_student.h"
#include <iostream>
#include <string>

int l_student_create(lua_State* L) {
    Student **s = (Student**)lua_newuserdata(L, sizeof(Student*));
    *s = new Student;
    return 1;
}

int l_student_getName(lua_State* L) {
    // obj 在 栈底
    Student **s = (Student**)lua_touserdata(L, 1);
    luaL_argcheck(L, s != NULL, 1, "invalid user data");

    lua_pushstring(L, (*s)->GetName().c_str());
    return 1;
}

int l_student_setName(lua_State* L) {
    // obj 在 栈底
    Student **s = (Student**)lua_touserdata(L, 1);
    luaL_argcheck(L, s != NULL, 1, "invalid user data");

    luaL_checkstring(L, -1);

    std::string name = lua_tostring(L, -1);
    (*s)->SetName(name);

    return 0;
}

static const luaL_Reg m_lib[] = {
    {"create", l_student_create},
    {"set", l_student_setName},
    {"get", l_student_getName},
    {NULL, NULL} // END
};

int luaopen_student(lua_State* L) {
    luaL_newlib(L, m_lib);
    return 1;
}
