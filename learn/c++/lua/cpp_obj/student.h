/*************************************************************************
 > File Name: student.h
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Sun 23 Dec 2018 03:45:08 PM CST
 ************************************************************************/

#ifndef _STUDENT_H
#define _STUDENT_H
#pragma once


#include <iostream>
#include <string>

class Student {
public:
    Student()
        : m_name{"default name"} {
    }
    ~Student() {
        std::cout << "Student " << m_name << " gone .>>>" << std::endl;
    }
    Student& SetName(const std::string& name) {
        m_name = name;
        return *this;
    }
    const std::string& GetName(void) const {
        return m_name;
    }
private:
    std::string m_name;
};

#endif
