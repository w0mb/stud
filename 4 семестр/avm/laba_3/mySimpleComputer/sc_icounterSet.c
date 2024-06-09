#include "mySimpleComputer.h"
int
sc_icounterSet (int value)
{
  if (value < MAXSIZE && value >= MINSIZE)
    {
      icounter = value;
      return 0;
    }
  else
    return -1;
}