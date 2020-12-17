//
// Created by 19791 on 2020/9/29.
//
struct Queen{
    int x,y;
    Queen(int xx = 0,int yy = 0):x(xx),y(yy){};
    bool operator==(Queen const& q) const{
        return (x == q.x)||(y == q.y)||(x+y == q.x+q.y)|| (x-y == q.x - q.y);
    }
    bool operator!=(Queen const& q) const{
        return !(*this == q);
    }
};
