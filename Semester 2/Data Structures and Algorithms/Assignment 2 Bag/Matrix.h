#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
struct Node {
	int line;
	int col;
	TElem value;
	Node* next;
	Node* prev;
};
class Matrix {

private:
	int lines;
	int cols;

	Node* list; /// a list of elements


	Node* insert_node(Node** node, int i, int j, TElem value);
	Node* search_node(Node* node, int i, int j) const;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	void delete_node(Node* node);

	void delete_(int i, int j);

    Node* getHead(int line) const {
        Node* node = list;
        while (node != nullptr && node->line < line) {
            node = node->next;
        }
        return node;
    }
};
