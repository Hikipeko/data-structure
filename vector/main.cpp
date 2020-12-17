#include <iostream>
#include "Vector.h"
#include "Stack.h"
#include <ctime>

using namespace std;

class rand_num {
    unsigned long next;
public:
    int rand_() {
        next = next * 1103515245 + 12345;
        return (unsigned int) (next / 65536) % 32768;
    }

    void srand_(unsigned int seed) { next = seed; }
};


int search_1(int arr[], int n, int a) {
    int hi = n;
    int lo = 0;
    int mi;
    while (hi > lo) {
        mi = (hi + lo) >> 1;
        if (a > arr[mi]) lo = mi;
        else if (a == arr[mi]) return mi;
        else hi = mi;
    }
    return -1;
}

int search_2(int arr[], int n, int a) {
    int hi = n-1;
    int lo = 0;
    int mi;
    while (hi != lo) {
        mi = lo + (hi - lo) * (a - arr[lo])/(arr[hi] - arr[lo]);
        if (a > arr[mi]) lo = mi;
        else if (a == arr[mi]) return mi;
        else hi = mi;
    }
    return -1;
}

static int MAX = 500000;

int main() {
    clock_t t1, t2;
    int arr[MAX];
    for(int i = 0;i<MAX;i++)
        arr[i] = i;
    t1 = clock();
    for (int i = 0; i < MAX ; i++)
        search_1(arr,MAX,1);
    t2 = clock();
    cout << t2 - t1 << endl;
}

