#!/bin/bash
# by orientlu

a=1
b=3

if [ "$a" -eq "$b" ]; then
    echo "a eq b"
fi

if [ "$a" -ne "$b" ]; then
    echo "a neq b"
fi

## -gt -ge -lt -le

## for bash, not for sh
## use (())
if (( "$a" <= "$b" )); then
    echo "a <= b"
fi

# -a -o -->  [[ && || ]]
if [ ""$a" -gt 0" -a ""$a" -lt "$b"" ]; then
    echo "-> a lt b"
fi

if [[ ""$a" -gt 0" && ""$a" -lt "$b"" ]]; then
    echo "-> a lt b"
fi


# 判断是否为空
if [ -n "$string" -o "$a" = "$b" ]; then
    echo "->1 $string || a = b"
fi
# 上判断字符串为空方式某些bash会报错
if [ "x$string" != x ];then
    echo "->1"$string
fi
string=a
if [ -n "$string" -o "$a" = "$b" ]; then
    echo "->2 $string || a = b"
fi
# 上判断字符串为空方式某些bash会报错
if [ "x$string" != x ];then
    echo "->2" $string
fi

