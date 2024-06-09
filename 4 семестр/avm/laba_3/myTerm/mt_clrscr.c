#include "myTerm.h"

int
mt_clrscr ()
{
  int fd = open (ttyname (1), O_RDWR);
  if (fd == -1)
    {
      fprintf (stderr, "failed opening the terminal\n");
      return -1;
    }
  write (fd, "\E[H\E[J\E[0;0H", 13);
  close (fd);
  return 0;
}