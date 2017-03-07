#!/bin/bash

gcc mq_1_snd.c -lrt mq_type.h -o 1.o
gcc mq_2_rcv.c -lrt mq_type.h -o 2.o

./1.o 12 &
sleep 1
./2.o &
