#include <console.h>
#include <myBigChars.h>
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <rk_structs.h>

int
memoryUI (void)
{
  for (int i = 0; i < 13; ++i)
    {
      for (int j = 0; j < 10; ++j)
        {
          int cellIndex = i * 10 + j;

          if (cellIndex < 128)
            {

              mt_gotoXY (2 + (5 * j + j), 2 + i);
              int tmp = memory[cellIndex];

              if (cellIndex == cell)
                {
                  mt_setbgcolor (WHITE);
                }
              else
                {
                  mt_setbgcolor (BLACK);
                }
              if (cellIndex == cell)
                {

                  mt_setfgcolor (BLACK);
                }
              else
                {
                  mt_setfgcolor (WHITE);
                }

              if ((tmp >> 15) & 1)
                {
                  printf ("-%04X", tmp & ((1 << 15) - 1));
                }

              else
                {
                  printf ("+%04X", tmp & ((1 << 15) - 1));
                }

              mt_setdefaultcolors ();
            }
        }
    }
  return 0;
}