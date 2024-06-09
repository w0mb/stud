#include "../include/mrc.h"
#include <stdio.h>

int
main ()
{
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_regInit ();
  sc_icounterInit ();

  for (int i = 0; i < 20; i++)
    {
      if (sc_memorySet (i, (10000 + i * i * i)) == -1)
        {
          printf ("Error: failed to set value to memory. address: %d\n", i);
        }
      int value = 0;
      if (sc_memoryGet (i, &value) == -1)
        {
          printf ("Error: failed to get value from memory. address: %d\n", i);
        }
      printf ("\n");
      printCell (value);
    }
  printf ("\n\nsc_memorySet Status code after inputting invalid value: %d\n",
          sc_memorySet (1, 10000000));
  sc_regSet (FLAG_BAD_COMMAND, 1);
  sc_regSet (FLAG_OVERFLOW, 1);
  printf ("\nflags bad command and overflow raised:\n");
  printFlags ();
  printf ("\n\nsc_regSet status code after inputting invalid register: %d\n",
          sc_regSet (100, 1));
  sc_accumulatorSet (42);
  int value = 0;
  sc_accumulatorGet (&value);
  printf ("\nresult of sc_accumulatorGet: %d\n", value);
  sc_icounterSet (100);
  sc_icounterGet (&value);
  printf ("\nresult of sc_icounterGet: %d\n", value);
  printf (
      "\nsc_icounterSet status code after inputting invalid register: %d\n",
      sc_icounterSet (1000000000));
  printf ("\nresult of printCell(5): \n");
  printCell (5);
  printf ("\nprinting sc_commandDecode for accumulator: \n");
  int sign, command, operand;
  sc_accumulatorGet (&value);
  sc_commandDecode (value, &sign, &command, &operand);
  printf ("%c%02x%02x ", (sign == 1) ? '+' : '-', command, operand);
  sign = 1;
  command = 0x0A;
  operand = 0x0A;
  sc_commandEncode (sign, command, operand, &value);
  printf ("\nprinting sc_commandEncode value for READ command: \n");
  printDecodedCommand (value);
  sc_commandDecode (value, &sign, &command, &operand);

  printf ("\nsign:%c command:%02x operand:%02x ", (sign == 1) ? '+' : '-',
          command, operand);

  return 0;
}
