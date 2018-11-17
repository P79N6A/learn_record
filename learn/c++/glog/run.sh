#!/bin/bash
# by orientlu

rm ./log -rf

g++ ./main.cpp  -lglog -lgflags_nothreads -o glog_test #-DNDEBUG

mkdir -p ./log

## http://rpg.ifi.uzh.ch/docs/glog.html

./glog_test --log_dir=./log/ --logtostderr=1 --minloglevel=1
#--logtostderr=1 ## 输出到屏幕，不输出到 file
#--minloglevel= ... 默认值是 0，代表INFO (1 代表WARNING，2 代表ERROR，而 3 代表FATAL)
