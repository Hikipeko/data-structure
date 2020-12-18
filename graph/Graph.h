#ifndef DATA_STRUCTURE_GRAPH_H
#define DATA_STRUCTURE_GRAPH_H

#include <climits>
#include "../list/Stack.h"

typedef enum {
    UNDISCOVERED, DISCOVERED, VISITED
} VStatus;
typedef enum {
    UNDETERMINED, TREE, CROSS, FORWARD, DACKWARD
} EType;

template<typename Tv, typename Te> //顶点类型，边类型
class Graph {
private:
    void reset(); //所有顶点，边的辅助信息
    void BFS(int, int &); //广度优先算法
    void DFS(int, int &); //深度优先算法
    void BCC(int, int &, Stack<int> &); //基于DFS的双连同分量分解算法
    bool TSort(int, int &, Stack <Tv> *); //基于DFS的拓扑排序算法
    template<typename PU>
    void PFS(int, PU); //优先级搜索框架
public:
    //顶点
    int n; //顶点数
    virtual int insert(Tv const &) = 0; //插入顶点，返回编号
    virtual Tv remove(int) = 0; //删除顶点及其关联边，返回顶点信息
    virtual Tv &vertex(int) = 0; //顶底v的信息
    virtual int inDegree(int) = 0; //顶点v的入度
    virtual int outDegree(int) = 0; //顶点v的出度
    virtual int firstNbr(int) = 0; //顶点v的首个邻接顶点
    virtual int nextNbr(int, int) = 0;// 顶点v的下一邻接顶点
    virtual VStatus &status(int) = 0; //顶点v的状态
    virtual int &dTime(int) = 0; //顶点v的时间标签dTime
    virtual int &fTime(int) = 0; //顶点v的时间标签fTime
    virtual int &parent(int) = 0;//顶点v在遍历树中的父亲
    virtual int &priority(int) = 0; //顶点v在遍历树中的优先级数
    //边：这里约定，无向边统一转化为一堆互逆的有向边
    int e; //总边数
    virtual bool exist(int, int) = 0;// 边(v,u)是否存在
    virtual void insert(Te const &, int, int, int); //在顶点之间插入权重为w的边e
    virtual Te remove(int, int) = 0; //删除边返回信息
    virtual EType &type(int, int) = 0; //边属性
    virtual Te &edge(int, int) = 0; // 边的数据（该边存在）
    virtual int &weight(int, int) = 0;//边的权重
    //算法
    void bfs(int); //广度优先搜索算法
    void dfs(int); //深度优先搜索算法
    void bcc(int); //基于DFS的双连同分量分解算法
    Stack<Tv> *tSort(int); //基于DFS的拓扑排序算法
    void prim(int);//最小支撑树Prim算法
    void dijkstra(int);//最短路径Dijkstra算法
    template<typename PU>
    void pfs(int, PU); //优先级搜索框架
};

template<typename Tv, typename Te>
void Graph<Tv, Te>::reset() {
    for (int i = 0; i < n; i++) {
        status(i) = UNDISCOVERED;
        dTime(i) = fTime(i) = -1;
        parent(i) = -1;
        priority(i) = INT_MAX;
        for (int j = 0; j < n; j++)
            if (exists(i, j) type(i, j) = UNDETERMINED);
    }
}

#endif //DATA_STRUCTURE_GRAPH_H
