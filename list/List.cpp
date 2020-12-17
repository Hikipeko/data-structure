//
// Created by 19791 on 2020/9/22.
//

#include <cstdlib>
#include "List.h"

template<typename T>
void List<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = nullptr;
    trailer->succ = nullptr;
    trailer->pred = header;
    _size = 0;
}

template<typename T>

T &List<T>::operator[](Rank r) const {
    ListNodePos p = first();
    while (r-- > 0)
        p = p->succ;
    return p->data;
}

template<typename T>
ListNodePos List<T>::find(const T &e, int n, ListNode<T> *p) {
    while (0 < n--)
        if (e == (p = p->pred)->data) return p;
    return nullptr;
}

template<typename T>
ListNodePos List<T>::insertAsFirst(const T &e) {
    _size++;
    return header->insertAsSucc(e);
}

template<typename T>
ListNodePos List<T>::insertAsLast(const T &e) {
    _size++;
    return trailer->insertAsPred(e);
}

template<typename T>
ListNodePos List<T>::insertA(ListNode<T> *p, const T &e) {
    _size++;
    return p->insertAsSucc(e);
}

template<typename T>
ListNodePos List<T>::insertB(ListNode<T> *p, const T &e) {
    _size++;
    return p->insertAsPred(e);
}

template<typename T>
void List<T>::copyNodes(ListNode<T> *p, int n) {
    init();
    while (n--) {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template<typename T>
List<T>::List(ListNode<T> *p, int n) {
    copyNodes(p, n);
}

template<typename T>
List<T>::List(const List<T> &L) {
    copyNode(L.first(), L.size());
}

template<typename T>
List<T>::List(const List<T> &L, Rank r, int n) {
    copyNodes(L[r], n);
}

template<typename T>
T List<T>::remove(ListNode<T> *p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template<typename T>
List<T>::~List() {
    clear();
    delete header;
    delete trailer;
}

template<typename T>
int List<T>::clear() {
    int oldSize = _size;
    while (0 < _size)
        remove(header->succ);
    return oldSize;
}

template<typename T>
int List<T>::deduplicate() {
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePos p = header;
    Rank r = 0;
    while (trailer != (p = p->succ)) {
        ListNodePos q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldSize - _size;
}

template<typename T>
void List<T>::traverse(void (*visit)(T &)) {
    for (ListNodePos p = header->succ; p != trailer; p = p->succ)
        visit(p->data);
}

template<typename T>
template<typename VST>
void List<T>::traverse(VST &visit) {
    for (ListNodePos p = header->succ; p != trailer; p = p->succ)
        visit(p->data);
}

template<typename T>
int List<T>::uniquify() {
    if (_size < 2) return 0;
    ListNodePos p = first();
    int oldSize = _size;
    ListNodePos q;
    while (trailer != (q = p->succ))
        (p->data == q->data) ? remove(q) : p = q;
    return oldSize - _size;
}

template<typename T>
//找到不大于e的最后者
ListNodePos List<T>::search(const T &e, int n, ListNode<T> *p) const {
    while (0 <= n--)
        if (((p = p->pred)->data) <= e)break;
    return p;
}

template<typename T>
void List<T>::sort(ListNode<T> *p, int n) {
    switch (rand() % 3) {
        case 1:
            insertionSort(p, n);
            break;
        case 2:
            selectoinSort(p, n);
            break;
        default:
            mergeSort(p, n);
            break;
    }
}

template<typename T>
void List<T>::insertionSort(ListNode<T> *p, int n) {
    for (int r = 0; r < n; r++) {
        insertA(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template<typename T>
void List<T>::selectionSort(ListNode<T> *p, int n) {
    ListNodePos head = p->pred;
    ListNodePos tail = p;
    for (int i = 0; i < n; i++) tail = tail->succ;
    while (1 < n) {
        ListNodePos max = selectMax(head->succ, n);
        insertB(tail, remove(max));
        tail = tail->pred;
        n--;
    }
}

template<typename T>
ListNodePos List<T>::selectMax(ListNode<T> *p, int n) {
    ListNodePos max = p;
    for (ListNodePos cur = p; 1 < n; n--)
        if ((cur = cur->succ)->data >= max->data)
            max = cur;
    return max;
}

template<typename T>
//当前列表自p起n个元素和列表L中q起m个元素归并
void List<T>::merge(ListNode<T> *&p, int n, List<T> &L, ListNode<T> *q, int m) {
    ListNodePos pp = p->pred;
    while (0 < m)
        if ((0 < n) && (p->data <= q->data)) {
            if ((q == (p = p->succ)))
                break;
            n--;
        } else {
            insertB(p,L.remove((q=q->succ)->pred));
            m--;
        }
    p = pp->succ;
}

template <typename T>
void List<T>::mergeSort(ListNodePos & p,int n){
    //valid(p) && rank(p) + n <= _size
    if(n<2) return;
    int m = n >>1;
    ListNodePos q = p;
    for (int i = 0;i<m;i++)
        q = q->succ;
    mergeSort(p,m);
    mergeSort(q,n-m);
    merge(p,m,*this,q,n-m);
}