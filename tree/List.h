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

    ListNodePos find(T const &e,int n,ListNodePos p);

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


#endif //LIST_LIST_H
