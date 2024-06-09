#include "../include/define_rofls.h"

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (sign < 0 || sign > 1 || command < 0 || command > 127 || operand < 0
      || operand > 127 || value == NULL)
    {
      return -1;
    }

  *value = (sign << 14) | (command << 7) | operand;

  return 0;
}