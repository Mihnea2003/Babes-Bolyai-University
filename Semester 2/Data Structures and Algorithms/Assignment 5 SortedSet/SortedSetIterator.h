#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
    int position; // position in the set's array
    SortedSetIterator(const SortedSet& m);
    /*
        Constructor
        Complexity:
            - BC/AC/WC: theta(n) (n = current array capacity)
        Input:
            - The set we iterate through
        Output:
            - The object is built
            - The iterator is set on the first position
    */

public:
    /*Complexity:
				- BC: theta(1), if the minimum element is at the root
				- AC: theta(n)
				- WC: theta(n) (n = current array capacity)
     */
	void first();
    /*Complexity:
				- BC: theta(1), if the node has a right child or is a left child
				- AC: theta(n)
				- WC: theta(n) (n = current array capacity), otherwise
     */
	void next();
    /*Complexity:
				- BC/AC/WC: theta(1)
     */
	TElem getCurrent();
    /*Complexity:
				- BC/AC/WC: theta(1)
     */
	bool valid() const;
};

