#include "../include/define_rofls.h"

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  if (sign == NULL || command == NULL || operand == NULL)
    {
      return -1;
    }

  *sign = (value >> 15) & 1;
  *command = (value >> 7) & 127;
  *operand = value & 127;

  return 0;
}