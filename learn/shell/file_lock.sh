#!/bin/bash
# by orientlu

if [ ! -f ./file_lock.o  ]; then
    touch ./file_lock_test.o
    if [ $? -ne 0  ]; then
        echo "create $_ failed"
        exit -1
    fi
fi

{
    #flock -n 3 # 3 文件描述符号
    flock  3 # 3 文件描述符号
    [ $? -eq 1  ] && { echo "failed"; exit -1;  }
    echo $$
    sleep 10

} 3<>file_lock_test.o
