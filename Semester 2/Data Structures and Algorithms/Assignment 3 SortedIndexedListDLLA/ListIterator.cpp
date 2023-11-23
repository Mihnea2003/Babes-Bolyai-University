#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	this->index = list.head;
}
//Complexitate:
//best case: O(1) - element is the last in list
//average case: O(n/2) - element is present but is not first or last
//worst case: O(n) - element is the first so it traverse the entire list
int SortedIndexedList::last_index_of(TComp e) const {
    int current = this->tail;
    while (current != -1) {
        if (this->elements[current].info == e) {
            return current;
        }
        current = this->elements[current].prev;
    }
    return -1;
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: Θ(1)
void ListIterator::first(){
	this->index = list.head;
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: Θ(1)
void ListIterator::next(){
	if(valid()){
        this->index = list.elements[this->index].next;
    }else{
        throw exception();
    }
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: Θ(1)
bool ListIterator::valid() const{
	if(index != -1)
        return true;
	return false;
}

//Complexitate:
//best case: Θ(1)
//worst case: Θ(1)
//average case: Θ(1)
TComp ListIterator::getCurrent() const{
	if(valid()){
        return list.elements[this->index].info;
    }else{
        throw exception();
    }
}


