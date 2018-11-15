/*************************************************************************
 > File Name: main.c
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Wed 31 Oct 2018 11:36:59 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>

#define LIB_PATH  "./libcalculate.so"

typedef int (*FunCal)(int, int);

int main()
{
    void *so_handle;
    char *error;
    FunCal p_fun_cal = NULL;

    // open so
    so_handle = dlopen(LIB_PATH, RTLD_LAZY | RTLD_LOCAL);
    if (!so_handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    // clear error msg
    dlerror();

    //p_fun_cal = (FunCal)dlsym(so_handle, "add_undefine");
    p_fun_cal = (FunCal)dlsym(so_handle, "add");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    int sum = p_fun_cal(1, 1);
    printf("1 + 1 sun is %d\n", sum);

    dlclose(so_handle);
    exit(EXIT_SUCCESS);
}
