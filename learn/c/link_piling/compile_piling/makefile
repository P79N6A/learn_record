
all:out

# 编译时打桩

out: main.c mymalloc.o
	# -I . : so will use mymalloc
	#  编译最终运行程序时指定include优先检索当前目录，所以会读取当前目录的头文件malloc.h
	#  替代系统库的
	gcc -I . -o out main.c mymalloc.o

mymalloc.o: mymalloc.c
	# no -I ., will use std malloc
	# 没有指定include当前目录，使用的是系统malloc
	gcc -DCOMPILELINK -c mymalloc.c

.PHONY : clean
clean:
	@rm -rf out *.o
