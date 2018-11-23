#!/bin/bash
# by orientlu

rm ./perf -f

pwd

src="./main.cpp ./mother.cpp ./naughty_kid.cpp ./flag.cpp"

g++  $src -o perf -lgflags -lpthread -lglog -levent -lrt #-DNDEBUG

./perf &
