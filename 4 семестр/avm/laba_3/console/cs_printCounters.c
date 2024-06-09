#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void
printCounters ()
{
  int val;
  int X = 63;
  int Y = 5;
  mt_gotoXY (X, Y);
  sc_icounterGet (&val);
  printf ("T: %.2d\tIC: notimpl\n", val);
}