#!/bin/bash
# by orientlu

gcc -fPIC -shared ./calculate.c -o libcalculate.so

gcc ./main.c -ldl -o test_dl

./test_dl
