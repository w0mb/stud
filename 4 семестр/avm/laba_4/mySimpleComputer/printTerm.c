#include <mySimpleComputer.h>
#include <myTerm.h>
#include <sc.h>

void
printTerm (int address, int input)
{

  mt_setfgcolor (WHITE);
  static int buffer[4] = { 0 };
  static int currentIndex = 0;

  if (input == 1)
    {
      buffer[currentIndex] = memory[address];
      currentIndex = (currentIndex + 1) % 4;
    }

  if (input == 0)
    {

      for (int i = 0; i < 4; i++)
        {
          mt_gotoXY (73, 21 + i);
          printf ("%d", address + i);
          printf ("> ");
          int index = (currentIndex) % 4;
          printf ("+%04X", buffer[index + i]);
        }
    }
  mt_setfgcolor (DEFAULT);
  // printf ("\n");
}
