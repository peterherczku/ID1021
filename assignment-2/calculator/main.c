#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct stack {
    int top;
    int size;
    int *array;
} stack;

stack *new_stack() {
    int *array = (int*)malloc(10*sizeof(int));
    stack *stk = (stack*)malloc(sizeof(stack));
    stk->size = 10;
    stk->array = array;
    stk->top = 0;
    return stk;
}
void push(stack *stk, int val) {
    if (stk->top == stk->size) {
        printf("Extending size...\n");
        int size = stk->size * 2;
        int *copy = (int*) malloc(size*sizeof(int));
        for (int i = 0; i < stk->size; i++) {
            copy[i] = stk->array[i];
        }
        free(stk->array);
        stk->size = size;
        stk->array = copy;
    }
    stk->array[stk->top] = val;
    stk->top = stk->top + 1;
}
int pop(stack *stk) {
    int returnValue = stk->array[stk->top - 1];
    stk->top = stk->top - 1;
    return returnValue;
}
int main() {
    stack *stk = new_stack();
    printf("HP-35 pocket calculator\n");
    size_t n = 10;
    char *buffer = (char*)malloc(n*sizeof(char));
    bool run = true;

    // 42 -
    while(run) {
        printf(" > ");
        getline(&buffer, &n, stdin);
        if (strcmp(buffer, "\n") == 0) {
            run = false;
        } else if (strcmp(buffer, "+\n") == 0) {
            int a = pop(stk);
            int b = pop(stk);
            push(stk, a+b);
        } else if(strcmp(buffer, "-\n") == 0) {
            int a = pop(stk);
            int b = pop(stk);
            push(stk, b-a);
        } else if(strcmp(buffer, "*\n") == 0) {
            int a = pop(stk);
            int b = pop(stk);
            push(stk, a*b);
        } else if(strcmp(buffer, "/\n") == 0) {
            int a = pop(stk);
            int b = pop(stk);
            push(stk, b/a);
        } else {
            int val = atoi(buffer);
            push(stk, val);
        }
    }
    printf("the result is: %d\n\n", pop(stk));
    printf("I love reversed polish notation, don't you?\n");
}