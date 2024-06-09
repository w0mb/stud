#include "myTerm.h"

int
mt_gotoXY (int x, int y)
{

  int fd = open (ttyname (1), O_WRONLY);
  if (fd == -1)
    {
      fprintf (stderr, "failed opening the terminal\n");
      return -1;
    }
  char buf[20];
  int len = snprintf (buf, sizeof (buf), "\E[%d;%dH", y, x);
  write (fd, buf, len);
  close (fd);
  return 0;
}
