#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void
printFlags ()
{
  int X = 92;
  int Y = 2;
  mt_gotoXY (X, Y);
  int value = 0;
  sc_regGet (FLAG_OVERFLOW, &value);
  printf ("%c ", (value == 0) ? '_' : 'P');
  sc_regGet (FLAG_DIVIDE_BY_ZERO, &value);
  printf ("%c ", (value == 0) ? '_' : '0');
  sc_regGet (FLAG_SIGSEV, &value);
  printf ("%c ", (value == 0) ? '_' : 'M');
  sc_regGet (FLAG_IGNORE_TACT, &value);
  printf ("%c ", (value == 0) ? '_' : 'T');
  sc_regGet (FLAG_BAD_COMMAND, &value);
  printf ("%c\n", (value == 0) ? '_' : 'E');
}