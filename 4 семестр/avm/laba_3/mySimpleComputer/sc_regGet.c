#include "mySimpleComputer.h"
int
sc_regGet (int registr, int *value)
{
  if (registr > FLAG_IGNORE_TACT || registr < FLAG_OVERFLOW || value == NULL)
    {
      return -1;
    }
  else
    {
      *value = (reg >> registr) & 0x1;
      return 0;
    }
}