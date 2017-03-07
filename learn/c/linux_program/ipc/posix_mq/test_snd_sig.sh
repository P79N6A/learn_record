#!/bin/bash

gcc mq_1_snd.c -lrt mq_type.h -o 1.o
gcc mq_3_sig.c -lrt mq_type.h -o 3.o

./3.o &
./1.o 2
./1.o 1
