#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void
printAccumulator ()
{
  int val;
  int X = 63;
  int Y = 2;
  mt_gotoXY (X, Y);
  sc_accumulatorGet (&val);
  printf ("sc: %.4d hex: %.4x\n", val, val);
}