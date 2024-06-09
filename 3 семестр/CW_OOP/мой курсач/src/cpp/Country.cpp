// Country.cpp
#include "../headers/Country.h"
#include "../headers/const.h"

Country::Country() {}

Country::Country(const char *fio, const char *st, short int home, short int appart, const char *date)
    : number_home(home), number_appart(appart)
{
    strncpy(FIO, fio, sizeof(FIO) - 1);
    strncpy(street, st, sizeof(street) - 1);
    strncpy(Date, date, sizeof(Date) - 1);
}

const char *Country::getFIO() const
{
    return FIO;
}

const char *Country::getStreet() const
{
    return street;
}

short int Country::getNumberHome() const
{
    return number_home;
}

short int Country::getNumberAppart() const
{
    return number_appart;
}

const char *Country::getDate() const
{
    return Date;
}

int Country::compare(const Country *other) const
{
    if (strcmp(FIO, other->getFIO()) == 0)
    {
        return strcmp(street, other->getStreet());
    }
    return strcmp(FIO, other->getFIO());
}
