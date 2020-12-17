//
// Created by 19791 on 2020/11/17.
//

#ifndef MAIN_CPP_BITMAP_H
#define MAIN_CPP_BITMAP_H


class Bitmap {
private:
    char* M;
    int N;
protected:
    void init(int n){M = new char [N=(n+7)/8];memset(M,0,N);}
public:
    Bitmap(int n = 8){init(8);}
    Bitmap(char*file,int n = 8){init(n);}
};


#endif //MAIN_CPP_BITMAP_H
