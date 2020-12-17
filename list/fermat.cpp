#include <cmath>
#include <iostream>
using namespace std;

void fermat(int n){
    int flag = true;
    for(int a = sqrt(n);a>=0 && flag;a--)
        for(int b = sqrt(n-a*a);b>=0&& flag;b--)
            for(int c = sqrt(n - a*a - b*b);c>=0;c--){
                int d = sqrt(n-a*a-b*b-c*c);
                if (d*d == n-a*a-b*b-c*c){
                    flag = false;
                    cout<<n<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<endl;
                    break;
                }
            }
}
