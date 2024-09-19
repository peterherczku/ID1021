#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sys/timeb.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

void printArray(int* array, int length) {
    printf("[");
    for(int i = 0; i < length; i++) {
        printf("%d,", array[i]);
    }
    printf("]\n");
}

int *unsorted(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n ; i++) {
        array[i] = rand()%(n*2);
    }
    return array;
}

void swap(int* array, int index1, int index2) {
    int temp = array[index2];
    array[index2] = array[index1];
    array[index1] = temp;
}

void merge(int* org, int* aux, int lo, int mid, int hi) {
    for(int i = lo; i <= hi; i++) {
        aux[i] = org[i];
    }
    int i = lo;
    int j = mid + 1;

    for (int k = lo; k <= hi; k++) {
        if(i > mid) {
            org[k] = aux[j];
            j++;
        } else if(j > hi) {
            org[k] = aux[i];
            i++;
        } else if(aux[i] <= aux[j]) {
            org[k] = aux[i];
            i++;
        } else {
            org[k] = aux[j];
            j++;
        }
    }
}

void merge_sort(int* org, int* aux, int lo, int hi) {
    if (lo != hi) {
        int mid = (lo + hi) / 2;
        merge_sort(org, aux, lo, mid);
        merge_sort(org, aux, mid + 1, hi);
        merge(org, aux, lo, mid, hi);
    }
}

void sort(int* org, int n) {
    if (n == 0) return;
    int *aux = (int*) malloc(n * sizeof(int));
    merge_sort(org, aux, 0, n - 1);
    free(aux);
}

void bench(int loop, int max, int steps) {
    struct timespec t_start, t_stop;
    for(int i = 1; i < (max / steps); i++) {
        int size = i * steps;
        long min = LONG_MAX;
        long sum = 0;
        for (int k = 0; k < loop; k++) {
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            for (int j = 0; j < 10; j++) {
                int* array = unsorted(size);
                sort(array, size);
                free(array);
            }
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            sum += wall;
        }
        printf("%d\t%0.5f\n", size, (double) sum / loop / 10.0 / 1000.0);
    }
}

int main() {
    bench(40, 25000, 500);
    return 0;
}