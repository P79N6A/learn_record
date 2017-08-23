#!/usr/bin/env python
# coding=utf-8
# by orientlu

import sqlite3

conn = sqlite3.connect('sqlite3_test.db')
cursor = conn.cursor()
#cursor.execute('create table user(id INTEGER not null  primary key, name varchar(20))')
ret = cursor.execute("insert into user (name) values ('lcd')")
print(ret)
ret = cursor.execute("select * from user")
print(ret)
values = cursor.fetchall()
print(values)
for v in values:
    print(v)

cursor.rowcount
cursor.close()
conn.commit()
conn.close()
