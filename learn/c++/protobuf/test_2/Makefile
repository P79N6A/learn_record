# orientlu test protobuf
# 20170707
all: cpp
cpp: test2

test2: main.cpp message.pb.cc
	pkg-config --cflags protobuf
	c++ main.cpp message.pb.cc -o $@ `pkg-config --cflags --libs protobuf`
	@echo "Crete $@"

.PHONY: all cpp clean
clean:
	@rm -f test2
	@echo "Clean .."
