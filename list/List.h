//
// Created by Hikipeko on 2020/9/22.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include "ListNode.h"

template<typename T>
class List {
private:
    //规模、头哨兵、尾哨兵
    int _size;
    ListNodePos header;
    ListNodePos trailer;
protected:
    void init();//列表创建时的初始化

    int clear();//清除所有节点

    void copyNodes(ListNodePos p, int n);//复制列表中自位置p起的第n项
    void merge(ListNodePos&, int, List<T> &, ListNodePos, int);//归并
    void mergeSort(ListNodePos&, int);//对从p开始连续n个节点归并排序
    void selectionSort(ListNodePos, int);//对从p开始连续n个节点选择排序
    void insertionSort(ListNodePos, int);//对从p开始连续n个节点插入排序
public:
    //构造函数
    List() { init(); }//默认
    List(List<T> const &L);//整体复制列表L
    List(List<T> const &L, Rank r, int n); //复制列表L中自第r项起的n项
    List(ListNodePos p, int n);//复制列表中自位置p起的n项
    //析构函数
    ~List();//释放（包含头、尾哨兵在内的）所有节点
    //只读访问接口
    Rank size() const { return _size; }

    bool empty() const { return _size <= 0; }

    T &operator[](Rank r) const;//重载，支持循秩访问（效率低）
    ListNodePos first() const { return header->succ; }//首节点位置
    ListNodePos last() const { return trailer->pred; }//末节点位置
    bool valid(ListNodePos p)//判断位置p是否对外合法
    { return p && (trailer != p) && (header != p); } //将头、尾节点等同于NULL
    int disorder() const;

    ListNodePos find(T const &e) const//无序列表查找
    { return find(e, _size, trailer); }

    ListNodePos find(T const &e, int n, ListNodePos p);

    ListNodePos search(T const &e) const //有序列表查找
    { return search(e, _size, trailer); }

    ListNodePos search(T const &e, int n, ListNodePos p) const; //有序区间查找
    ListNodePos selectMax(ListNodePos p, int n); //在p及其n-1个后继中选出最大者
    ListNodePos selectMax() { return selectMax(header->succ, _size); } //整体最大者
// 可写访问接口
    ListNodePos insertAsFirst(T const &e); //将e当作首节点插入
    ListNodePos insertAsLast(T const &e); //将e当作末节点插入
    ListNodePos insertA(ListNodePos p, T const &e); //将e当作p的后继插入（After）
    ListNodePos insertB(ListNodePos p, T const &e); //将e当作p的前驱插入（Before）
    T remove(ListNodePos p); //删除合法位置p处的节点,返回被删除节点
    void merge(List<T> &L) { merge(header->succ, _size, L, L.header->succ, L._size); } //全列表归并
    void sort(ListNodePos p, int n); //列表区间排序
    void sort() { sort(first(), _size); } //列表整体排序
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    void reverse(); //前后倒置（习题）
// 遍历
    void traverse(void (* )(T &)); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
    template<typename VST>
    //操作器
    void traverse(VST &); //遍历，依次实施visit操作（函数对象，可全局性修改）
};

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
#endif //LIST_LIST_H
