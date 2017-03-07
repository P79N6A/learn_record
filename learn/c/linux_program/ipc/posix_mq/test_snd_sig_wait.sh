#!/bin/bash

gcc mq_1_snd.c -lrt mq_type.h -o 1.o
gcc mq_3_sig_2.c -lrt mq_type.h -o 4.o

./4.o &
./1.o 2
./1.o 1
