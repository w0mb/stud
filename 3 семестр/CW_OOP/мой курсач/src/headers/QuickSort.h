// QuickSort.h
#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "sortAlgorithm.h"

class QuickSort : public SortAlgorithm
{
public:
    void sort(List *&head) override;
};

#endif // QUICKSORT_H
