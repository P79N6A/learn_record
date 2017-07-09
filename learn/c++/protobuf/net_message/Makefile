# orientlu test protobuf
# 20170707
all: cpp
cpp: server client

protoc_middleman: message.proto
	protoc --proto_path=.  --cpp_out=. message.proto
	@echo "Create proto.cc/h"

server: server.cpp protoc_middleman
	pkg-config --cflags protobuf
	c++ server.cpp message.pb.cc -o $@ `pkg-config --cflags --libs protobuf`
	@echo "Crete $@"

client: client.cpp protoc_middleman
	pkg-config --cflags protobuf
	c++ client.cpp message.pb.cc -o $@ `pkg-config --cflags --libs protobuf`
	@echo "Crete $@"

.PHONY: all cpp clean
clean:
	@rm -f server
	@rm -f client
	@rm -f message.pb.*
	@echo "Clean .."
