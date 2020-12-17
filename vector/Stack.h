//
// Created by Hikipeko on 2020/9/25.
//

#ifndef P3_STACK_H
#define P3_STACK_H

#include "Vector.h"

template<typename T>
class Stack : public Vector<T> {
public:
    void push(T const &e) { Vector<T>::insert(Vector<T>::size(), e); }

    T pop() { return Vector<T>::remove(Vector<T>::size() - 1); }

    T &top() { return (*this)[Vector<T>::size() - 1]; }

    bool isempty() { return Vector<T>::empty(); }
};

bool paren(const char exp[], int lo, int hi);
#endif //P3_STACK_H
