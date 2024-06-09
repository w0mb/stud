#include "mySimpleComputer.h"
int
sc_memorySet (int address, int value)
{
  if (address > 127 || address < 0 || value > MAXSIZE || value <= MINSIZE)
    {
      return -1;
    }
  else
    {
      _RAM[address] = value;
    }
  return 0;
}