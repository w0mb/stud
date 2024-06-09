CC = gcc
CFLAGS = -I../include -c -Wall -Wextra
SOURCES = $(wildcard *.c)

%.o: %.c
	$(CC) $(CFLAGS) $<

all:  $(SOURCES:.c=.o)

clean:
	rm -rf *.o

.PHONY: SOURCES all clean
