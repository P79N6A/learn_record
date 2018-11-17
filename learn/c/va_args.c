/*************************************************************************
 > File Name: main.c
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Sat 17 Nov 2018 10:31:25 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdarg.h>

void var_fun(int count, ... )
{
    va_list valist;
    va_start(valist, count); //根据可变参数个数初始化

    printf("Get %d arg : ", count);
    for (int i = 0; i < count; ++i) {
        int arg = va_arg(valist, int); // 循环取出指定类型的参数
        printf(" %d;", arg);
    }
    printf("\n");

    va_end(valist); //释放内存
}

// c99. __VA_ARGS__ 表示可变参数 ...
#define VAR_FUN_1(count, ... ) var_fun(count, __VA_ARGS__)
// 自己使用别称代替__VA_ARGS__
#define VAR_FUN_2(count, args... ) var_fun(count, args)

#define VAR_FUN_3(count, ... ) var_fun(count, ##__VA_ARGS__)

int main(int argc, char* argv[])
{
    var_fun(1, 1);
    var_fun(2, 1, 2);
    var_fun(3, 1, 2, 3);

    VAR_FUN_1(1, 1);
    VAR_FUN_2(1, 1);
    //VAR_FUN_2(0); // 无参传入会报错, var_fun_3  ## 解决
    VAR_FUN_3(1, 1); // 无参传入会报错, var_fun_3  ## 解决
    VAR_FUN_3(0); // 无参传入会报错, var_fun_3  ## 解决
    return 0;
}

