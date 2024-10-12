#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

stack *new_stack() {
    node** array = (node**)malloc(10*sizeof(node*));
    stack *stk = (stack*)malloc(sizeof(stack));
    stk->size = 10;
    stk->array = array;
    stk->top = 0;
    return stk;
}
void push(stack *stk, node* val) {
    if (stk->top == stk->size) {
        int size = stk->size * 2;
        node** copy = (node**) malloc(size*sizeof(node*));
        for (int i = 0; i < stk->size; i++) {
            copy[i] = stk->array[i];
        }
        free(stk->array);
        stk->size = size;
        stk->array = copy;
    }
    stk->array[stk->top] = val;
    stk->top++;
}
node* pop(stack *stk) {
    if (stk->top == 0) return 0;
    if(stk->size > 4 && stk->top <= stk->size / 4) {
        int size = stk->size / 2;
        node** array = (node**) malloc(size * sizeof(node*));
        for (int i = 0; i < size / 2; i++) {
            array[i] = stk->array[i];
        }
        stk->size = size;
        free(stk->array);
        stk->array = array;
    }
    node* returnValue = stk->array[stk->top - 1];
    stk->top = stk->top - 1;
    return returnValue;
}

int is_empty(stack *stk) {
    return (stk->top == 0);
}