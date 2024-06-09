#include "myTerm.h"

int
mt_delline ()
{
  int fd = open (ttyname (1), O_WRONLY);
  if (fd == -1)
    {
      fprintf (stderr, "failed opening the terminal\n");
      return -1;
    }
  write (fd, "\E[M", 4);

  close (fd);
  return 0;
}