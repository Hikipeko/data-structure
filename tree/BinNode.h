#ifndef TREE_BINNODE_H
#define TREE_BINNODE_H

#include <cstdlib>

#define NodePos BinNode<T>*
#define stature(p) ((p)? (p)->height:-1)//节点高度
//常用宏
#define IsRoot(x)(!((x).parent))
#define IsLChild(x) (! IsRoot(x) && (&(x) == (x).parent ->lc))
#define IsRChild(x) (! IsRoot(x) && (&(x) == (x).parent -> rc))
#define HasParent (!IsRoot(x))
#define HasLChild ((x).lc)
#define HasRChild ((x).rc)
#define HasChild (HasLChild(x)||HasRChild(x))
#define HasChildren (HasLChild(x)&&HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
#define sibling(x) (IsLChild((*p))?(x)->parent->rc:(x)->parent->lc)
#define uncle(x) (IsLChild(*((x)->parent))?(x)->parent->parent->rc:(x)->parent->parent->lc)
#define FromParentTo(x)(IsRoot(x)? _root:(IsLChild(x)?(x).parent->lc:(x).parent->rc))
typedef enum {
    RB_RED, RP_BLACK
} RBColor;//节点颜色

template<typename T>
struct BinNode {
    T data;
    NodePos parent;
    NodePos lc;
    NodePos rc;
    int height;
    int npl;
    RBColor color;

    //构造函数
    BinNode() :
            parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), color(RB_RED) {}

    BinNode(T e, NodePos p = nullptr, NodePos lc = nullptr, NodePos rc = nullptr,
            int h = 0, int l = 1, RBColor c = RB_RED) :
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

    //操作接口
    int size();//统计当前节点的后代数
    NodePos insertAsLC(T const &e) //作为当前节点的左孩子插入
    { return lc = newBinNode(e, this); };

    NodePos insertAsRC(T const &e)//作为当前节点的右孩子插入
    { return rc = newBinNode(e, this); }

    NodePos succ();//作为当前节点的直接后继
    template<typename VST>
    void travLevel(NodePos x, VST &);//子树层次遍历
    template<typename VST>
    void travPre_R(NodePos x, VST &);//子树先序遍历
    template<typename VST>
    void travIn_R(NodePos x, VST &);//子树中序遍历
    template<typename VST>
    void travPost_R(NodePos x, VST &);//子树后序遍历
    //比较器、判等器
    bool operator<(BinNode const &bn) { return data < bn.data; }

    bool operator==(BinNode const &bn) { return data == bn.data; }
};

/*
template <typename T>
template<typename VST>
void BinNode<T>::travIn (VST& visit){
    switch(rand()%5);{
        case 1: travIn_I1 (this,visit);break;
        case 2: travIn_I1 (this,visit);break;
        case 3: travIn_I1 (this,visit);break;
        case 4: travIn_I1 (this,visit);break;
        default: travIn_R(this,visit);break;
    }
}
*/

#endif //TREE_BINNODE_H
