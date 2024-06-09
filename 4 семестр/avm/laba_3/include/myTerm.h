#ifndef MYTERMINAL
#define MYTERMINAL

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

enum Colors
{
  black,
  red,
  green,
  yellow,
  blue,
  magenta,
  cyan,
  white
};

int mt_clrscr ();
int mt_delline ();
int mt_gotoXY (int x, int y);
int mt_setbgcolor (enum Colors color);
int mt_setcursorvisible (int value);
int mt_setdefaultcolor ();
int mt_setfgcolor (enum Colors color);

#endif