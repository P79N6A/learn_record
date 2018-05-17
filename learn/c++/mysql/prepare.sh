#!/bin/bash
# by orientlu

## 安装启动mysql
## 查看db 开发包，存在现实连接程序信息，否者需要安装mysql-devel
mysql_config --cflags --libs

MYSQL_ROOT=jklfds
TEST_DB=test
## 创建测试数据库
mysql -uroot -p${MYSQL_ROOT} -e "create database $TEST_DB";
mysql -uroot -p${MYSQL_ROOT} -D${TEST_DB} -e "create table test(name varchar(255),num int(10) ); ";


