#include "../include/define_rofls.h"

int
sc_icounterSet (int value)
{
  if (value < -COMMAND_RANGE || value > COMMAND_RANGE)
    return -1;

  command_counter = value;

  return 0;
}