//
// Created by bro_b on 5/15/2023.
//
#include "Matrix.h"
#include <exception>
#include <stdexcept>
#ifndef LAB2SDA_MATRIXITERATOR_H
#define LAB2SDA_MATRIXITERATOR_H
class MatrixIterator {
private:
    const Matrix* matrix;
    int line;
    Node* current;
public:
    // constructor
    MatrixIterator(const Matrix* matrix, int line) {
        this->matrix = matrix;
        this->line = line;
        this->current = matrix->getHead(line);
    }

    // move to the next element
    void next() {
        if (current != nullptr) {
            current = current->next;
        }
    }

    // move to the previous element
    void previous() {
        if (current != nullptr) {
            current = current->prev;
        }
    }

    // check if there are more elements
    bool valid() const {
        return current != nullptr && current->line == line;
    }

    // get the value of the current element
    TElem getValue() const {
        if (current != nullptr) {
            return current->value;
        }
        throw std::exception();
    }

    // set the value of the current element
    void setValue(TElem value) {
        if (current != nullptr) {
            current->value = value;
        } else {
            throw std::exception();
        }
    }
};


#endif //LAB2SDA_MATRIXITERATOR_H
