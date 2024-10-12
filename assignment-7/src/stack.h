#include "tree.h"

typedef struct stack {
    int top;
    int size;
    node** array;
} stack;


stack *new_stack();
void push(stack *stk, node* val);
node* pop(stack *stk);
int is_empty(stack *stk);