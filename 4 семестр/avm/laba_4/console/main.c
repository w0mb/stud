#include <fcntl.h>
#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <unistd.h>

void lab2 (void);
void lab3 (void);
void lab4 (void);

int bc[][2] = {
  { 0xE7E7FFFF, 0xFFFFE7E7 }, // 0  |
  { 0x1CDC7C3C, 0xFFFF1C1C }, // 1  |
  { 0xFF07FFFF, 0xFFFFE0FF }, // 2  |
  { 0xFF07FFFF, 0xFFFF07FF }, // 3  |
  { 0xFFE7E7E7, 0x070707FF }, // 4  |
  { 0xFFE0FFFF, 0xFFFF07FF }, // 5  |
  { 0xFFE0FFFF, 0xFFFFE7FF }, // 6  |
  { 0x1C0EFFFE, 0x3838FE38 }, // 7  |
  { 0x7EE7FF7E, 0x7EFFE77E }, // 8  |
  { 0xFFE7FFFF, 0xFFFF07FF }, // 9  |
  { 0xFFE7FF7E, 0xE7E7E7FF }, // A  |
  { 0xFEE7FFFE, 0xFEFFE7FE }, // B  |
  { 0xE0E7FF7E, 0x7EFFE7E0 }, // C  |
  { 0xE7E7FFF8, 0xF8FFE7E7 }, // D  |
  { 0xFFE0FFFF, 0xFFFFE0FF }, // E  |
  { 0xFFE0FFFF, 0xE0E0E0FF }, // F  |
  { 0x7E180000, 0x00000018 }, // +  |
  { 0x7E000000, 0x00000000 }, // -  |
  { 0x1CDC7C3C, 0xFFFF1C1C }  // 1  |
};

int
drawingBoxes ()
{
  if (bc_box (1, 1, 61, 15)) // memory
    return -1;
  if (bc_box (62, 1, 27, 3)) // accumulator
    return -1;
  if (bc_box (62, 4, 27, 3)) // counter
    return -1;
  if (bc_box (89, 4, 27, 3)) // operation
    return -1;
  if (bc_box (89, 1, 27, 3)) // flags
    return -1;
  if (bc_box (62, 7, 54, 13)) // bigChars
    return -1;
  if (bc_box (84, 20, 32, 7)) // keys
    return -1;
  if (bc_box (1, 16, 61, 4)) //  bigChar mini
    return -1;
  if (bc_box (1, 20, 69, 7)) //  cash
    return -1;
  if (bc_box (70, 20, 14, 7)) //  In-Out
    return -1;

  return 0;
}

int
drawingTexts ()
{
  mt_gotoXY (25, 1);
  mt_setfgcolor (RED);
  printf (" Оперативная память ");
  mt_gotoXY (66, 1);
  printf (" Аккумулятор ");
  mt_gotoXY (65, 4);
  printf (" Счётчик команд ");
  mt_gotoXY (93, 4);
  printf (" Команда ");
  mt_gotoXY (91, 1);
  printf (" Регистр флагов ");
  mt_gotoXY (70, 7);
  mt_setbgcolor (WHITE);
  printf (" Редактируемая ячейка (увеличено) ");
  mt_gotoXY (20, 16);
  printf (" Редактируемая ячейка (формат) ");
  mt_gotoXY (63, 18);
  mt_setfgcolor (BLUE);
  mt_setbgcolor (DEFAULT);
  printf (" Номер редактируемой ячейки: %d ", 0);
  mt_setfgcolor (DEFAULT);

  mt_setbgcolor (WHITE);
  mt_setfgcolor (GREEN);
  mt_gotoXY (23, 20);
  printf (" Кеш процессора ");

  mt_gotoXY (73, 20);
  printf (" IN-OUT ");

  mt_gotoXY (95, 20);

  printf (" Клавиши ");
  mt_setfgcolor (WHITE);
  mt_setbgcolor (DEFAULT);

  mt_gotoXY (85, 21);
  printf ("l - load");
  mt_gotoXY (95, 21);
  printf ("s - save");
  mt_gotoXY (105, 21);
  printf ("i - reset");
  mt_gotoXY (85, 22);
  printf ("r  - run");
  mt_gotoXY (95, 22);
  printf ("t  - step");
  mt_gotoXY (85, 23);
  printf ("ESC - выход");
  mt_gotoXY (85, 24);
  printf ("F5 - accumulator");
  mt_gotoXY (85, 25);
  printf ("F6 - instruction counter");

  mt_gotoXY (1, 28);
  printf ("%s", "Введите имя файла для загрузки: ");
  mt_setfgcolor (DEFAULT);
  return 0;
}

