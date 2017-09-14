
all:out

out: main.c mymalloc.o
	gcc -o out main.c
mymalloc.o: mymalloc.c
	gcc -DRUNTIME --share -fpic -o mymalloc.so mymalloc.c -ldl

.PHONY : clean run
run:
	# 指定运行时加载的库
	#setenv LD_PRELOAD "./mymalloc.SO"; ./out; unsetenv LD_PRELOAD
	export LD_PRELOAD="./mymalloc.so"; ./out; unset LD_PRELOAD
	export LD_PRELOAD="./mymalloc.so"; uptime; unset LD_PRELOAD

clean:
	@rm -rf out *.so
