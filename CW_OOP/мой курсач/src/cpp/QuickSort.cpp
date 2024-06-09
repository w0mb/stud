// QuickSort.cpp
#include "../headers/QuickSort.h"
#include "../headers/List.h"
#include "../headers/const.h"

// Implementation of QuickSort methods
void swap(List *&a, List *&b)
{
    Country *tempData = a->getData();
    a->setData(b->getData());
    b->setData(tempData);
}

List *partition(List *low, List *high)
{
    Country *pivot = high->getData();
    List *i = low->getPrev();

    for (List *j = low; j != high; j = j->getNext())
    {
        if (strcmp(j->getData()->getFIO(), pivot->getFIO()) < 0)
        {
            i = (i == nullptr) ? low : i->getNext();
            swap(i, j);
        }
    }

    i = (i == nullptr) ? low : i->getNext();
    swap(i, high);

    return i;
}

void quickSortUtil(List *low, List *high)
{
    if (high != nullptr && low != high && low != high->getNext())
    {
        List *pivot = partition(low, high);
        quickSortUtil(low, pivot->getPrev());
        quickSortUtil(pivot->getNext(), high);
    }
}

void QuickSort::sort(List *&head)
{
    if (head != nullptr)
    {
        List *lastNode = head;
        while (lastNode->getNext() != nullptr)
        {
            lastNode = lastNode->getNext();
        }
        quickSortUtil(head, lastNode);
    }
}