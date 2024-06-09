#include "mySimpleComputer.h"
int
sc_regInit ()
{
  reg = 0;
  reg = reg | (1 << FLAG_IGNORE_TACT);
  return 0;
}