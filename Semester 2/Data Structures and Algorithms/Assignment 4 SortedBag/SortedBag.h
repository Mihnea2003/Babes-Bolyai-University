#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

#include <utility>
#include <complex>

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

struct Node{
    std::pair<TElem,int> elem;
    int next;
};

class SortedBag {
	friend class SortedBagIterator;

private:
    Node* table;    // Hash table
    int firstFree;  // Index of the first free node
    int count;      // Number of elements in the hash table
    int capacity;

    int hashFunction(int key) const {
        return std::abs(key % capacity);
    }
    Relation relation; // Relation object for comparison

public:
	//constructor
	SortedBag(Relation r);

    //set the firstFree variable to the index of the first free position
    void setFirstFree();

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() ;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();
};