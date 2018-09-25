项目编写插件so，插件需要链接到其他静态库，开始有点晕...


```bash
## 编译静态库，地球人都这么编写
gcc -o static.o -c static.c
ar -r libstatic.a static.o

## 编译动态库，然后链接上面的静态库
gcc -o dynamic.o -c dynamic.c
gcc -o libdynamic.so -shared -fPIC -L. -lstatic dynamic.o

## 编译程序，报错，静态库中没有找到符号
gcc main.c -L. -ldynamic -o main

##查看发现，so中没有把静态库的东西搞进去
nm xx.so
```

有人说：
静态库也-fPIC -shared
这....

然后看到
https://blog.csdn.net/edwardlulinux/article/details/56812636

试了下，靠谱
调换了位置
gcc -o libdynamic1.so -shared -fPIC dynamic.o -L. -lstatic


