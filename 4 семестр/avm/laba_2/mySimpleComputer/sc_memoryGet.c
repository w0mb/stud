#include "../include/define_rofls.h"
static int memory[128];

int
sc_memoryGet (int address, int *value)
{
  if (value != NULL)
    {
      memory[address] = *value;
      return 0;
    }
  return -1;
}
