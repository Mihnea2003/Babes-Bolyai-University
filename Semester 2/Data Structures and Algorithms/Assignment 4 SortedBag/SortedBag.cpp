#include "SortedBag.h"
#include "SortedBagIterator.h"
//Overall:Theta of capacity
SortedBag::SortedBag(Relation r):relation(r) {
    capacity = 100000;
    table = new Node[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i].next = -1;
    }
    firstFree = 0;
    count = 0;
}
//Complexity in any case is Theta of capacity
void SortedBag::setFirstFree() {
    for (int i = 0; i < capacity; i++) {
        if (table[i].elem.second == 0 || table[i].elem.first == -1) {
            // Check if the current position maintains the sorted order
            if (i == 0 || (i > 0 && relation(table[i-1].elem.first, table[i].elem.first))) {
                firstFree = i;
                break;
            }
        }
    }
}
//best case complexity is O(1)
//the worst case complexity is O(capacity + n),n the numbers of elements
//the overall case complexity is O(capacity + n)
void SortedBag::add(TComp e) {
    int position = hashFunction(e);
    int current = table[position].next;
    int prev = position;

    // Find the correct position to insert the element while maintaining the sorted order
    while (current != -1 && relation(table[current].elem.first, e)) {
        prev = current;
        current = table[current].next;
    }

    // Check if the element already exists in the sorted bag
    if (current != -1 && table[current].elem.first == e) {
        table[current].elem.second++; // Increment the frequency
        count++;
    } else {
        if (firstFree == capacity - 1) {
            // Perform resizing if the table is full
            int newCapacity = capacity * 2;
            Node* newTable = new Node[newCapacity];
            for (int i = 0; i < capacity; i++) {
                newTable[i] = table[i];
            }
            for (int i = capacity; i < newCapacity; i++) {
                newTable[i].next = -1;
            }
            newTable[newCapacity - 1].next = -1;
            delete[] table;
            table = newTable;
            firstFree = capacity;
            capacity = newCapacity;
        }

        if (!table[prev].elem.first || table[prev].elem.first == -1) {
            // Insert the element into an empty position
            table[prev].elem = std::make_pair(e, 1); // Set initial frequency to 1
            if (prev == firstFree) {
                setFirstFree();
            }
            count++;
        } else {
            // Insert the element into a new position
            current = firstFree;
            setFirstFree();
            table[prev].next = current;
            table[current].elem = std::make_pair(e, 1); // Set initial frequency to 1
            table[current].next = -1;
            count++;
        }
    }
}
//the best case complexity is O(1)
//the worst case complexity is O(n)
//the overall case complexity is O(n)
bool SortedBag::remove(TComp e) {
    int position = hashFunction(e);
    int current = table[position].next;
    int prev = position;
    while (current != -1 && table[current].elem.first != e) {
        prev = current;
        current = table[current].next;
    }
    if (current == -1) {
        if (table[prev].elem.first && table[prev].elem.first == e) {
            if (table[prev].elem.second > 1) {
                table[prev].elem.second -= 1;
                count--;
                return true;
            } else {
                table[prev].elem.first = -1;
                table[prev].elem.second = 0;
                table[prev].next = -1;
                count--;
                return true;
            }
        } else{
            return false;
        }
    } else {
        if (table[prev].elem.first == e) {
            if (table[prev].elem.second > 1) {
                table[prev].elem.second -= 1;
                count--;
                return true;
            } else {
                int nextNodePosition = table[prev].next;
                table[prev].elem.first = table[nextNodePosition].elem.first;
                table[prev].elem.second = table[nextNodePosition].elem.second;
                table[prev].next = table[nextNodePosition].next;
                table[nextNodePosition].elem.first = -1;
                table[nextNodePosition].elem.second = 0;
                table[nextNodePosition].next = -1;
                count--;
                return true;
            }
        } else{
            return false;
        }
    }
}


//best case complexity is O(1)
//the worst case complexity is O(n)
//the overall case complexity is O(n)
bool SortedBag::search(TComp elem) const {
    int position = this->hashFunction(elem);
    if (table[position].elem.first && table[position].elem.first == elem) {
        return true;
    }
    int current = table[position].next;
    while (current != -1 && table[current].elem.first != elem) {
        current = table[current].next;
    }

    return (current != -1);
}

//the best case complexity is O(1)
//the worst case complexity is O(n)
//the overall case complexity is O(n)
int SortedBag::nrOccurrences(TComp elem) const {
    int position = hashFunction(elem);
    int current = table[position].next;
    int n = 0;

    if (table[position].elem.first == elem) {
        n += table[position].elem.second;
    }

    while (current != -1) {
        if (table[current].elem.first == elem) {
            n += table[current].elem.second;
        }
        current = table[current].next;
    }

    return n;
}


//the complexity of the size() function is Theta(1).
int SortedBag::size() const {
    return count;
}

//Theta(1)
bool SortedBag::isEmpty() const {
    return (count == 0);
}

//Theta(1)
SortedBagIterator SortedBag::iterator() {
    return SortedBagIterator(*this);
}

//Theta(1)
SortedBag::~SortedBag() {
    delete[] table;
}
