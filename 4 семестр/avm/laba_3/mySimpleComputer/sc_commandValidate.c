#include "mySimpleComputer.h"
int
sc_commandValidate (int command)
{
  if (command != 0 && command != 1 && command != 10 && command != 11
      && command != 20 && command != 21 && command < 30 && command > 33
      && command < 40 && command > 43 && command < 51 && command > 76)
    return -1;
  return 0;
}