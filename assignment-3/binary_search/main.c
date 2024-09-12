#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <limits.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

bool binary_search(int array[], int length, int key) {
    int first = 0;
    int last = length - 1;
    while (true) {
        int index = (first + last) / 2;
        if (array[index] == key) {
            return true;
        }
        if (array[index] < key && index < last) {
            first = index + 1;
            continue;
        }
        if (array[index] > key && index > first) {
            last = index;
            continue;
        }
        break;
    }
    return false;
}

int *sorted(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    int nxt = 0;
    for (int i = 0; i < n ; i++) {
        nxt += rand()%10 + 1;
        array[i] = nxt;
    }
    return array;
}

int *unsorted(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n ; i++) {
        array[i] = rand()%(n*2);
    }
    return array;
}

void benchmark_binary(int loop) {
    struct timespec t_start, t_stop;
    for(int i = 1; i < 50; i++) {
        int size = i * 100;
        long min = LONG_MAX;
        for (int k = 0; k < loop; k++) {
            int* array = sorted(size);
            int* keys = unsorted(size*2);
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            for(int j = 0; j < 100; j++) {
                binary_search(array, size, keys[j]);
            }
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < min) min = wall;
        }
        printf("%d\t%0.5f\n", size, (double) min / 100.0);
    }
}

int main() {
    benchmark_binary(300);
    return 0;
}