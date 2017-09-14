
all:out

out: main.c mymalloc.o
	# __wrap_malloc and __wrap_free
	gcc -Wl,--wrap,malloc -Wl,--wrap,free -o out main.c mymalloc.o

mymalloc.o: mymalloc.c
	gcc -DLINKTIME -c mymalloc.c

.PHONY : clean
clean:
	@rm -rf out *.o
