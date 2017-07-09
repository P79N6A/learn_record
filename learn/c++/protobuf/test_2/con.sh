#!/bin/bash

protoc --proto_path=.  --cpp_out=. message.proto
