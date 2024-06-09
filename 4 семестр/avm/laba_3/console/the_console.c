#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

/* struct winsize {
    unsigned short ws_row;
    unsigned short ws_col;
    unsigned short ws_xpixel;
    unsigned short ws_ypixel;
}; */

int
main ()
{
  char *terminal = ttyname (1);

  int fd = open (terminal, O_WRONLY);

  if (fd == -1)
    {
      fprintf (stderr, "failed opening the terminal\n");
      return -1;
    }
  if (!isatty (1))
    {
      return -1;
    }
  struct winsize ws;
  if (!ioctl (1, TIOCGWINSZ, &ws))
    {
      if (ws.ws_row < 30 || ws.ws_col < 95)
        {
          printf ("Not enough size in the terminal. Sorry!");
          return -1;
        }
    }
  else
    return -1;
  close (fd);

  for (int i = 0; i < 5; i++)
    {
      strcpy (_SCROLL_BUFFER[i], "");
    }
  mt_clrscr ();
  sc_regInit ();
  sc_icounterInit ();
  sc_memoryInit ();
  sc_accumulatorInit ();
  printAccumulator ();
  printCell (0, black, white);
  for (int i = 1; i < _RAM_SIZE; i++)
    {
      printCell (i, white, black);
    }
  printCommand ();
  printCounters ();
  printDecodedCommand (_RAM[0]);
  printFlags ();
  printTerm (0, 1);
  printTerm (4, 1);
  printTerm (12, 1);
  printTerm (64, 1);
  printTerm (34, 1);
  printTerm (11, 1);
  printTerm (0, 0);
  getchar ();
  printTerm (12, 0);
  getchar ();
  return 0;
}