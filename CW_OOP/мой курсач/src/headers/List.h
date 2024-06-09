// List.h
#ifndef LIST_H
#define LIST_H

#include "Country.h"

class List
{
private:
    Country *data;
    List *next;
    List *prev;

public:
    List();
    List(Country *country);

    Country *getData() const;
    List *getNext() const;
    List *getPrev() const;

    void setNext(List *nextNode);
    void setPrev(List *prevNode);
    void setData(Country *newData);

    int compare(List *other) const;
};

#endif // LIST_H
