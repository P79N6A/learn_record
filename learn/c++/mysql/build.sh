#!/bin/bash
# by orientlu
g++ test_insert.cpp `mysql_config --cflags --libs` -o test

