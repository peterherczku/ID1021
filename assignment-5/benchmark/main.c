#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sys/timeb.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

typedef struct cell {
    int value;
    struct cell *tail;
} cell;

typedef struct linked {
    cell *first;
} linked;

linked *create_linked() {
    linked *new = (linked*)malloc(sizeof(linked));
    new->first = NULL;
    return new;
}

void free_linked(linked *lnk) {
    cell *nxt = lnk->first;
    while (nxt != NULL) {
        cell *tmp = nxt->tail;
        free(nxt);
        nxt = tmp;
    }
    free(lnk);
}

void add(linked *lnk, int item) {
    cell *newCell = (cell*)malloc(sizeof(cell));
    newCell->value = item;
    newCell->tail = lnk->first;
    lnk->first = newCell;
}

int length(linked *lnk) {
    int i = 0;
    cell* current = lnk->first;
    while(current != NULL) {
        i++;
        current = current->tail;
    }
    return i;
}

bool find(linked *lnk, int item) {
    cell* current = lnk->first;
    while(current != NULL) {
        if(current->value == item) return true;
        current = current->tail;
    }
    return false;
}

void removeItem(linked *lnk, int item) {
    cell* prev = NULL;
    cell* current = lnk->first;
    while(current != NULL) {
        if(current->value == item) {
            if(prev == NULL) {
                lnk->first = current->tail;
            } else {
                prev->tail = current->tail;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->tail;
    }
}

void append(linked *a, linked *b) {
    cell *nxt = a->first;
    cell *prv = NULL;
    while(nxt != NULL) {
        prv = nxt;
        nxt = nxt->tail;
    }
    if (prv != NULL) {
        prv->tail = b->first;
    } else {
        a->first = b->first;
    }
    b->first = NULL;
}

linked *init_list(int n) {
    linked *a = create_linked();
    for (int i = 0; i < n; i++) {
        add(a, i);
    }
    return a;
}

void bench(int loop, int max, int steps) {
    struct timespec t_start, t_stop;
    for(int i = 1; i < (max / steps); i++) {
        int size = i * steps;
        long min = LONG_MAX;
        for (int k = 0; k < loop; k++) {
            linked* listA = init_list(size);
            linked* listB = init_list(1000);
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            append(listA, listB);
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < min) min = wall;
            free_linked(listA);
        }
        printf("%d\t%0.5f\n", size, (double) min / 1000.0);
    }
}


int main() {
    bench(100, 100000, 2500);
    return 0;
}