int
drawingMemory ()
{
  for (int i = 0; i < 128; i++)
    {
      int row = (i) / MEMORY_BLOCK_WIDTH + MEMORY_BLOCK_START_ROW + 1;
      int col = (i) % MEMORY_BLOCK_WIDTH * CELL_WIDTH + MEMORY_BLOCK_START_COL;
      mt_gotoXY (col, row);
      if (i == count)
        {
          mt_setbgcolor (WHITE);

          int cell_value = memory[i];
          printf ("+%04X ", cell_value);
          mt_setdefaultcolors ();
        }

      int cell_value = memory[i];
      printf ("+%04X", cell_value);
    }

  return 0;
}

int
drawingFlags ()
{
  char flags[] = { 'O', 'Z', 'M', 'P', 'C' };
  for (int i = 1; i < 5; ++i)
    {
      int value;
      if (sc_regGet (i, &value))
        return -1;
      if (value)
        {
          mt_gotoXY (69 + (i * 2), 11);
          printf ("%c", flags[i]);
        }
    }

  return 0;
}

int
drawingBigChars ()
{
  int tmp = memory[count];
  if (!((tmp >> 14) & 1))
    bc_printbigchar (bc[16], 63, 9, WHITE, DEFAULT);

  for (int i = 0; i < 4; ++i)
    {
      int ch = (tmp & (0b1111 << (4 * (3 - i)))) >> (4 * (3 - i));

      bc_printbigchar (bc[ch], 62 + 8 * (i + 1) + 2 * (i + 1), 9, WHITE,
                       DEFAULT);
    }

  return 0;
}

int
uiAdd ()
{
  mt_clrscr ();
  count = 0;
  drawingBoxes ();
  drawingTexts ();
  mt_gotoXY (1, 24);

  return 0;
}

int
uiUpdate ()
{
  drawingMemory ();
  drawingFlags ();
  drawingBigChars ();
  mt_gotoXY (1, 24);
  return 0;
}

int
main (void)
{
  sc_memoryInit ();
  sc_regInit ();
  sc_icounterInit ();
  sc_accumulatorInit ();
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
  uiAdd ();
  sc_memorySet (0, 0x3434);
  sc_memorySet (11, 0x1234);
  sc_memorySet (22, 0xABCD);
  sc_memorySet (127, 0x1F7F);
  sc_regSet (IGNORING_TACT_PULSES, 3);
  sc_accumulatorSet (42);
  sc_icounterSet (0);
  printAccumulator ();
  printCounters ();
  printFlags ();
  printCommand ();
  printDecodedCommand (0x3434);
  printTerm (0, 1);
  printTerm (1, 1);
  printTerm (2, 1);
  printTerm (3, 1);
  printTerm (1, 0);

  uiUpdate ();
  int fd = open ("test.bin", O_WRONLY);
  bc_bigcharwrite (fd, *bc, 18);
  close (fd);
  mt_gotoXY (1, 30);

  return 0;
}

void
lab4 (void)
{
}

