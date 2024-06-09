#ifndef CONSOLE_H
#define CONSOLE_H
#include "myTerm.h"
#include <stdio.h>

extern char _SCROLL_BUFFER[5][64];

void printAccumulator ();
void printCell (int address, enum Colors fg, enum Colors bg);
void printCounters ();
void printDecodedCommand (int value);
void printFlags ();
void printTerm (int address, int input);
void printCommand ();

#endif