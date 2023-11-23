#include "Matrix.h"
#include <exception>
using namespace std;

//BC:O(1)-the node is inserted first
//WC:O(n)
Node* Matrix::insert_node(Node** node, int i, int j, TElem value)
{
    Node* new_node = new Node;
    new_node->line = i;
    new_node->col = j;
    new_node->value = value;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    // If the list is empty or the new node is smaller than the head node
    if (*node == nullptr || i < (*node)->line || (i == (*node)->line && j < (*node)->col)) {
        new_node->next = *node;
        if (*node != nullptr) {
            (*node)->prev = new_node;
        }
        *node = new_node;
    }
    else {
        Node* current = *node;
        // Go through the list to find the position of the new node
        while (current->next != nullptr && (i > current->next->line || (i == current->next->line && j > current->next->col))) {
            current = current->next;
        }
        new_node->next = current->next;
        if (current->next != nullptr) {
            current->next->prev = new_node;
        }
        current->next = new_node;
        new_node->prev = current;
    }

    return new_node;
}
//BC:O(1)-(node==nullptr)
//WC:O(n)-last node
//AC:O(log n)
Node* Matrix::search_node(Node* node, int i, int j) const
{
    // Go through the list while the next node still exists and the indices of the node we are searching for 
    // is not smaller than the ones from the current node
    // When the indices of the current node become greater than the ones of the node we are looking for, 
    // it means that our node is not in the list
    // We stop at the last node from the list, but smaller than the one we are looking for 
    while (node != nullptr && (node->line < i || (node->line == i && node->col < j))) {
        node = node->next;
    }

    // If the next node is not the one we need, but is greater, 
    // it means that our node is not in the list
    if (node != nullptr && node->line == i && node->col == j) {
        return node;
    }
    return nullptr;
}


//O(1)
Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->lines = nrLines;
	this->cols = nrCols;
	this->list = nullptr;
}

//O(1)
int Matrix::nrLines() const {
	return this->lines;
}

//O(1)
int Matrix::nrColumns() const {
	return this->cols;
}

//BC:O(1)
//WC:O(n)
//AC:O(log n)
TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= this->lines || j < 0 || j >= this->cols)
        throw exception();

    Node* node = search_node(this->list, i, j);//this->list points to the first node

    if (node == nullptr)		//if the node with line i and column j doesn't exist => nullprtr
        return NULL_TELEM;
    else
        return node->value;

}
//BC:O(1)-the node is null in the begining and is placed first
//WC:O(n)-the node is last in the list
//AC:O(log n)
TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= this->lines || j < 0 || j >= this->cols)
        throw exception();

    Node* node = search_node(this->list, i, j);
    if (node == nullptr)
    {
        insert_node(&list, i, j, e);
        return NULL_TELEM;	//the element was null before
    }
    TElem old = node->value;
    node->value = e;
    if (e == 0) {
        delete_(i, j);
    }
    return old;
}

void Matrix::delete_node(Node* node)
{
    if (node == nullptr) {
        return;
    }

    if (node->prev == nullptr) {  // node is the head of the list
        list = node->next;
    }
    else {
        node->prev->next = node->next;
    }

    if (node->next != nullptr) {
        node->next->prev = node->prev;
    }

    delete node;
}

void Matrix::delete_(int i, int j)
{
    Node* node_to_delete = search_node(list, i, j);
    delete_node(node_to_delete);
}



