#include <mySimpleComputer.h>
#include <myTerm.h>
#include <sc.h>

void
printDecodedCommand (int value)
{
  mt_gotoXY (2, 18);
  mt_setfgcolor (WHITE);
  if ((value >> 15) & 1)
    {
      printf (
          "dec: -%d | oct: -%o | hex: -%X | bin: ", value & ((1 << 15) - 1),
          value & ((1 << 15) - 1), value & ((1 << 15) - 1));
    }
  else
    {
      printf ("dec: %d | oct: %o | hex: %X | bin: ", value, value, value);
    }

  for (int i = 15; i >= 0; i--)
    {
      printf ("%d", (value >> i) & 1);
    }
  mt_setfgcolor (DEFAULT);
}
