#ifndef MAIN_CPP_BINTREE_H
#define MAIN_CPP_BINTREE_H

#include "BinNode.h"
#include "Queue.h"

template<typename T>
class BinTree {
protected:
    int _size;
    NodePos _root;

    virtual int updateHeight(NodePos x);//更新节点x的高度
    void updateHeightAbove(NodePos x);//更新节点x和祖先的高度
public:
    BinTree() : _size(0), _root(nullptr) {}//构造函数
    ~BinTree() { if (0 < _size) remove(_root); }

    int size() const { return _size; }

    bool empty() const { return !_root; }

    NodePos root() const { return _root; }

    NodePos insertAsRoot(T const &e);//插入根节点
    NodePos insertAsLC(NodePos x, T const &e);//作为左孩子插入
    NodePos insertAsRC(NodePos x, T const &e);//作为右孩子插入
    NodePos attachAsLC(NodePos x, BinTree<T> *&t);//t作为左子树插入
    NodePos attachAsRC(NodePos x, BinTree<T> *&t);//t作为右子树插入
    int remove(NodePos x);//删除以x为节点的子树，返回size

    BinTree<T> *secede(NodePos x);//将子树x从树种摘除，转化为一棵独立的树
    template<typename VST>
    //操作器
    void travLevel(VST &visit) { if (_root) _root->travLevel(visit); }//层次遍历
    template<typename VST>
    void travPre(VST &visit) { if (_root) _root->travPre(visit); }//先序遍历
    template<typename VST>
    void travIn(VST &visit) { if (_root) _root->travIn(visit); }//中序遍历
    template<typename VST>
    void travPost(VST &visit) { if (_root) _root->travPost(visit); }//后序遍历
    bool operator<(BinTree<T> const &t)//比较器
    { return _root && t._root && lt(_root, t._root); }

    bool operator==(BinTree<T> const &t)//判等器
    { return _root && t._root && (_root == t._root); }
};

template<typename T>
int BinTree<T>::updateHeight(BinNode<T> *x) {
    return x->height = 1 + max(stature(x->lc)), stature(x->rc);
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNode<T> *x) {
    while (x) {
        int curr_height = x->height;
        if (curr_height == updateHeight(x))
            return;
        x = x->parent;
    }
}

template<typename T>
NodePos BinTree<T>::insertAsRoot(const T &e) {
    _size = 1;
    return _root = new BinNode<T>(e);
}

template<typename T>
NodePos BinTree<T>::insertAsLC(BinNode<T> *x, const T &e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template<typename T>
NodePos BinTree<T>::insertAsRC(BinNode<T> *x, const T &e) {
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template<typename T>
NodePos BinTree<T>::attachAsLC(BinNode<T> *x, BinTree<T> *&S) {
    x->lc = S->root;
    if (x->lc)x->lc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = nullptr;
    S->_size = 0;
    release(S);
    S = nullptr;
    return x;
}

template<typename T>
NodePos BinTree<T>::attachAsRC(BinNode<T> *x, BinTree<T> *&S) {
    x->rc = S->root;
    if (x->rc)x->rc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = nullptr;
    S->_size = 0;
    release(S);
    S = nullptr;
    return x;
}

template<typename T>
int BinTree<T>::remove(BinNode<T> *x) {
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}

template<typename T>
static int removeAt(NodePos x) {
    if (!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data);
    release(x);
    return n;
}

template<typename T>
BinTree<T> *BinTree<T>::secede(NodePos x) {
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);
    auto *S = new BinTree<T>;
    S->root = x;
    x->parent = nullptr;
    S->_size = x->_size;
    _size -= S->_size;
    return S;
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre_R(NodePos x, VST &visit) {
    if (!x) return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::travPost_R(NodePos x, VST &visit) {
    if (!x) return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_R(NodePos x, VST &visit) {
    if (!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::travLevel(BinNode<T> *_x, VST &) {
    Queue<NodePos> Q;
    Q.enqueue(_x);
    while (!Q.empty()) {
        NodePos x = Q.dequeue();
        visit(x->data);
        if (x->lc) Q.enqueue(x->lc);
        if (x->rc) Q.enqueue((x->rc));
    }
}

template<typename T>
int num_decendant(NodePos x) {
    if (x == nullptr) return 0;
    else return (x->lc->size() + x->rc->size());
}

template<typename T>
int BinNode<T>::size() {
    return num_decendant(this) - 1;
}


#endif //MAIN_CPP_BINTREE_H
