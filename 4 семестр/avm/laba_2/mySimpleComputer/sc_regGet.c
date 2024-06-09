#include "../include/define_rofls.h"

int
sc_regGet (int reg, int *value)
{
  if (reg < 0 || reg >= NUM_OF_FLAGS || value == NULL)
    {
      return -1;
    }

  value = (flag_register >> (reg - 1)) & 1;

  return 0;
}