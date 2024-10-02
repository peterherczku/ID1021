#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <sys/timeb.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

typedef struct node {
    int value;
    struct node *next;
} node;

typedef struct queue {
    node *first;
} queue;

void free_queue(queue *q) {
    node *nxt = q->first;
    while (nxt != NULL) {
        node *tmp = nxt->next;
        free(nxt);
        nxt = tmp;
    }
    free(q);
}

queue *create_queue() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->first = NULL;
    return q;
}

int empty(queue *q) {
    return (q->first == NULL);
}
void enqueue(queue* q, int v) {
    node *nd = (node*)malloc(sizeof(node));
    nd->value = v;
    nd->next = NULL;
    node *prv = NULL;
    node *nxt = q->first;
    while (nxt != NULL) {
        prv = nxt;
        nxt = nxt->next;
    }
    if (prv != NULL) {
        prv->next = nd;
    } else {
        q->first = nd;
    }
}
int dequeue(queue *q) {
    int res = 0;
    if (q->first != NULL) {
        res = q->first->value;
        node* nd = q->first;
        q->first = nd->next;
        free(nd);
    }
    return res;
}

queue *init_queue(int size) {
    queue* q = create_queue();
    for (int i = 0; i < size; i++) {
        enqueue(q, i);
    }
    return q;
}

void bench(int tries, int repeat, int max, int steps) {
    struct timespec t_start, t_stop;
    for(int i = 1; i < (max / steps); i++) {
        int size = i * steps;
        long minEnqueue = LONG_MAX;
        long minDequeue = LONG_MAX;
        for (int k = 0; k < tries; k++) {
            queue* q = init_queue(size);
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            for (int i = 0; i < repeat; i++) {
                enqueue(q, repeat);
            }
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < minEnqueue) minEnqueue = wall;
            free_queue(q);
        }
        for (int k = 0; k < tries; k++) {
            queue* q = init_queue(size);
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            for (int i = 0; i < repeat; i++) {
                dequeue(q);
            }
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < minDequeue) minDequeue = wall;
            free_queue(q);
        }
        printf("%d\t%0.5f\t%0.5f\n", size, (double) minEnqueue / repeat / 1000.0, (double) minDequeue / repeat);
    }
}

int main() {
    bench(40, 400, 10000, 500);
    return 0;
}