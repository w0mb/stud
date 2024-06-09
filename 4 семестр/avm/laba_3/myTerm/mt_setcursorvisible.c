#include <myTerm.h>

int
mt_setcursorvisible (int value)
{
  char *terminal = ttyname (1);

  int fd = open (terminal, O_WRONLY);

  if (fd == -1)
    {
      fprintf (stderr, "failed opening the terminal\n");
      return -1;
    }
  if (value != 0)
    {
      write (1, "\E[?25h\E[?8c", 12);
    }
  else
    {
      write (1, "\E[?25l\E[?1c", 12);
    }
  close (fd);
  return 0;
}