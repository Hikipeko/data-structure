//
// Created by 19791 on 2020/10/26.
//
#include "head.h"

using std::cout;

int fact(int n) {
    if (n < 0) { throw n; }
    return n ? fact(n - 1) * n : 1;
}

void try_catch() {
    int x;
    int *p = &x;
    try { *p = fact(-1); }
    catch (int n) {
        cout << n << " is negative!\n";
    }
    cout << x;
}

enum QUQ {
    a, b, c = 3, d, e = 1, f, g = f + d
};

void enumerate_test() {
    QUQ lovelyCat = e;
    cout << static_cast<int>(lovelyCat) << endl;
}

#include <unistd.h>

void flush_test() {
    cout << "Line 1...";
    usleep(1000000);
    cout << "\nLine 2" << endl;
    cout << "Line 3" << endl;
}

void foo() {
    try {
        throw "as"; // try int and double
    }
    catch (char c) {
        cout << "Char " << c << " caught!" << endl;
    }
    cout << "Foo executed." << endl;
}

void bar() {
    try {
        foo();
    }
    catch (int i) {
        cout << "Int " << i << " caught!" << endl;
    }
    cout << "Bar executed." << endl;
}

void exception_test() {
    try {
        bar();
    }
    catch (...) {
//default constructor
        std::cout << "Default catch!" << endl;
    }
    cout << "Main executed." << endl;
}

void print_array(int A[], int n)
// EFFECTS: Print current array in the end so
// that smaller arrays are printed first
{
    for (int i = 0; i < n; i++) {
        if (i == n - 1)
            cout << A[i] << " ";
        else
            cout << A[i] << ", ";
    }
    cout << endl;
}

void print_triangle(int A[], int n) {
    if (n == 1) {
        print_array(A, 1);
        return;
    }
    int *B = new int[n - 1];
    for (int i = 0; i < n - 1; i++)
        B[i] = A[i] + A[i + 1];
    print_triangle(B, n - 1);
    delete[] B;
    print_array(A, n);
}

void generate_strings(int K) {
    if (K < 1) return;
    char *str = new char[K + 1];
    str[K] = '\0';
    str[K - 1] = '0';
    generate_help(str, K - 2);
    str[K - 1] = '1';
    generate_help(str, K - 2);
}

void generate_help(char str[], int n) {
    if (n == -1) {
        cout << str << ' ';
        return;
    }
    if (str[n + 1] == '0') {
        str[n] = '0';
        generate_help(str, n - 1);
        str[n] = '1';
        generate_help(str, n - 1);
    } else {
        str[n] = '0';
        generate_help(str, n - 1);
    }
}

void add_1(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i]++;
}