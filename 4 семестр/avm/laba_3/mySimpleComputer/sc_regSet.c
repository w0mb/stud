#include "mySimpleComputer.h"
int
sc_regSet (int registr, int value)
{
  if (registr <= FLAG_IGNORE_TACT && registr >= FLAG_OVERFLOW)
    {
      if (value)
        {
          reg = reg | (1 << registr);
        }
      else
        {
          reg = reg & ~(1 << registr);
        }
      return 0;
    }
  else
    return -1;
}