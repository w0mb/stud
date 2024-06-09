#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void
printTerm (int address, int input)
{
  int X = 67;
  int Y = 19;
  mt_gotoXY (X, Y);
  if (input == 0)
    { // output
      if (!strcmp (_SCROLL_BUFFER[0], ""))
        {
          printf ("%.3d> %d\n", address, _RAM[address]);
        }
      else
        {
          printf ("%.3d> %d\n", address, _RAM[address]);
          mt_gotoXY (X, Y + 1);
          printf ("%s\n", _SCROLL_BUFFER[0]);
          mt_gotoXY (X, Y + 2);
          printf ("%s\n", _SCROLL_BUFFER[1]);
          mt_gotoXY (X, Y + 3);
          printf ("%s\n", _SCROLL_BUFFER[2]);
          mt_gotoXY (X, Y + 4);
          printf ("%s\n", _SCROLL_BUFFER[3]);
        }
      for (int i = 0; i < 5; i++)
        {
          if (_SCROLL_BUFFER[i] == NULL)
            {
              sprintf (_SCROLL_BUFFER[i], "%.3d> %d", address, _RAM[address]);
            }
          else if (i == 4)
            {
              sprintf (_SCROLL_BUFFER[4], "%s", _SCROLL_BUFFER[3]);
              sprintf (_SCROLL_BUFFER[3], "%s", _SCROLL_BUFFER[2]);
              sprintf (_SCROLL_BUFFER[2], "%s", _SCROLL_BUFFER[1]);
              sprintf (_SCROLL_BUFFER[1], "%s", _SCROLL_BUFFER[0]);
              sprintf (_SCROLL_BUFFER[0], "%.3d> %d", address, _RAM[address]);
            }
        }
    }
  else // input
    {
      if (!strcmp (_SCROLL_BUFFER[0], ""))
        {
          printf ("%.3d< ", address);
          sprintf (_SCROLL_BUFFER[4], "%s", _SCROLL_BUFFER[3]);
          sprintf (_SCROLL_BUFFER[3], "%s", _SCROLL_BUFFER[2]);
          sprintf (_SCROLL_BUFFER[2], "%s", _SCROLL_BUFFER[1]);
          sprintf (_SCROLL_BUFFER[1], "%s", _SCROLL_BUFFER[0]);
          scanf ("%d", &_RAM[address]);
          printf ("\n");
          sprintf (_SCROLL_BUFFER[0], "%.3d< %d", address, _RAM[address]);
          printCell (address, white, black);
        }
      else
        {
          printf ("%.3d<                    \n", address);
          mt_gotoXY (X, Y + 1);
          printf ("%s\n", _SCROLL_BUFFER[0]);
          mt_gotoXY (X, Y + 2);
          printf ("%s\n", _SCROLL_BUFFER[1]);
          mt_gotoXY (X, Y + 3);
          printf ("%s\n", _SCROLL_BUFFER[2]);
          mt_gotoXY (X, Y + 4);
          printf ("%s\n", _SCROLL_BUFFER[3]);
          mt_gotoXY (X + 5, Y);
          sprintf (_SCROLL_BUFFER[4], "%s", _SCROLL_BUFFER[3]);
          sprintf (_SCROLL_BUFFER[3], "%s", _SCROLL_BUFFER[2]);
          sprintf (_SCROLL_BUFFER[2], "%s", _SCROLL_BUFFER[1]);
          sprintf (_SCROLL_BUFFER[1], "%s", _SCROLL_BUFFER[0]);
          scanf ("%d", &_RAM[address]);
          sprintf (_SCROLL_BUFFER[0], "%.3d< %d", address, _RAM[address]);
          printCell (address, white, black);
        }
    }
}