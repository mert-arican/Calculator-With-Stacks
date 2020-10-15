//
//  header.h
//  Stack
//
//  Created by Mert Arıcan on 13.10.2020.
//  Copyright © 2020 Mert Arıcan. All rights reserved.
//

#ifndef Header_h
#define Header_h
#define MAX 100
typedef struct stack {
    int count;
    int items[MAX];
} stack;

void push(stack *self, int item) {
    self->items[self->count++] = item;
}

int pop(stack *self) {
    return self->items[--self->count];
}

int top(stack *self) {
    return self->items[self->count-1];
}
//    char *expression = "(13+5*(6+8/4))";
//    char *expression = "8+2*(21/(7-4)+2)";
//    char *expression = "5+3*10/6-2";
//    char *expression = "(12+4-3)*(7*2+5)";
//    char *expression = "21/((4+8)*2-17)";
#endif /* Header_h */
