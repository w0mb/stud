#include "../include/define_rofls.h"

int
sc_regSet (int reg, int value)
{
  if (reg < 0 || reg >= NUM_OF_FLAGS)
    {
      return -1;
    }

  if (value == 0)
    {
      flag_register &= ~(1 << reg);
    }
  else
    {
      flag_register |= (1 << reg);
    }

  return 0;
}