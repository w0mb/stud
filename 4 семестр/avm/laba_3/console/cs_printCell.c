#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void
printCell (int address, enum Colors fg, enum Colors bg)
{
  int sign, command, operand;
  if (mt_setfgcolor (fg))
    {
      printf ("Error: fg color setting error");
      return;
    }
  if (mt_setbgcolor (bg))
    {
      printf ("Error: bg color setting error");
      return;
    }
  int X = 6 * (address % 10);
  int Y = address / 10;
  int padding = 1;
  if (mt_gotoXY (X + padding, Y + padding))
    {
      printf ("Error: gotoXY error");
      return;
    }
  if (sc_commandDecode (_RAM[address], &sign, &command, &operand) == -1)
    {
      printf ("Error: decode error");
      return;
    }
  printf ("%c%02x%02x\n", (sign == 1) ? '+' : '-', command, operand);
}