// Menu.cpp

#include "../headers/Menu.h"
#include "../headers/const.h"


void Menu::searchByFIO(Database &database)
{
    cout << endl;
    cout << "Enter Fio" << endl;
    char substring[3];
    SetConsoleCP(866);
    cin >> substring;
    SetConsoleCP(1251);

    if (strcmp(substring, "0") != 0)
    {
        List *current = database.getFirstElement();
        int count = 0;

        while (current != nullptr)
        {
            if (strncmp(current->getData()->getFIO(), substring, 3) == 0)
            {
                cout << count << " " << current->getData()->getFIO() << "\t" << current->getData()->getStreet()
                     << "\t" << current->getData()->getNumberHome() << "\t" << current->getData()->getNumberAppart()
                     << "\t" << current->getData()->getDate() << endl;
                count++;
            }
            current = current->getNext();
        }

        if (count == 0)
        {
            cout << "No records found for the specified FIO substring." << endl;
        }
        else
        {
            cout << endl << "Founded " << count << " positions." << endl;
        }
    }
}

char Menu::getUserChoice()
{
    char choice;
    cin >> choice;
    return choice;
}

void Menu::showSortedRecords(Database &database)
{
    database.sortBase();
    database.printList(database.getBase());
}

void Menu::showUnsortedRecords(Database &database)
{
    database.printList(database.getBase());
}

void Menu::showMenu(Database &database)
{
    char choice;
    
    do
    {
        cout << "===== Menu =====" << endl;
        cout << "1. Search by FIO" << endl;
        cout << "2. Show sorted records" << endl;
        cout << "3. Show unsorted records" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        
        choice = getUserChoice();

        switch (choice)
        {
        case '1':
            searchByFIO(database);
            break;
        case '2':
            showSortedRecords(database);
            break;
        case '3':
            showUnsortedRecords(database);
            break;
        case '0':
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (choice != '0');
}