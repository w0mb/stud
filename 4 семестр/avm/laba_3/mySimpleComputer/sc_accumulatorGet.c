#include "mySimpleComputer.h"
int
sc_accumulatorGet (int *value)
{
  if (value == NULL)
    return -1;
  *value = accumulator;
  return 0;
}