//
// Created by 19791 on 2020/9/22.
//

#include "ListNode.h"
template <typename T>
ListNodePos ListNode<T>::insertAsPred(const T &e) {
    ListNode x = new ListNode(e,pred,this);
    pred->succ = x;
    pred = x;
    return x;
}

template <typename T>
ListNodePos ListNode<T>::insertAsSucc(const T &e) {
    ListNode x = new ListNode(e,this,succ);
    succ->pred = x;
    succ = x;
    return x;
}

