/*************************************************************************
 > File Name: mylualib.h
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 19 Dec 2018 12:21:46 AM CST
 ************************************************************************/

#ifndef _MYLUALIB_H
#define _MYLUALIB_H
#pragma once

#include <lua.hpp>

/// call by lua when require
extern "C" int luaopen_mylualib(lua_State *L);

#endif
