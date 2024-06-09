#ifndef MYSIMPLECOMPUTER_H
#define MYSIMPLECOMPUTER_H

#include <stdint.h>
#include <stdio.h>

#define _RAM_SIZE 128
#define MAXSIZE 0x7FFF
#define MINSIZE -0x8000

#define FLAG_OVERFLOW 0
#define FLAG_DIVIDE_BY_ZERO 1
#define FLAG_SIGSEV 2
#define FLAG_BAD_COMMAND 3
#define FLAG_IGNORE_TACT 4

extern int _RAM[_RAM_SIZE];
extern int_fast16_t icounter;
extern int_fast16_t accumulator;
extern int_fast8_t reg;

int sc_accumulatorGet (int *value);
int sc_accumulatorInit ();

int sc_accumulatorSet (int value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandValidate (int command);
int sc_icounterGet (int *value);

int sc_icounterInit ();

int sc_icounterSet (int value);
int sc_memoryGet (int address, int *value);

int sc_memoryInit ();
int sc_memoryLoad (char *filename);
int sc_memorySave (char *filename);
int sc_memorySet (int address, int value);

int sc_regGet (int registr, int *value);

int sc_regInit ();

int sc_regSet (int registr, int value);
#endif