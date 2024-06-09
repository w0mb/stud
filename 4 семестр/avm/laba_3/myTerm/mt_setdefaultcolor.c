#include "myTerm.h"

int
mt_setdefaultcolor ()
{
  int retcode = 0;
  retcode = mt_setbgcolor (black);
  if (retcode != 0)
    return -1;
  retcode = mt_setfgcolor (white);
  if (retcode != 0)
    return -1;
  return 0;
}