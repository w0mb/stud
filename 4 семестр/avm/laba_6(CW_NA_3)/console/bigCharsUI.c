#include "variables.h"
#include <console.h>
#include <myBigChars.h>
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <rk_structs.h>

int
bigCharsUI (void)
{
  int tmp;
  sc_memoryGet (cell, &tmp);
  if (!((tmp >> 15) & 1))
    {
      bc_printbigchar (bc[16], 63, 9, WHITE, DEFAULT);
    }
  else
    {
      bc_printbigchar (bc[17], 63, 9, WHITE, DEFAULT);
    }

  tmp &= ((1 << 15) - 1);

  for (int i = 0; i < 4; ++i)
    {
      int ch = (tmp & (0xF << (4 * (3 - i)))) >> (4 * (3 - i));
      bc_printbigchar (bc[ch], 62 + 8 * (i + 1) + 2 * (i + 1), 9, WHITE,
                       DEFAULT);
    }
  return 0;
}