#include "mySimpleComputer.h"
int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (sign < 0 || sign > 1 || command < 0 || command > 0x7F || operand < 0x0
      || operand > 0x7F || value == NULL)
    return -1;
  *value = (sign << 14) | (command << 7) | operand;
  return 0;
}