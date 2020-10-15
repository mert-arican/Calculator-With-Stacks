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
    // Pops the last two integers from operandStack, pops the operation from operationStack,
    // then performs the operation and pushes the result to operandStack.
    push(&operandStack, performOperation(pop(&operatorStack), pop(&operandStack), pop(&operandStack)));
}

int calculate(char *expression, unsigned long length) {
    for (int i = 0; i < length; i++) {
        int c = expression[i];
        if (isdigit(c)) {
            // If c is a digit, then read the operand with 'getOperandFromExpression' function.
            // This function mutates the i value. --- i becomes the integer's last digit's index.
            push(&operandStack, getOperandFromExpression(expression, &i));
        }
        // If c is a operator...
        else if (c == '(') {
            // if c is '(' then push it to the stack.
            push(&operatorStack, c);
        } else if (c == ')') {
            // if c is ')' then, until top of the operatorStack is '(' perform subroutine. Then pop '('.
            while (top(&operatorStack) != '(') { subroutine(); }
            pop(&operatorStack);
        }
        // If c is arithmetic operator...
        else if (operatorStack.count == 0 || top(&operatorStack) == '(' || getPrecedence(top(&operatorStack)) < getPrecedence(c)) {
            // if operatorStack is empty, or top operator is '(', or the precedence of the top operator is less than the precedence
            // of the c, push c to the operatorStack.
            push(&operatorStack, c);
        } else if (getPrecedence(top(&operatorStack)) >= getPrecedence(c)) {
            // if precedence of the top operator is bigger than or equal to the precedence of c,then until top operator's precedence
            // is less than the precedence of c, perform subroutine. Then push c to the stack.
            while (getPrecedence(top(&operatorStack)) >= getPrecedence(c)) { subroutine(); }
            push(&operatorStack, c);
        }
    }
    // until all of the operators are popped, i.e. used, perform subroutine.
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
