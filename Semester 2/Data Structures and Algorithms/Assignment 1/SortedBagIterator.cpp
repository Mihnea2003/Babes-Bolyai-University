//
// Created by bro_b on 4/1/2023.
//
#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    current = 0;
}

TComp SortedBagIterator::getCurrent() {
    if (!valid()) {
        throw std::exception("Invalid iterator position.");
    }
    return bag.elements[current];
}

bool SortedBagIterator::valid() {
    return current < bag.Bagsize;
}

void SortedBagIterator::next() {
    if (!valid()) {
        throw std::exception("Invalid iterator position.");
    }
    current++;
}

void SortedBagIterator::first() {
    current = 0;
}
