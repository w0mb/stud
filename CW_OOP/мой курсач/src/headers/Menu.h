// Menu.h

#ifndef MENU_H
#define MENU_H

#include "Database.h"

class Menu
{
public:
    static void showMainMenu();
    static char getUserChoice();
    static void showSortedRecords(Database &database);
    static void showUnsortedRecords(Database &database);
    static void searchByFIO(Database &database);
    static void showMenu(Database &database);
};

#endif  // MENU_H
