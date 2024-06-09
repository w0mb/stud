// Database.h
#ifndef DATABASE_H
#define DATABASE_H

#include "List.h"
#include "SortAlgorithm.h"

class Database
{
private:
    List *base;
    SortAlgorithm *sortAlgorithm;

public:
    Database();
    Database(List *initialBase, SortAlgorithm *algorithm);

    void copyBase(List *source, List *&destination);
    void printList(List *base);
    void sortBase();
    void addNode(Country *country);
    void readBaseFromFile(const char *fileName);

    int binarySearch(const char *FIO_prefix);

    List *getBase() const;
    void clearBase();
    void setSortAlgorithm(SortAlgorithm *algorithm);
    List *getFirstElement() const;
};

#endif // DATABASE_H
