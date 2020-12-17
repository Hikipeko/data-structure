//
// Created by 19791 on 2020/9/22.
//

#ifndef LIST_LISTNODE_H
#define LIST_LISTNODE_H

typedef int Rank;//秩
#define ListNodePos ListNode<T>*//节点位置

template<typename T>//双向链表实现
struct ListNode {
    //成员——数值、前驱、后继
    T data;
    ListNodePos pred;
    ListNodePos succ;

    //构造函数
    ListNode() {};//针对header和trailer的构造
    ListNode(T e, ListNodePos p = nullptr, ListNodePos s = nullptr)
            : data(e), pred(p), succ(s) {}//默认构造器
    //操作接口
    ListNodePos insertAsPred(T const &e);//当前节点前插入新节点
    ListNodePos insertAsSucc(T const &e);//当前节点后插入新节点
};


template <typename T>
ListNodePos ListNode<T>::insertAsPred(const T &e) {
    ListNodePos x = new ListNode(e,pred,this);
    pred->succ = x;
    pred = x;
    return x;
}

template <typename T>
ListNodePos ListNode<T>::insertAsSucc(const T &e) {
    ListNodePos x = new ListNode(e,this,succ);
    succ->pred = x;
    succ = x;
    return x;
}
#endif //LIST_LISTNODE_H
