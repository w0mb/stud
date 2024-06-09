// memory, registers, comands

#define _RAM_SIZE 128
#define MAXSIZE 0x7FFF
#define MINSIZE -0x8000

#define FLAG_OVERFLOW (1 << 0)
#define FLAG_DIVIDE_BY_ZERO 1
#define FLAG_SIGSEV 2
#define FLAG_ZERO (1 << 1)
#define FLAG_SIGN 3
#define FLAG_BAD_COMMAND 3

//----------------------------control.c-----------------------------------------//

int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandValidate (int command);

//----------------------------register.c-----------------------------------------//

int sc_regInit (void);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int value);
int sc_accumulatorInit (void);
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);
int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_icounterGet (int *value);

//----------------------------memory.c-----------------------------------------//

int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);