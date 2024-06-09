#include "../include/mySimpleComputer.h"
#include "../mySimpleComputer/sc.h"
#include "simpleassembler.h"

int
main (int argc, char **argv)
{
  FILE *file_sa, *file_o;
  if (argc != 3)
    {
      printf ("Usage: sat file.sa file.o\n ");
      return -1;
    }
  if ((file_sa = fopen (argv[1], "rb")) <= 0)
    {
      printf ("Can`t open '%s' file.\n", argv[1]);
      return -1;
    }
  printf ("File is open\n");
  sc_memoryInit ();
  char line[100], ch, comment[10], operandLine[10], commentLine[100] = "\0";
  int value, address, command, operand;
  do
    {
      fgets (line, sizeof (line), file_sa);
      if (feof (file_sa))
        {
          break;
        }
      if (sscanf (line, "%d %s %s ;%s", &address, comment, operandLine,
                  commentLine)
          < 3)
        {
          printf ("Invalid syntax\n");
          return -1;
        }
      command = sa_commandValidate (comment);
      printf ("%d %d %s\n", address, command, operandLine);
      if (command != -1)
        {
          if (command != 1)
            {
              if (sscanf (operandLine, "%d", &operand) != 1
                  || sc_commandEncode (command, operand, &value) == -1
                  || sa_memorySet (address, value) == -1)
                {
                  printf ("Invalid syntax\n");
                  return -1;
                }
            }
          else
            {
              if (sscanf (operandLine, "%c%04X", &ch, &value) != 2)
                {
                  printf ("Invalid syntax\n");
                  return -1;
                }
              if (ch == '-')
                {
                  value = -value;
                }
              if (sa_memorySet (address, value) == -1)
                {
                  printf ("Invalid syntax\n");
                  return -1;
                }
            }
        }
      else
        {
          printf ("Invalid syntax\n");
          return -1;
        }
    }
  while (!feof (file_sa));
  fclose (file_sa);
  if (sc_memorySave (argv[2]) == -1)
    {
      printf ("Can`t create '%s' file.\n", argv[2]);
      return -1;
    }
  return 0;
}