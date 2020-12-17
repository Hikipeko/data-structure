#include <iostream>
#include <cstring>
#include "Stack.h"
#include <cmath>

using namespace std;

#define N_OPTR 9
typedef enum {
    ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
} Operator;
const char pri[N_OPTR][N_OPTR] = {//运算优先级[栈顶][当前]
        //        +    -    *    /    ^    !    (    )    \0 当前
        /* +  */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
        /* -  */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
        /* *  */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
        /* /  */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
        /* ^  */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
        /* !  */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
        /* (  */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
        /* )  */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '=',
};

void readNumber(char *&p, Stack<double> &stk) {
    double num = double(*p - '0');
    double fraction = 0.1;
    while (isdigit(*(++p)))
        num = num * 10 + (*p - '0');
    if ('.' == *p) {
        while (isdigit(*(++p))) {
            num += fraction * (*p - '0');
            fraction /= 10;
        }
    }
    stk.push(num);
}

Operator optr2rank(char op) {
    switch (op) {
        case '+':
            return ADD;
        case '-':
            return SUB;
        case '*':
            return MUL;
        case '/':
            return DIV;
        case '^':
            return POW;
        case '!':
            return FAC;
        case '(':
            return L_P;
        case ')':
            return R_P;
        case '\0':
            return EOE;
        default:
            exit(-1);
    }
}

char orderBetween(char op1, char op2) {
    return pri[optr2rank(op1)][optr2rank(op2)];
}

void append(char *&rpn, double opnd) {
    int n = strlen(rpn);
    char buf[64];
    if (opnd != (float) (int) opnd)
        sprintf(buf, "%.2f \0", opnd);
    else
        sprintf(buf, "%d \0", (int) opnd);
    rpn = (char *) realloc(rpn, sizeof(char) * (n + strlen(buf) + 2));
    strcat(rpn, buf);
}

void append(char *&rpn, char optr) {
    int n = strlen(rpn);
    rpn = (char *) realloc(rpn, sizeof(char *) * (n + 4));
    sprintf(rpn + n, "%c ", optr);
    rpn[n + 2] = '\0';
}

int fact(int n) { return (n <= 0) ? 1 : n * fact(n - 1); }

double calcu(char op, double num) {
    return (double) fact(int(num));
}

double calcu(double num1, char op, double num2) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
        case '^':
            return pow(num1, num2);
        default:
            exit(-1);
    }
}

double evaluate(char *S, char *&RPN) {//对表达式S求值，并转化为逆波兰表达式
    int num_optr = 0;
    int num_opnd = 0;
    Stack<double> opnd;//运算数栈
    Stack<char> optr;//运算符栈
    optr.push('\0');
    while (!optr.empty()) {
        if (isdigit(*S)) {
            readNumber(S, opnd);
            append(RPN, opnd.top());
            num_opnd++;
        }
        switch (orderBetween(optr.top(), *S)) {
            case '<'://栈顶运算符优先级更低，计算推迟
                if (*S != '(') num_optr++;
                optr.push(*S);
                S++;
                if (num_optr != (opnd.size())) {
                    cout << "Invalid expression!" << endl;
                    exit(-1);
                }
                break;
            case '='://优先级相等，脱括号并处理下一个字符
                optr.pop();
                S++;
                break;
            case '>': {//栈顶优先级更好，处理计算，结果入栈
                char op = optr.pop();
                append(RPN, op);
                if ('!' == op) {
                    double pOpnd = opnd.pop();
                    opnd.push(calcu(op, pOpnd));
                } else {
                    double pOpnd2 = opnd.pop();
                    double pOpnd1 = opnd.pop();
                    opnd.push(calcu(pOpnd1, op, pOpnd2));
                    num_opnd--;
                }
                num_optr--;
                break;
            }
            default:
                exit(-1);
        }
    }
    return opnd.pop();
}

