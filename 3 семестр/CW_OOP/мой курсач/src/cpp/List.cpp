// List.cpp
#include "../headers/List.h"

List::List() : data(nullptr), next(nullptr), prev(nullptr) {}

List::List(Country *country) : data(country), next(nullptr), prev(nullptr) {}

Country *List::getData() const
{
    return data;
}

List *List::getNext() const
{
    return next;
}

List *List::getPrev() const
{
    return prev;
}

void List::setNext(List *nextNode)
{
    next = nextNode;
}

void List::setPrev(List *prevNode)
{
    prev = prevNode;
}

void List::setData(Country *newData)
{
    data = newData;
}

int List::compare(List *other) const
{
    return this->getData()->compare(other->getData());
}
