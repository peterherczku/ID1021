#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <sys/timeb.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

typedef struct queue {
    int firstIndex;
    int lastIndex;
    int* array;
    int size;
} queue;

queue* create_queue() {
    queue *q = (queue*) malloc(sizeof(queue));
    q->firstIndex = 0;
    q->lastIndex = 0;
    q->size = 4;
    q->array = (int*) malloc(sizeof(int)*q->size);
    return q;
}

void enqueue(queue* q, int value) {
    q->array[q->lastIndex] = value;
    q->lastIndex = (q->lastIndex + 1) % q->size;
    if(q->firstIndex == q->lastIndex) {
        int* newArray = (int*) malloc(sizeof(int)*q->size*2);
        int k = 0;
        for(int i = q->lastIndex; i < q->size; i++) {
            newArray[k] = q->array[i];
            k++;
        }
        for(int i = 0; i < q->lastIndex; i++) {
            newArray[k] = q->array[i];
            k++;
        }
        q->firstIndex = 0;
        q->lastIndex = k;
        int* arr = q->array;
        q->array = newArray;
        free(arr);
        q->size = q->size * 2;
    }
}

int dequeue(queue* q) {
    if(q->firstIndex == q->lastIndex) return -1;
    int val = q->array[q->firstIndex];
    q->firstIndex = (q->firstIndex + 1) % q->size;
    return val;
}

queue *init_queue(int size) {
    queue* q = create_queue();
    for (int i = 0; i < size; i++) {
        enqueue(q, i);
    }
    return q;
}

void free_queue(queue* q) {
    free(q->array);
    free(q);
}

void bench(int tries, int repeat, int max, int steps) {
    struct timespec t_start, t_stop;
    for(int i = 1; i <= (max / steps); i++) {
        int size = i * steps;
        long min = LONG_MAX;
        for (int k = 0; k < tries; k++) {
            queue* q = init_queue(size - repeat);
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            for (int i = 0; i < repeat; i++) {
                dequeue(q);
                enqueue(q, repeat);
            }
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < min) min = wall;
            free_queue(q);
        }
        printf("%d\t%0.5f\n", size, (double) min / repeat);
    }
}

int main() {
    bench(200, 1000, 30000, 1500);
    return 0;
}

