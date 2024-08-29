
CC = gcc
CFLAGS = -Wall
AR = ar
ARFLAGS = rcs

all: client

client: client.o client_lib.o
	$(CC) $(CFLAGS) -o client client.o client_lib.o

client.o: client.c client_lib.h
	$(CC) $(CFLAGS) -c client.c

client_lib.o: client_lib.c client_lib.h
	$(CC) $(CFLAGS) -c client_lib.c

clean:
	rm -f *.o client
