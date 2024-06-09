#include <stdio.h>

#define ACUM_RANGE 10000
#define COMMAND_RANGE 100

#define FLAG_IGNORE_TACT 4
#define NUM_OF_FLAGS 4

static int accumulator;
static int command_counter;
static int flag_register;
