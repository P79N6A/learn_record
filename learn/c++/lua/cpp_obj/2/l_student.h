/*************************************************************************
 > File Name: l_student.h
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Sun 23 Dec 2018 03:50:52 PM CST
 ************************************************************************/

#ifndef _L_STUDENT_H
#define _L_STUDENT_H
#pragma once

// now we have define a cpp class Student
#include "lua.hpp"
#include "../student.h"

extern "C" int luaopen_student(lua_State* L);

#endif
