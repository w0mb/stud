#include "../include/define_rofls.h"
static int memory[128];

int
sc_memoryLoad (char *filename)
{
  if (filename != NULL)
    {
      FILE *fp = fopen (filename, "rb");
      if (fp == NULL)
        {
          printf ("Failed to open file for reading.\n");
          return -1;
        }

      if (fread (memory, sizeof (int), 128, fp) != 128)
        {
          printf ("Error writing to file.\n");
          fclose (fp);
          return -1;
        }

      fclose (fp);
      return 0;
    }
  return -1;
}
