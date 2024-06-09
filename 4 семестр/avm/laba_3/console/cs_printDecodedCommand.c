#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void
printDecodedCommand (int value)
{
  int X = 2;
  int Y = 15;
  mt_gotoXY (X, Y);
  printf ("dec: %d | octa: %o | hex: %x  binary: ", value, value, value);
  char arr[sizeof (int) * 8];
  for (long long unsigned int i = 0u; i < sizeof (int) * 8; i++)
    {
      if (value & 0x1)
        arr[i] = '1';
      else
        arr[i] = '0';
      value >>= 1;
    }
  int flag = 0;
  for (int i = sizeof (int) * 8 - 1; i >= 0; i--)
    {
      if (arr[i] == '1' && !flag)
        {
          flag = 1;
        }
      else if (!flag)
        continue;
      printf ("%c", arr[i]);
    }
  printf ("\n");
}