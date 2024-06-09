CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 
SRCDIR = .
OBJ_DIR = ./obj
LIBDIR = .

#SRCS := $(wildcard $(SRCDIR)/*.c)
SRCS := $(filter-out $(SRCDIR)/main.c, $(wildcard $(SRCDIR)/*.c))
OBJS := $(patsubst $(SRCDIR)/%,$(OBJ_DIR)/%,$(SRCS:.c=.o))

LIB_FILE = $(LIBDIR)/libMySimpleComputer.a

.PHONY: all clean

all: $(LIB_FILE)

$(LIB_FILE): $(OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRCDIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -I../include -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: all $(SRCDIR) $(SRCDIR)console.out

$(SRCDIR)console.out: $(OBJ_DIR)/main.o $(LIB_FILE)
	$(CC) $(CFLAGS) -o $@ $^
$(OBJ_DIR)main.o: main.c 
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_DIR) $(LIB_FILE) *.bin





# all: $(OBJ_DIR) $(DIR_OUT)pr01.out
# $(DIR_OUT)pr01.out: $(OBJ_DIR)main.o $(OBJ_DIR)libsc.a 
# 	$(CC) $(CFLAGS) -o $@ $^
# $(OBJ_DIR)main.o: main.c 
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)libsc.a: $(OBJ_DIR)sc_memoryInit.o $(OBJ_DIR)sc_memoryGet.o $(OBJ_DIR)sc_memorySet.o $(OBJ_DIR)sc_memorySave.o $(OBJ_DIR)sc_memoryLoad.o $(OBJ_DIR)sc_regSet.o $(OBJ_DIR)sc_regInit.o $(OBJ_DIR)sc_regGet.o $(OBJ_DIR)sc_commandEncode.o $(OBJ_DIR)sc_commandDecode.o $(OBJ_DIR)sc_commandValidate.o $(OBJ_DIR)printAccumulator.o $(OBJ_DIR)printCell.o $(OBJ_DIR)printCounters.o $(OBJ_DIR)printDecodedCommand.o $(OBJ_DIR)printFlags.o $(OBJ_DIR)sc_accumulatorInit.o $(OBJ_DIR)sc_accumulatorGet.o $(OBJ_DIR)sc_accumulatorSet.o $(OBJ_DIR)sc_icounterInit.o $(OBJ_DIR)sc_icounterSet.o $(OBJ_DIR)sc_icounterGet.o
# 	ar rcs $@ $^
#$(OBJ_DIR)sc_memoryInit.o:  sc_memoryInit.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_memoryGet.o:  sc_memoryGet.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_memorySet.o:  sc_memorySet.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_memorySave.o:  sc_memorySave.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_memoryLoad.o:  sc_memoryLoad.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_regSet.o:  sc_regSet.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_regInit.o:  sc_regInit.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_regGet.o:  sc_regGet.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_commandEncode.o:  sc_commandEncode.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_commandDecode.o:  sc_commandDecode.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_commandValidate.o:  sc_commandValidate.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)printAccumulator.o:  printAccumulator.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)printCell.o: printCell.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)printCounters.o: printCounters.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)printDecodedCommand.o: printDecodedCommand.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)printFlags.o: printFlags.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_accumulatorInit.o: sc_accumulatorInit.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_accumulatorGet.o: sc_accumulatorGet.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_accumulatorSet.o: sc_accumulatorSet.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_icounterInit.o: sc_icounterInit.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_icounterSet.o: sc_icounterSet.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
# $(OBJ_DIR)sc_icounterGet.o: sc_icounterGet.c
# 	$(CC) -c $(CFLAGS) -o $@ $^
