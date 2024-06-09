#include "myTerm.h"

int
mt_setfgcolor (enum Colors color)
{
  int fd = open (ttyname (1), O_WRONLY);
  if (fd == -1)
    {
      fprintf (stderr, "failed opening the terminal\n");
      return -1;
    }
  char buf[20];
  int len = snprintf (buf, sizeof (buf), "\E[3%dm", color);
  write (fd, buf, len);
  close (fd);
  return 0;
}