#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

class Test{
public:
    int val[3];
};

int main() {
    Test t1,t2;
    t1.val[0]= 1;
    t2 = t1;
    cout<<t2.val[0];
    t1.val[0] = 2;
    cout<<endl<<t2.val[0];
    char c = ' ';
    bool flag = true;
    return 0;
}
