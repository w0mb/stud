#include "mySimpleComputer.h"
int
sc_memoryGet (int address, int *value)
{
  if (address > 127 || address < 0 || value == NULL)
    {
      return -1;
    }
  else
    {
      *value = _RAM[address];
    }
  return 0;
}