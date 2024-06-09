#include "../include/define_rofls.h"

int
sc_icounterGet (int *value)
{
  if (value == NULL)
    return -1;

  *value = command_counter;

  return 0;
}
