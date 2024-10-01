#include <stdio.h>
#include <stdlib.h>

int MAX=100;

int stack[100];
int top = -1;

void push(int x) {
    if (top == MAX - 1) {
        printf("Stack ovrflow\n");
        return;
    }
    stack[++top] = x;
}

int pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

void reverse(char* elem, int length) {
    int i;
    char temp;
    for (i = 0; i < length / 2; i++) {
        temp = elem[i];
        elem[i] = elem[length - i - 1];
        elem[length - i - 1] = temp;
    }
}

void infixToPrefix(char* infix, char* prefix) {
    int len = 0;
    while (infix[len] != '\0') len++;
    
    reverse(infix, len);
    
    char op_stack[MAX];
    int op_top = -1;
    int i, j = 0;

    for (i = 0; i < len; i++) {
        if (isDigit(infix[i])) {
            prefix[j++] = infix[i];
        } else if (infix[i] == ')') {
            op_stack[++op_top] = infix[i];
        } else if (infix[i] == '(') {
            while (op_top != -1 && op_stack[op_top] != ')') {
                prefix[j++] = op_stack[op_top--];
            }
            op_top--;
        } else if (isOperator(infix[i])) {
            while (op_top != -1 && precedence(op_stack[op_top]) > precedence(infix[i])) {
                prefix[j++] = op_stack[op_top--];
            }
            op_stack[++op_top] = infix[i];
        }
    }

    while (op_top != -1) {
        prefix[j++] = op_stack[op_top--];
    }

    prefix[j] = '\0';
    reverse(prefix, j);
}

int evaluatePrefix(char* prefix) {
    int len = 0;
    while (prefix[len] != '\0') len++;

    for (int i = len - 1; i >= 0; i--) {
        if (isDigit(prefix[i])) {
            push(prefix[i] - '0');
        } else if (isOperator(prefix[i])) {
            int op1 = pop();
            int op2 = pop();
            if (prefix[i] == '+') push(op1 + op2);
            if (prefix[i] == '-') push(op1 - op2);
            if (prefix[i] == '*') push(op1 * op2);
            if (prefix[i] == '/') push(op1 / op2);
            if (prefix[i] == '^') {
                int result = 1;
                for (int j = 0; j < op2; j++) result *= op1;
                push(result);
            }
        }
    }
    return pop();
}

int main() {
    char infix[MAX], prefix[MAX];
    printf("Enter the infix elemression:");
    scanf("%s", infix);

    infixToPrefix(infix, prefix);
    printf("Prefix epexression: %s\n", prefix);

    int result = evaluatePrefix(prefix);
    printf("Result of evaluation: %d\n", result);

    return 0;
}
