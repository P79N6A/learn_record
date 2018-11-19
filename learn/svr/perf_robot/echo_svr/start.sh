#!/bin/bash
# by orientlu

mkdir -p ./log/

g++ ./echo_svr.cpp  -o echo_svr -lgflags -lpthread -lglog -levent

./echo_svr  &
