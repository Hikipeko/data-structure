//
// Created by 19791 on 2020/9/29.
//

#include "Stack.h"

bool paren(const char exp[], int lo, int hi) {
    Stack<char> S;
    for (int i = lo; i < hi; i++) {
        switch (exp[i]) {
            case '(':
            case '[':
            case '{':
                S.push(exp[i]);
                break;
            case ')':
                if ((S.isempty()) || S.pop() != '(') return false;
                break;
            case ']':
                if ((S.isempty()) || S.pop() != '[') return false;
                break;
            case '}':
                if ((S.isempty()) || S.pop() != '{') return false;
                break;
            default:
                break;
        }
    }
    return S.isempty();
}