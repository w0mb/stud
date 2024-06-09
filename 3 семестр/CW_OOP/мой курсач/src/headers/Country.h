// Country.h
#ifndef COUNTRY_H
#define COUNTRY_H

class Country
{
private:
    char FIO[32];
    char street[18];
    short int number_home;
    short int number_appart;
    char Date[10];

public:
    Country();
    Country(const char *fio, const char *st, short int home, short int appart, const char *date);

    const char *getFIO() const;
    const char *getStreet() const;
    short int getNumberHome() const;
    short int getNumberAppart() const;
    const char *getDate() const;

    int compare(const Country *other) const;
};

#endif // COUNTRY_H
