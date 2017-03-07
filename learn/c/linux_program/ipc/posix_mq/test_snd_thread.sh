#!/bin/bash

gcc mq_1_snd.c -lrt mq_type.h -o 1.o
gcc mq_4_thread.c  -lrt -lpthread ./mq_type.h -o 5.o

./5.o &
./1.o 2
./1.o 1
