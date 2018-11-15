#!/bin/bash
# by orientlu
g++ ./client.c  -levent_core -o client
g++ ./server.c  -levent_core -o server
