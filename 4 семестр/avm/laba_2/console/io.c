#include "../include/mrc.h"
#include <stdio.h>

void
printCell (int address)
{
  int value;
  if (sc_memoryGet (address, &value) == 0)
    {
      int sign, command, operand;
      sc_commandDecode (value, &sign, &command, &operand);
      printf ("+%04X %04X %04X\n", sign, command, operand);
    }
  else
    {
      printf ("Memory read error\n");
    }
}

void
printFlags (void)
{
  int flag_overflow, flag_zero, flag_sign;
  sc_regGet (FLAG_OVERFLOW, &flag_overflow);
  sc_regGet (FLAG_ZERO, &flag_zero);
  sc_regGet (FLAG_SIGN, &flag_sign);

  printf ("Overflow: %c, Zero: %c, Sign: %c\n", flag_overflow ? '1' : '0',
          flag_zero ? '1' : '0', flag_sign ? '1' : '0');
}

void
printDecodedCommand (int value)
{
  int sign, command, operand;
  sc_commandDecode (value, &sign, &command, &operand);
  printf ("Decimal: %d, Octal: %o, Hex: %X, Binary: ", value, value, value);
  for (int i = 15; i >= 0; i--)
    {
      printf ("%d", (value >> i) & 1);
    }
  printf ("\n");
}

void
printAccumulator (void)
{
  int value;
  sc_accumulatorGet (&value);
  printf ("Accumulator value: %d\n", value);
}

void
printCounters (void)
{
  int icount;
  sc_icounterGet (&icount);
  printf ("Instruction counter: %d\n", icount);
}