void
lab3 (void)
{
  // int value;

  // sc_memoryInit ();
  // sc_regInit ();
  // sc_icounterInit ();
  // sc_accumulatorInit ();
  // sc_memorySet (0, 5);
  // sc_memorySet (1, 10);
  // sc_memorySet (2, 15);
  // sc_memorySet (3, 20);
  // sc_memorySet (4, 0xa);
  // sc_memorySet (5, 0xb);
  // sc_memorySet (6, 123);
  // // sc_memorySet (3, -5);
  // sc_regSet (WRONG_FLAG, 1);

  // sc_accumulatorSet (42);
  // sc_accumulatorGet (&value);
  // sc_icounterSet (5);
  // sc_icounterGet (&value);
  // int f = 0, f_c = 0, f_o = 0;
  // sc_commandEncode (0xb, 0x1, &f);
  // sc_commandDecode (f, &f_c, &f_o);
  // for (int i = 0; i < 128; i++)
  //   {
  //     sc_memoryGet (i, &value);
  //     printCell (i, WHITE, BLUE);
  //   }

  // printAccumulator ();
  // printCounters ();
  // printFlags ();
  // printDecodedCommand (0xa);
  // printTerm (0, 1);
  // printTerm (1, 1);
  // printTerm (2, 1);
  // printTerm (3, 1);
  // // for (int i = 0; i < 4; i++)
  // //   {
  // printTerm (1, 0);
  // //}

  // // printTerm(7, 0);
  // printCommand ();
  // mt_setdefaultcolors ();
  // mt_gotoXY (17, 2);
}

void
lab2 (void)
{
  // int value;
  // puts ("\n");
  // sc_memoryInit ();
  // sc_regInit ();
  // sc_icounterInit ();
  // sc_accumulatorInit ();
  // sc_memorySet (1, 5);
  // sc_memorySet (-2, 4);
  // sc_memorySet (3, 3);
  // for (int i = 0; i < 3; i++)
  //   {
  //     sc_memoryGet (i + 1, &value);
  //     printf ("RAM[%d] = %d\n", i + 1, value);
  //   }
  // printf ("Save RAM\n");
  // sc_memorySave ("./mySimpleComputer/mem.bin");
  // printf ("Load RAM\n");
  // sc_memoryLoad ("./mySimpleComputer/mem.bin");
  // for (int i = 0; i < 3; i++)
  //   {
  //     sc_memoryGet (i + 1, &value);
  //     printf ("RAM[%d] = %d\n", i + 1, value);
  //   }
  // puts ("\n");
  // sc_memorySet (10, 54);
  // sc_memoryGet (10, &value);
  // printf ("RAM[%d] = %d\n", 10, value);

  // sc_regInit ();

  // sc_regSet (WRONG_FLAG, 1);

  // sc_regGet (OUT_OF_MEMORY_BOUNDS, &value);
  // printf ("\nRegister: %d, Value: %d ", OUT_OF_MEMORY_BOUNDS, value);

  // sc_regGet (WRONG_FLAG, &value);
  // printf ("\nRegister: %d, Value: %d ", WRONG_FLAG, value);

  // sc_regGet (OPERATION_OVERFLOW, &value);
  // printf ("\nRegister: %d, Value: %d ", OPERATION_OVERFLOW, value);

  // sc_regGet (INCORRECT_COMMAND_RECEIVED, &value);
  // printf ("\nRegister: %d, Value: %d ", INCORRECT_COMMAND_RECEIVED, value);

  // sc_regGet (DIVISION_ERR_BY_ZERO, &value);
  // printf ("\nRegister: %d, Value: %d ", DIVISION_ERR_BY_ZERO, value);
  // puts ("\n");
  // sc_accumulatorInit ();
  // sc_accumulatorSet (42);
  // sc_accumulatorGet (&value);
  // sc_icounterInit ();
  // sc_icounterSet (5);
  // sc_icounterGet (&value);
  // int f = 0, f_c = 0, f_o = 0;
  // sc_commandEncode (0xb, 0x1, &f);
  // printf ("Encoded command: %x  \n", f);
  // sc_commandDecode (f, &f_c, &f_o);
  // printf ("Command: %x   operand: %x  \n", f_c, f_o);
  // puts ("\n");
  // printCell (1);
  // printAccumulator ();
  // printCounters ();
  // printFlags ();
  // puts ("\n");
  // printDecodedCommand (0xa);
}