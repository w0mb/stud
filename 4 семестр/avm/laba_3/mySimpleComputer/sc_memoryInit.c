#include "mySimpleComputer.h"
int
sc_memoryInit ()
{
  int i;
  for (i = 0; i < _RAM_SIZE; i++)
    {
      _RAM[i] = 0;
    }
  return 0;
}