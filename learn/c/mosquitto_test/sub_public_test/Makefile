CC = gcc
CFLAGS = -Wall -ggdb

LDFLAGS = -lmosquitto -lpthread

all : mosquitto_client

mosquitto_client : mysql_log.o
	${CC} $^ -o $@ ${LDFLAGS}

mysql_log.o : mysql_log.c
	${CC} -c $^ -o $@ ${CFLAGS}


.PHONY: all clean
clean : 
	-rm -f *.o mosquitto_client 
