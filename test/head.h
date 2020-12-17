//
// Created by 19791 on 2020/10/26.
//

#ifndef P6_HEAD_H
#define P6_HEAD_H
#include <iostream>
#include <sstream>
#include <assert.h>
using namespace std;

int fact(int n);

void try_catch();

void enumerate_test();

void flush_test();
void foo();
void bar();
void exception_test();
void print_array(int A[] , int n);
void print_triangle(int A[],int n);
void generate_help(char str[],int n);
void generate_strings(int K);

void add_1 (int arr[], int n);
class Test{
private:
    int* val;
public:
    Test(int x = 0){val = new int(x);}
    void add(){(*val)++;}
    void print() const{cout<<*val;}
};
#endif //P6_HEAD_H
