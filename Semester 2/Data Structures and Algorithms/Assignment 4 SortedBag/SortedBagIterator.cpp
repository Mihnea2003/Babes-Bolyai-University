#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;
//Theta(capacity)
SortedBagIterator::SortedBagIterator(SortedBag& b) : bag(b) {
    currentPair = 0;
    currentPosition = -1;
    while (currentPair < bag.capacity && (bag.table[currentPair].elem.first == -1 || bag.table[currentPair].elem.second == 0)) {
        currentPair++;
    }
    if (currentPair < bag.capacity) {
        currentPosition = currentPair;
    }
}

//theta(1)
TComp SortedBagIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return bag.table[currentPosition].elem.first;
}

//Theta(1)
bool SortedBagIterator::valid() {
    return currentPosition >= 0 && currentPosition < bag.capacity && bag.count > 0;
}
//Theta(1)
void SortedBagIterator::next() {
    if (!valid()) {
        throw std::exception();
    }
    currentPosition = bag.table[currentPosition].next;
}
//Theta(capacity)
void SortedBagIterator::first() {
    currentPair = 0;
    currentPosition = -1;
    while (currentPair < bag.capacity && (bag.table[currentPair].elem.first == -1 || bag.table[currentPair].elem.first == 0)) {
        currentPair++;
    }
    if (currentPair < bag.capacity) {
        currentPosition = currentPair;
    }
}
//best case,when we want to remove the last element so it raises an exception,Theta(1)
//worst case,when we want to remove the first element,O(n)n being the elements in the bag
//overall:O(n)
TElem SortedBagIterator::remove() {
    if (!valid()) {
        throw std::exception();
    }
    TComp removedElement = bag.table[currentPosition].elem.first;

    if (bag.table[currentPosition].elem.second > 1) {
        bag.table[currentPosition].elem.second--;
        bag.count--;
    } else {
        int nextNodePosition = bag.table[currentPosition].next;
        bag.table[currentPosition].elem.first = bag.table[nextNodePosition].elem.first;
        bag.table[currentPosition].elem.second = bag.table[nextNodePosition].elem.second;
        bag.table[currentPosition].next = bag.table[nextNodePosition].next;
        bag.table[nextNodePosition].elem.first = -1;
        bag.table[nextNodePosition].elem.second = 0;
        bag.table[nextNodePosition].next = -1;
        bag.count--;
        currentPosition = nextNodePosition;
    }

    return removedElement;
}

