#!/usr/bin/env python3
# coding=utf-8
# by orientlu
# pip3 install pymysql
import pymysql


db = pymysql.connect('localhost', 'root', 'jklfds')
cursor = db.cursor()
cursor.execute("select version()")
data = cursor.fetchone()
print(data)
cursor.execute("show databases")
data = cursor.fetchall()
print(data)

cursor.execute("drop database if exists testdb")
data = cursor.fetchall()
print(data)
cursor.execute("create database testdb")
data = cursor.fetchall()
print(data)
cursor.close()
db.close()

#----

db = pymysql.connect('localhost', 'root', 'jklfds', 'testdb')
cursor = db.cursor()

cursor.execute("drop table if exists user")
data = cursor.fetchall()
print(data)

sql = """CREATE TABLE user(
        id CHAR(20) NOT NULL primary key,
        name CHAR(20))"""
cursor.execute(sql)


sql = """INSERT INTO user(id ,name)
        VALUES ('1', 'MOHAN')"""
try:
    cursor.execute(sql)
    db.commit()
except:
    db.rollback()


sql = """select * from user"""
try:
    cursor.execute(sql)
    results = cursor.fetchall()
    for row in results:
        print(row)
        print(row[0])
except:
    print("error")

cursor.close()
db.close()
