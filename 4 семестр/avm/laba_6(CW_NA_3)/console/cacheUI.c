#include <console.h>
#include <myBigChars.h>
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <rk_structs.h>

int
cacheUI ()
{
  for (int i = 0; i < CACHE_SIZE; ++i)
    {
      mt_gotoXY (2, 21 + i);

      if (cache[i].address == -1)
        {
          printf ("-");
        }
      else
        {
          printf ("%02d:", cache[i].address);
          for (int j = 0; j < CACHE_LINE_SIZE; ++j)
            {
              if ((cache[i].data[j] >> 15) & 1)
                {
                  printf (" -%04X", (cache[i].data[j]) & ((1 << 15) - 1));
                }
              else
                {
                  printf (" +%04X", cache[i].data[j] & ((1 << 15) - 1));
                }
            }
        }
    }
  return 0;
}