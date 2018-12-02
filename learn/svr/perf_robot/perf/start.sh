#!/bin/bash
# by orientlu

rm ./robot_perf -f

pwd

src="./main.cpp ./mother.cpp ./naughty_kid.cpp ./flag.cpp ./robot.cpp ./robot_action/pack.cpp ./robot_action/unpack.cpp"

#g++  $src -o robot_perf -L ./lib -lpthread -lrt -lgflags  -lglog -levent  #-DNDEBUG
g++  $src -o robot_perf -lpthread -lrt -lgflags  -lglog -levent  #-DNDEBUG

./robot_perf &
