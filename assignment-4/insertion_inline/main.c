#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sys/timeb.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

int *unsorted(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n ; i++) {
        array[i] = rand()%(n*2);
    }
    return array;
}

void printArray(int* array, int length) {
    printf("[");
    for(int i = 0; i < length; i++) {
        printf("%d,", array[i]);
    }
    printf("]\n");
}

void sort(int* array, int n) {
    for (int i = 1; i < n; i++) {
        for(int j = i; j > 0 && array[j] < array[j - 1]; j--) {
            int temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;
        }
    }
}

void bench(int loop, int max, int steps) {
    struct timespec t_start, t_stop;
    for(int i = 1; i < (max / steps); i++) {
        int size = i * steps;
        long min = LONG_MAX;
        for (int k = 0; k < loop; k++) {
            int* array = unsorted(size);
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            sort(array, size);
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < min) min = wall;
            free(array);
        }
        printf("%d\t%0.5f\n", size, (double) min / 1000.0);
    }
}

int main() {
    bench(40, 25000, 1000);
    return 0;
}