#include "mySimpleComputer.h"
int
sc_accumulatorSet (int value)
{
  if (value < MAXSIZE && value >= MINSIZE)
    {
      accumulator = value;
      return 0;
    }
  else
    return -1;
}