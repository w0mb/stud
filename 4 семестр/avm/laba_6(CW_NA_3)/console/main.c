#include <console.h>
#include <fcntl.h>
#include <unistd.h>
#include <variables.h>

int
main (void)
{
  int value;

  if (!isatty (fileno (stdout)))
    {
      fprintf (stderr, "Launch");
      return 1;
    }

  int col = 0, row = 0;
  mt_getscreensize (&col, &row);
  if (col < 20 || row < 30)
    {
      fprintf (stderr, "The terminal screen is too small");
      return 1;
    }
  rk_myTermSave ();
  sc_memoryInit ();
  sc_regInit ();
  sc_icounterInit ();
  sc_accumulatorInit ();
  sc_initCache ();

  sc_regSet (IGNORING_TACT_PULSES, 1);
  count = 0;
  int buffer, ignoringImp, segmentationFault, incorrectCom, devZero, memX,
      memY;
  enum keys key;
  char name[20];
  char filename[128];
  signal (SIGALRM, IRC);
  signal (SIGUSR1, IRC);
  char bufferCh[10];
  uiAdd ();
  do
    {
      sc_regGet (IGNORING_TACT_PULSES, &ignoringImp);
      uiAdd ();
      rk_readKey (&key);
      if (ignoringImp)
        {
          sc_regGet (DIVISION_ERR_BY_ZERO, &devZero);
          sc_regGet (OUT_OF_MEMORY_BOUNDS, &segmentationFault);
          sc_regGet (INCORRECT_COMMAND_RECEIVED, &incorrectCom);

          if (devZero || segmentationFault || incorrectCom)
            {
              switch (key)
                {
                case RUN:
                  uiAdd ();
                  printf ("Input file name for load: ");
                  scanf ("%s", filename);
                  filename[strlen (filename) - 1] = '\0';
                  if (sc_memoryLoad (filename))
                    {
                      messageUI ((char *)"Failed to load memory", RED);
                      break;
                    }
                  else
                    messageUI ((char *)"Successful load", GREEN);
                  break;
                case SAVE:
                  printf ("Input file name for save > ");
                  scanf ("%s", filename);
                  if (sc_memorySave (filename))
                    {
                      messageUI ((char *)"Failed to save memory", RED);
                      break;
                    }
                  else
                    messageUI ((char *)"Successful save", GREEN);
                  break;
                case RESET:
                  raise (SIGUSR1);
                  break;
                }
            }
          else
            {
              switch (key)
                {
                case UP:
                  if (cell < 128)
                    {
                      if (cell <= 9)
                        {
                          cell = 120 + cell;
                        }
                      else
                        {
                          cell -= 10;
                        }
                      if (cell == 128 || cell == 129)
                        {
                          cell -= 10;
                        }
                    }
                  break;
                case DOWN:
                  if (cell < 128)
                    {
                      if (cell >= 120)
                        {
                          cell = cell - 120;
                        }
                      else
                        {
                          cell += 10;
                        }
                      if (cell == 128 || cell == 129)
                        {
                          cell = cell - 120;
                        }
                    }
                  break;
                case LEFT:
                  if (cell < 128)
                    {
                      if (!(cell % 10))
                        {
                          cell += 9;
                        }
                      else
                        {
                          cell--;
                        }
                    }

                  if (cell == 128 || cell == 129)
                    {
                      cell -= 2;
                    }
                  break;
                case RIGHT:
                  if (cell < 128)
                    {
                      if (!((cell + 1) % 10))
                        {
                          cell -= 9;
                        }
                      else
                        {
                          cell++;
                        }
                    }

                  if (cell == 128 || cell == 129)
                    {
                      cell -= 8;
                    }
                  break;
                case SAVE:
                  printf ("Input file name for save > ");
                  scanf ("%s", filename);
                  if (sc_memorySave (filename))
                    {
                      messageUI ((char *)"Failed to save memory", RED);
                      break;
                    }
                  else
                    messageUI ((char *)"Successful save", GREEN);

                  break;
                case LOAD:
                  printf ("Input file name for load: ");
                  scanf ("%s", filename);
                  if (sc_memoryLoad (filename))
                    {
                      messageUI ((char *)"Failed to load memory", RED);
                      break;
                    }
                  else
                    messageUI ((char *)"Successful load", GREEN);
                  break;
                case RUN:
                  sc_regInit ();

                  raise (SIGALRM);
                  break;
                case STEP:
                  cell = count;
                  uiAdd ();
                  CU ();
                  break;
                case RESET:
                  sc_memoryInit ();
                  sc_accumulatorInit ();
                  sc_icounterInit ();
                  raise (SIGUSR1);
                  break;
                case ENTER:

                  memX = cell % 10;
                  memY = cell / 10;
                  mt_gotoXY ((memX + 1) * 6 - 4, memY + 2);
                  scanf ("%s", bufferCh);
                  int hexValue;
                  if (bufferCh[0] == '-')
                    {
                      if (sscanf (bufferCh + 1, "%x", &hexValue) != 1)
                        {
                          continue;
                        }
                      hexValue = hexValue | (1 << 15);
                    }
                  else
                    {
                      if (sscanf (bufferCh, "%x", &hexValue) != 1)
                        {
                          continue;
                        }
                    }

                  if (sc_memorySet (cell, hexValue))
                    return -1;
                  printTerm (cell, 1, membuffer);
                  break;
                case F5:
                  printf ("Set accumulator: ");
                  scanf ("%d", &accumulator);
                  if (accumulator > 32767 || accumulator < -32767)
                    {
                      accumulator = 0;
                      sc_regSet (OVERFLOW_OPERATION, 1);
                    }
                  break;
                case F6:
                  printf ("Set instruction counter: ");
                  scanf ("%d", &count);
                  if (count < 0 || count > 128)
                    {
                      sc_regSet (OVERFLOW_OPERATION, 1);
                      count = cell;
                    }
                  cell = count;
                  break;
                }
            }
        }
      else
        {
          if (key == RESET)
            {
              raise (SIGUSR1);
            }
        }
    }
  while (key != EXIT);
  printf ("(^-^)  return 0;\n");
  free (cache);
  return 0;
}