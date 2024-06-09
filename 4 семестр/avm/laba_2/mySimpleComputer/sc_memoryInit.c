#include "../include/define_rofls.h"
static int memory[128];

int
sc_memoryInit (void)
{
  for (size_t i = 0; i < 128; i++)
    {
      memory[i] = 1;
    }
}