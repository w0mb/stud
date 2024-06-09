#include "myTerm.h"

int
mt_setbgcolor (enum Colors color)
{
  char *terminal = ttyname (1);

  int fd = open (terminal, O_WRONLY);

  if (fd == -1)
    {
      fprintf (stderr, "failed opening the terminal\n");
      return -1;
    }

  char buf[20];
  int len = snprintf (buf, sizeof (buf), "\E[4%dm", color);
  write (fd, buf, len);
  return 0;
}