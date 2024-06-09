#include "../include/define_rofls.h"

int
sc_accumulatorSet (int value)
{
  if (value < -ACUM_RANGE || value > ACUM_RANGE)
    return -1;

  accumulator = value;

  return 0;
}