# orientlu test protobuf
# 20170707
all: cpp
cpp: test1

protoc_middleman: message.proto
	protoc --proto_path=.  --cpp_out=. message.proto
	@echo "Create proto.cc/h"

test1: main.cpp protoc_middleman
	pkg-config --cflags protobuf
	c++ main.cpp message.pb.cc -o test1 `pkg-config --cflags --libs protobuf`
	@echo "Crete $@"

.PHONY: all cpp clean
clean:
	@rm -f test1
	@rm -f message.pb.*
	@echo "Clean .."
