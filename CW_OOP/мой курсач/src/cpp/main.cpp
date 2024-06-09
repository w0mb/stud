#include "../headers/Database.h"
#include "../headers/Menu.h"
#include "../headers/SortAlgorithm.h"
#include "../headers/QuickSort.h"
#include "../headers/const.h"

int main()
{
    Database myDatabase;
    myDatabase.readBaseFromFile("testBase4.dat");

    SortAlgorithm *quickSort = new QuickSort();
    myDatabase.setSortAlgorithm(quickSort);

    Menu myMenu;

    while (true)
    {
        myMenu.showMenu(myDatabase);
        char choice = myMenu.getUserChoice();

        switch (choice)
        {
        case '1':
            myMenu.showSortedRecords(myDatabase);
            break;

        case '2':
            myMenu.showUnsortedRecords(myDatabase);
            break;

        case '3':
            myMenu.searchByFIO(myDatabase);
            break;

        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
