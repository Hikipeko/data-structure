#include <iostream>
#include <time.h>


using namespace std;
const int MAX = 500000;

int B[MAX];

void merge(int *val, int lo, int mi, int hi) {
    if (val[mi - 1] <= val[mi]) return;
    for (int i = 0; i < (mi - lo); i++)
        B[i] = val[lo + i];
    int pos1 = 0;
    int pos2 = mi;
    int curr = lo;
    while (curr<hi){
        if (!(pos2 == hi) && (pos1 == (mi - lo) || val[pos2] < B[pos1]))
            val[curr++] = val[pos2++];
        else if (pos2 == hi || val[pos2] >= B[pos1])
            val[curr++] = B[pos1++];}
}

void merge_sort(int *var, int lo, int hi) {
    if ((hi - lo) < 2)
        return;
    int mi = (hi + lo) / 2;
    merge_sort(var, lo, mi);
    merge_sort(var, mi, hi);
    merge(var, lo, mi, hi);
}

int test_merge() {
    clock_t t1, t2,t3,t4,t5;
    int val[MAX];
    for (int i = 0; i < MAX; i++)
        val[i] = MAX - i;

    t1 = clock();
    merge_sort(val, 0, MAX);
    t2 = clock();
    merge_sort(val, 0, MAX);
    t3 = clock();
    cout << int(t2 - t1)<<endl;
    cout<<int(t3 - t2)<<endl;
    return 0;
}

