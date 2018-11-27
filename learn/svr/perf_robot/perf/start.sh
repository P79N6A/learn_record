#!/bin/bash
# by orientlu

rm ./perf -f

pwd

src="./main.cpp ./mother.cpp ./naughty_kid.cpp ./flag.cpp ./robot.cpp ./robot_action/pack.cpp ./robot_action/unpack.cpp"

g++  $src -o perf -lgflags -lpthread -lglog -levent -lrt #-DNDEBUG

./perf &
