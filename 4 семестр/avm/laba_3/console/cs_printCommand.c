#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void
printCommand ()
{
  int X = 92;
  int Y = 5;
  mt_gotoXY (X, Y);
  int value;
  sc_icounterGet (&value);
  sc_memoryGet (value, &value);
  int sign, command, operand;
  sc_commandDecode (value, &sign, &command, &operand);
  int returncode = sc_commandValidate (command);
  if (returncode != 0 || sign != 0)
    {
      printf ("  !  + FF : FF\n");
    }
  else
    {
      printf ("    + %d : %d\n", command, operand);
    }
}