#include "mySimpleComputer.h"
int
sc_memoryLoad (char *filename)
{
  int i;
  FILE *fp;
  fp = fopen (filename, "rb");
  if (fp == NULL)
    {
      return -1;
    }
  int buffer[_RAM_SIZE];
  for (i = 0; i < _RAM_SIZE; i++)
    {
      if (fscanf (fp, "%d", &buffer[i]) < 0)
        return -1;
    }
  for (i = 0; i < _RAM_SIZE; i++)
    {
      _RAM[i] = buffer[i];
    }
  fclose (fp);
  return 0;
}