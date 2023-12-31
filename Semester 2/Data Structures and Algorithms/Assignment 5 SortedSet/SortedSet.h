#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
typedef bool (*Condition)(TComp); // filter function
#define NULL_TELEM -11111
class SortedSetIterator;
const int INITIAL_CAPACITY = 127; // 7 levels
const int NONEXISTENT_POSITION = -1;

struct Node {
    TComp info;
    int left;
    int right;
    int parent;
};
const Node NULL_NODE = { NULL_TELEM, NONEXISTENT_POSITION, NONEXISTENT_POSITION, NONEXISTENT_POSITION };

class SortedSet {
	friend class SortedSetIterator;
private:
    Node* elements;
    int elementCount;
    int arrayCapacity;
    Relation relation;
    int rootPosition;
    int* nextEmpty;
    int firstEmpty; // index of the first empty position (used in nextEmpty)
    int findPositionOf(TComp elem) const;
    /*
        Finds the position of a given element in the bstree
        Complexity:
            - BC: theta(1), when the element is the root of the bstree
            - AC: theta(n) (n = current array capacity)
            - WC: theta(n), when the element is a leaf of the bstree
        Input:
            - The element we search for
        Output:
            - Returns the position of the element, if it is found
            - Returns NONEXISTENT_POSITION, otherwise
    */

    void addNewNode(TComp elem, int position, bool isLeftChild, int parentPosition);
    /*
        Adds a new node to the tree
        Complexity:
            - BC/AC/WC: theta(1)
        Input:
            - The value (elem) of the new node
            - Its position and its parent's position
            - Whether it's a leftChild or not (used when maintaining the parent-child links)
        Output:
            - The node is added to the tree
            - The parent-child links are updated
            - If necessary, the root position is updated
    */

    void resizeArrays();
    /*
        Resizes the current arrays
        Complexity:
            - BC/AC/WC: theta(n) (n = current array capacity)
        Input:
            - The old arrays and their capacities are already known
        Output:
            - The content of the arrays is copied to new and larger arrays
    */

    bool isLeftChild(int position) const;
    bool isRightChild(int position) const;
    /*
        (I've put both specifications here because they are very similar)
        Checks if the current node is a left child or a right child
        Complexity:
            - BC/AC/WC: theta(1)
        Input:
            - The position of the node
        Output:
            - Returns true/ false, according to whether the node is a left/ right child
    */

    int getPositionOfMaximum(int rootPosition) const;
    int getPositionOfMinimum(int rootPosition) const;
    /*
        (I've put both specifications here because they are very similar)
        Finds the position of the maximum/ minimum element in a subtree given by its root
        Complexity:
            - BC: theta(1), when the maximum/minimum element is at the root
            - AC: theta(n) (n = current array capacity)
            - WC: theta(n) (n = current array capacity) when all the elements are in a 'chain'
        Input:
            - The position of the root of the subtree we search through
        Output:
            - Returns the position of the maximum/ minimum element
    */

    void addToNextEmpty(int position);
    /*
        Adds a new position to the beginning of nextEmpty
        Complexity:
            - BC/AC/WC: theta(1)
        Input:
            - The position we want to add
        Output:
            - The position is added to nextEmpty, firstEmpty is updated accordingly
    */

    void removeWithNoSuccessors(int position);
    /*
        Removes a node with no successors
        Complexity:
            - BC/AC/WC: theta(1)
        Input:
            - The position of the node we want to remove
        Output:
            - The node is removed from the tree
            - The parent-child links are updated
            - If necessary, the root position is updated
    */

    void removeWithOneSuccessor(int position, bool hasLeftChild);
    /*
        Removes a node with one successor
        Complexity:
            - BC/AC/WC: theta(1)
        Input:
            - The position of the node we want to remove
            - Whether is has a left child or not (=> right child)
        Output:
            - The node is removed from the tree
            - The parent-child links are updated
            - If necessary, the root position is updated
    */

    void removeWithTwoSuccessors(int position);
    /*
        Removes a node with two successors
        Complexity:
            - BC/AC/WC: theta(n) (n = current array capacity)
        Input:
            - The position of the node we want to remove
        Output:
            - The node is removed from the tree
            - The parent-child links are updated
            - If necessary, the root position is updated
    */

    void resetEmpty();
    /*
        Resets the nextEmpty list (happens when the set is empty)
        Complexity:
            - BC/AC/WC: theta(n) (n = current array capacity)
        Input:
            - None
        Output:
            - nextEmpty and firstEmpty are reset
    */

    void independentListsCopy(const SortedSet& originalSet);
    /*
        Copies the content of the lists from another set to the current one
        Complexity:
            - BC/AC/WC: theta(n) (n = current array capacity)
        Input:
            - The SortedSet we copy from
        Output:
            - The content of elements and nextEmpty is copied from originalSet
            - The lists are resized if required
    */

public:
	//constructor
	SortedSet(Relation r);
   /* Complexity:
            - BC/AC/WC: theta(n) (n = initial array capacity)
    Input:
            - The relation between its elements
    - The initial array capacity is already set
            Output:
            - The object is built
    */
	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);
    /*Complexity:
				- BC/AC/WC: theta(n) (n = current array capacity)
			Input:
				- The element we want to add
			Output:
				- Returns true if the element was added (it didn't exist prior to this)
				- Returns false, otherwise
     */

	
	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);
    /*Complexity:
				- BC: theta(1), when the node has 0 or 1 children
				- AC: theta(n) (n = current array capacity)
				- WC: theta(n), when the node has 2 children
			Input:
				- The element we want to remove
			Output:
				- Returns true if the element was removed (it existed prior to this)
				- Returns false, otherwise
     */

	//checks if an element is in the sorted set
	bool search(TElem elem) const;
    /*Complexity:
				- BC: theta(1), when the element is the root of the bstree
				- AC: theta(n) (n = current array capacity)
				- WC: theta(n), when the element is a leaf of the bstree
			Input:
				- The element we search for
			Output:
				- Returns true if the element is found
				- Returns false otherwise
     */


	//returns the number of elements from the sorted set
	int size() const;
    /*Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
     */

	//checks if the sorted set is empty
	bool isEmpty() const;
    /*Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
			Output:
				- Returns true if the set is empty
				- Returns false, otherwise
     */

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;
    /*Complexity:
				- BC/AC/WC: theta(n), (n = current array capacity)
			Input:
				- None
     */
    SortedSet(const SortedSet& originalSet);
    /*
        Overloaded copy constructor
        Complexity:
            - BC/AC/WC: theta(n) (n = current array capacity)
        Input:
            - The set we copy from
        Output:
            - The content of the originalSet is transfered to the current one
    */
    SortedSet& operator = (const SortedSet& originalSet);
    /*
        Overloaded assignment operator
        Complexity:
            - BC/AC/WC: theta(n) (n = current array capacity)
        Input:
            - The set we copy from
        Output:
            - The content of the originalSet is transfered to the current one
    */

	// destructor
	~SortedSet();
    TComp getElement(int position);
    void filter(Condition cond);
};
