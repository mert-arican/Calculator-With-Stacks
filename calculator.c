//
//  main.c
//  Stack
//
//  Created by Mert Arıcan on 13.10.2020.
//  Copyright © 2020 Mert Arıcan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"

stack operatorStack;
stack operandStack;

int performOperation(char operator, int firstOperand, int secondOperand) {
    switch (operator) {
        case '+': return firstOperand + secondOperand;
        case '-': return secondOperand - firstOperand;
        case '*': return firstOperand * secondOperand;
        case '/': return secondOperand / firstOperand;
        default: return 0;
    }
}

int getOperandFromExpression(char *expression, int *index) {
    int i = *index, operand = 0;
    while (isdigit(expression[*index])) { (*index)++; }
    for ((*index)--; i <= *index; i++) { operand += ((pow(10, (*index)-i)) * (expression[i] - '0')); }
    return operand;
}

int getPrecedence(int operator) {
    if (operator == '+' || operator == '-') { return 1; }
    else if (operator == '*' || operator == '/') { return 2; }
    return 0;
}

void subroutine(void) {
    push(&operandStack, performOperation(pop(&operatorStack), pop(&operandStack), pop(&operandStack)));
}

int calculate(char *expression, unsigned long length) {
    for (int i = 0; i < length; i++) {
        int c = expression[i];
        if (isdigit(c)) {
            push(&operandStack, getOperandFromExpression(expression, &i));
        } else if (c == '(') {
            push(&operatorStack, c);
        } else if (c == ')') {
            while (top(&operatorStack) != '(') { subroutine(); }
            pop(&operatorStack);
        } else if (operatorStack.count == 0 || top(&operatorStack) == '(' || getPrecedence(top(&operatorStack)) < getPrecedence(c)) {
            push(&operatorStack, c);
        } else if (getPrecedence(top(&operatorStack)) >= getPrecedence(c)) {
            while (getPrecedence(top(&operatorStack)) >= getPrecedence(c)) { subroutine(); }
            push(&operatorStack, c);
        }
    }
    while (operatorStack.count > 0) { subroutine(); }
    return top(&operandStack);
}

int main(int argc, const char * argv[]) {
    operandStack = (stack) { .count = 0 };
    operatorStack = (stack) { .count = 0 };
    char *expression = "(12*(4+3-16/8)-5)";
    int result = calculate(expression, strlen(expression));
    printf("Result of %s = %d\n", expression, result);
    return 0;
}
