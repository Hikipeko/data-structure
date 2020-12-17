#ifndef QUEUE_H_STACK_H
#define QUEUE_H_STACK_H

#include "List.h"

template <typename T>
class Stack: public List<T>{
public:
    void push(T const& e){List<T>::insertAsLast(e);}
    T pop(){return List<T>::remove(List<T>::last());}
    T& top(){return List<T>::last()->data;}
};

#endif //QUEUE_H_STACK_H
