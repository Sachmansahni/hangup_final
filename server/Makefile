# Makefile
CC = gcc
CFLAGS = -Wall
AR = ar
ARFLAGS = rcs

all: server

server: server.o server_lib.o
	$(CC) $(CFLAGS) -o server server.o server_lib.o

server.o: server.c server_lib.h
	$(CC) $(CFLAGS) -c server.c

server_lib.o: server_lib.c server_lib.h
	$(CC) $(CFLAGS) -c server_lib.c

clean:
	rm -f *.o server
