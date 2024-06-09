CC = gcc
CFLAGS = -I../include -c -Wall -Wextra
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

libMyTerm.a: $(OBJECTS)
	ar rcs $@ $<

all: libMySC.a

$(OBJECTS): $(SOURCES)

clean:
	rm -rf *.o *.a

.PHONY: OBJECTS all clean
