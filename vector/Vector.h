//
// Created by user on 2020/9/4.
//
#ifndef P3_VECTOR_H
#define P3_VECTOR_H

#include <cstdlib>

const int DEFAULT_CAPACITY = 3;

template<typename T>
class Vector {
protected:
    int _size;//规模、容量、数据区
    int _capacity;
    T *_elem;

    void copyFrom(T const *A, int lo, int hi);//复制区间[lo,hi)
    void expand();//扩容
    void shrink();//装填因子过小时压缩
    bool bubble(int lo, int hi);//扫描交换
    void bubbleSort(int lo, int hi);//气泡排序
    //int max(int lo,int hi);//
    void merge(int lo, int mi, int hi);

    void selectionSort(int hi, int lo);//选择排序
    void mergeSort(int lo, int hi);//归并排序
    //int partition (int lo,int hi);//轴点构造算法
    void quickSort(int lo, int hi);//快速排序算法
    void heapSort(int lo, int hi);//堆排序
public:
    //构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0);//s个v

    Vector(T const *A, int n) { copyFrom(A, 0, n); }

    Vector(T const *A, int lo, int hi) { copyfrom(A, lo, hi); }

    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); }

    Vector(Vector<T> const &V, int lo, int hi) { copyFrom(V._elem, lo, hi); }

    //构析函数
    ~Vector() { delete[] _elem; }

    //只读访问接口
    int size() const { return _size; }//规模
    bool empty() const { return !_size; }//判空
    int disordered() const;//是否排序
    int find(T const &e) const { return find(e, 0, _size); }//无序向量查找
    int find(T const &e, int lo, int hi) const;//
    int search(T const &e) const//有序向量查找
    { return (0 >= _size) ? -1 : search(e, 0, _size); }

    int search(T const &e, int lo, int hi) const;//有序向量区间查找
    //可写访问接口
    T &operator[](int r) const;//重载下标操作符
    Vector<T> &operator=(Vector<T> const &);//重载=以便克隆
    T remove(int r);//删除第r个元素
    int remove(int lo, int hi);//删除[lo,hi)之间元素
    int insert(int r, T const &e);//插入元素
    int insert(T const &e) { return insert(_size, e); }//作为末元素插入
    void sort(int lo, int hi);//区间排序
    void sort() { sort(0, _size); }//整体排序
    void unsort(int lo, int hi);//区间置乱
    void unsort() { unsort(0, _size); }

    int deduplicate();//无序去重
    int uniquify();//有序去重
    //遍历
    void traverse(void(*)(T &));

    template<typename VST>
    void traverse(VST &);
};


template<typename T>
void swap(T &a, T &b) {
    T temp = b;
    b = a;
    a = temp;
}

template<typename T>
Vector<T>::Vector(int c, int s, T v) {
    if (c < 2 * s) c = 2 * s;
    _elem = new T[_capacity = c];
    for (_size = 0; _size < s; _size++)
        _elem[_size] = v;
}

template<typename T>
void Vector<T>::copyFrom(T const *A, int lo, int hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi)
        _elem[_size++] = A[lo++];
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &V) {
    if (_elem) delete[] _elem;
    copyFrom(V._elem, 0, V._size());
    return *this;
}

template<typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template<typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return;
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 1; i < _size; i++)
        _elem[i] = oldElem[i];
}

template<typename T>
T &Vector<T>::operator[](int r) const {
    return _elem[r];
}

template<typename T>
void permute(Vector<T> &V) {
    for (int i = V._size(); i > 0; i--)
        swap(V[i - 1], V[rand() % i]);
}

template<typename T>
void Vector<T>::unsort(int lo, int hi) {
    T *V = _elem + lo;
    for (int i = hi - lo; i > 0; i--)
        swap(V[i - 1], V[rand() % i]);
}

template<typename T>
int Vector<T>::find(const T &e, int lo, int hi) const {
    while ((lo < hi--) && e != _elem[hi]);
    return hi;
}

template<typename T>
int Vector<T>::insert(int r, const T &e) {
    expand();
    for (int i = _size; i > r; i--)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    _size++;
    return r;
}

template<typename T>
int Vector<T>::remove(int lo, int hi) {
    if (lo == hi) return 0;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template<typename T>
T Vector<T>::remove(int r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template<typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    int i = 1;
    while (i < _size)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    return oldSize - _size;
}

template<typename T>
void Vector<T>::traverse(void (*visit)(T &)) {
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}

template<typename T>
template<typename VST>
//元素类型、操作器
void Vector<T>::traverse(VST &visit) {
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}

template<typename T>
int Vector<T>::disordered() const {
    int n = 0;
    for (int i = 1; i < _size; i++)
        if (_elem[i - 1] > _elem[i]) n++;
    return n;
}

template<typename T>
int Vector<T>::uniquify() {
    int i = 0, j = 0;
    while (++j < _size)
        if (_elem[i] != _elem[j]) _elem[++i] = _elem[j];
    _size = ++i;
    shrink();
    return j - i;
}

template<typename T>
int Vector<T>::search(const T &e, int lo, int hi) const {
    return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

template<typename T>
static int binSearch(T *A, T const &e, int lo, int hi) {
    while (lo < hi) {
        int mi = (lo + hi) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template<typename T>
void Vector<T>::sort(int lo, int hi) {
    switch (rand() % 5) {
        case 1:
            bubbleSort(lo, hi);
            break;
        case 2:
            selectionSort(lo, hi);
            break;
        case 3:
            mergeSort(lo, hi);
            break;
        case 4:
            heapSort(lo, hi);
            break;
        default:
            quickSort(lo, hi);
            break;
    }
}

template<typename T>
void Vector<T>::bubbleSort(int lo, int hi) {
    while (!bubble(lo, hi--));
}

template<typename T>
bool Vector<T>::bubble(int lo, int hi) {
    bool sorted = true;
    while (++lo < hi)
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]);
        }
    return sorted;
}

template<typename T>
void Vector<T>::mergeSort(int lo, int hi) {
    if (hi - lo < 2)return;
    int mi = (hi + lo) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template<typename T>
void Vector<T>::merge(int lo, int mi, int hi) {
    T *A = _elem + lo;
    int lb = mi - lo;
    int lc = hi - mi;
    T *B = new T[lb];
    for (int i = 0; i < lb; B[i] = A[i++]);
    T *C = _elem + mi;
    for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
        if ((j == lb) || (C[k] < B[j]))A[i++] = C[k++];
        if ((k == lc) || (C[k] >= B[j])) A[i++] = B[j++];
    }
}


#endif //P3_VECTOR_H