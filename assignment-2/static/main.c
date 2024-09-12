#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>


long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

typedef struct stack {
    int top;
    int size;
    int *array;
} stack;
stack *new_stack(int size) {
    int *array = (int*)malloc(size*sizeof(int));
    stack *stk = (stack*)malloc(sizeof(stack));
    stk->array = array;
    stk->size = size;
    stk->top = 0;
    return stk;
}
void push(stack *stk, int val) {
    if(stk->top == stk->size) {
        printf("Stack overflow");
        return;
    }
    stk->array[stk->top] = val;
    stk->top++;
}

int pop(stack *stk) {
    if (stk->top == 0) return 0;
    stk->top--;
    int val = stk->array[stk->top];
    return val;
}

long bench(int size) {
    struct timespec t_start, t_stop;

    stack *stk = new_stack(size);
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    for (int i = 0; i < size; i++) {
        push(stk, i);
    }

    for (int i = 0; i < size; i++) {
        pop(stk);
    }
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    return nano_seconds(&t_start, &t_stop);

}

int main() {
    for (int i = 10000; i < 50000; i += 1000) {
        long min = LONG_MAX;
        for(int j = 0; j < 5; j++) {
            long wall = bench(i);
            if (wall < min) min = wall;
        }
        printf("%d\t%ld\n", i, min/(i*2));
    }
}
