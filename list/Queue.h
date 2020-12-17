//
// Created by 19791 on 2020/9/29.
//

#ifndef LISTNODE_CPP_QUEUE_H
#define LISTNODE_CPP_QUEUE_H
#include "List.h"
template<typename T>
class Queue: public List<T>{
public:
    void enqueue(T const& e){return List<T>::insertAsLast(e);}
    T dequeue(){return List<T>::remove(List<T>::first());}
    T& front(){return List<T>::first()->data;}
};

#endif //LISTNODE_CPP_QUEUE_H
