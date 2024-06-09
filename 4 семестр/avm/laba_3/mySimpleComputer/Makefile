CC = gcc
CFLAGS = -I../include -c -Wall -Wextra
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

libMySC.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

all: libMySC.a

clean:
	rm -rf *.o libMySC.a

.PHONY: all clean

$(OBJECTS): $(SOURCES)
