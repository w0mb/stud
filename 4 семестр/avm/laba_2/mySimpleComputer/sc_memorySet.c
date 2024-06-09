#include "../include/define_rofls.h"
static int memory[128];

int
sc_memorySet (int address, int value)
{
  if (address >= 0 && address <= 128)
    {
      memory[address] = value;
      return 0;
    }
  return -1;
}