//
// Created by bro_b on 4/1/2023.
//

#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
    friend class SortedBag;

private:
    const SortedBag& bag;
    SortedBagIterator(const SortedBag& b);

    int current;  // current position in the array

public:
    TComp getCurrent();
    bool valid();
    void next();
    void first();
};

