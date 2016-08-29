
BUILD_FLAG :=
FW_VER=$(shell git log -1 --pretty="%h")
BUILD_FLAG += -DCODE_VER=0x$(FW_VER)

out : main.o
	gcc $(BUILD_FLAG) -o main.o main.c
