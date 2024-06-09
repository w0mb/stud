#include "mySimpleComputer.h"
int
sc_memorySave (char *filename)
{
  int i;
  FILE *fp;
  fp = fopen (filename, "wb");
  if (fp == NULL)
    {
      return -1;
    }
  for (i = 0; i < _RAM_SIZE; i++)
    {
      if (fprintf (fp, "%d", _RAM[i]) < 0)
        return -1;
    }
  fclose (fp);
  return 0;
}