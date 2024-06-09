#include "../include/define_rofls.h"
static int memory[128];

int
sc_memorySave (char *filename)
{
  if (filename != NULL)
    {
      FILE *fp = fopen (filename, "wb");
      if (fp == NULL)
        {
          printf ("Failed to open file for writing.\n");
          return -1;
        }

      if (fwrite (memory, sizeof (int), 128, fp) != 128)
        {
          printf ("Error reading to file.\n");
          fclose (fp);
          return -1;
        }

      fclose (fp);
      return 0;
    }
  return -1;
}