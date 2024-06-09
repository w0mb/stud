// Database.cpp
#include "../headers/Database.h"
#include "../headers/const.h"

// Implementation of Database methods

Database::Database() : base(nullptr), sortAlgorithm(nullptr) {}

Database::Database(List *initialBase, SortAlgorithm *algorithm)
    : base(initialBase), sortAlgorithm(algorithm) {}

int Database::binarySearch(const char *FIO_prefix)
{
    int l = 0, r = N, m = 0;
    while (l < r)
    {
        m = (l + r) / 2;
        if (strncmp(base->getData()->getFIO(), FIO_prefix, 3) == 0)
        {
            cout << "da";
            return m;
        }
        if (strncmp(base->getData()->getFIO(), FIO_prefix, 3) < 0)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

void Database::setSortAlgorithm(SortAlgorithm *algorithm)
{
    sortAlgorithm = algorithm;
}

void Database::addNode(Country *country)
{
    List *newNode = new List(country);
    if (!base)
    {
        base = newNode;
    }
    else
    {
        List *temp = base;
        while (temp->getNext() != nullptr)
        {
            temp = temp->getNext();
        }
        temp->setNext(newNode);
        newNode->setPrev(temp);
    }
}

void Database::copyBase(List *source, List *&destination)
{
    destination = nullptr;
    List *lastCopiedNode = nullptr;

    while (source != nullptr)
    {
        const char *fio = source->getData()->getFIO();
        const char *street = source->getData()->getStreet();
        short int numberHome = source->getData()->getNumberHome();
        short int numberAppart = source->getData()->getNumberAppart();
        const char *date = source->getData()->getDate();

        Country *newCountry = new Country(fio, street, numberHome, numberAppart, date);
        List *newNode = new List(newCountry);

        if (destination == nullptr)
        {
            destination = newNode;
        }
        else
        {
            lastCopiedNode->setNext(newNode);
            newNode->setPrev(lastCopiedNode);
        }

        lastCopiedNode = newNode;
        source = source->getNext();
    }
}

void Database::readBaseFromFile(const char *fileName)
{
    clearBase();

    std::ifstream file(fileName, std::ios::binary | std::ios::in);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    Country country;
    while (file.read(reinterpret_cast<char *>(&country), sizeof(Country)))
    {
        addNode(new Country(country));
    }

    file.close();
}

void Database::printList(List *base)
{
    int i = 0;
    char n;
    SetConsoleCP(1251);

    system("cls");

    cout << "1 for 20 / 2 for 4000 / 3 for nothing" << endl;
    cin >> n;

    List *current = base;

    if (n == '1')
    {
        cout << "FIO\t\t\tSTREET\t\tHOUSE\tNUM\tAPP\tCHECK IN DATE" << endl;
        while (current != nullptr)
        {
            cout << i + 1 << "\t" << current->getData()->getFIO() << "\t"
                 << current->getData()->getStreet() << "\t" << current->getData()->getNumberHome() << "\t"
                 << current->getData()->getNumberAppart() << "\t" << current->getData()->getDate() << endl;

            i++;
            List *nextNode = current->getNext();
            current = nextNode;

            if (i % 20 == 0)
            {
                cout << "Press 'right arrow' for next 20 records, 'left arrow' for previous 20 records, or 'e' to exit." << endl;

                while (true)
                {
                    if (_kbhit())
                    {
                        char key = _getch();
                        if (key == 77)
                        {
                            system("cls");
                            cout << "FIO\t\t\tSTREET\t\tHOUSE\tNUM\tAPP\tCHECK IN DATE" << endl;
                            break;
                        }
                        else if (key == 75)
                        {
                            system("cls");
                            cout << "FIO\t\t\tSTREET\t\tHOUSE\tNUM\tAPP\tCHECK IN DATE" << endl;
                            for (int j = 0; j < 20 && current->getPrev() != nullptr; j++)
                            {

                                current = current->getPrev();
                            }
                            i -= 40;
                            break;
                        }
                        else if (key == 'e')
                        {
                            system("cls");
                            return;
                        }
                    }
                }
            }
        }
    }
    else if (n == '2')
    {
        cout << "FIO\t\t\tSTREET\t\tHOUSE\tNUM\tAPP\tCHECK IN DATE" << endl;
        while (current != nullptr)
        {
            cout << i + 1 << "\t" << current->getData()->getFIO() << "\t"
                 << current->getData()->getStreet() << "\t" << current->getData()->getNumberHome() << "\t"
                 << current->getData()->getNumberAppart() << "\t" << current->getData()->getDate() << endl;

            i++;
            current = current->getNext();
        }
    }

    cout << "Press any key to exit." << endl;
    _getch();
}

void Database::sortBase()
{
    if (sortAlgorithm)
    {
        List *copy = nullptr;
        copyBase(base, copy);
        sortAlgorithm->sort(copy);
        clearBase();
        base = copy;
    }
}

List *Database::getFirstElement() const
{
    return base;
}

List *Database::getBase() const
{
    return base;
}

void Database::clearBase()
{
    List *temp;
    while (base != nullptr)
    {
        temp = base;
        base = base->getNext();
        delete temp;
    }
}