//
// Created by bro_b on 4/1/2023.
//
#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    this->capacity = 1;
    this->elements = new TComp[this->capacity];
    this->r = r;
    this->Bagsize = 0;
}

void SortedBag::add(TComp e) {
    // If the array is full, resize it
    if (Bagsize == capacity) {
        TComp* newElements = new TComp[capacity * 2];
        for (int i = 0; i < Bagsize; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity *= 2;
    }

    // Find the correct position for the new element
    int pos = 0;
    while (pos < Bagsize&& r(elements[pos], e)) {
        pos++;
    }

    // Shift elements to the right to make room for the new element
    for (int i = Bagsize; i > pos; i--) {
        elements[i] = elements[i - 1];
    }

    // Insert the new element at the correct position
    elements[pos] = e;
    Bagsize++;
}


bool SortedBag::remove(TComp e) {
    int index = -1;
    for (int i = 0; i < capacity; i++) {
        if (elements[i] == e) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return false; // element not found
    }
    else {
        for (int i = index; i < Bagsize - 1; i++) {
            elements[i] = elements[i + 1];
        }
        elements[Bagsize - 1] = NULL_TCOMP;
        Bagsize--;
        return true; // element found and removed
    }
    return false;
}


bool SortedBag::search(TComp elem) const {
    for (int i = 0; i < Bagsize; i++) {
        if (elements[i] == elem) {
            return true;
        }
    }
    return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
    int count = 0;
    for (int i = 0; i < Bagsize; i++) {
        if (elements[i] == elem) {
            count++;
        }
    }
    return count;
}



int SortedBag::size() const {
    return Bagsize;
}


bool SortedBag::isEmpty() const {
    return Bagsize == 0;
}


SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
    delete[] elements;
}