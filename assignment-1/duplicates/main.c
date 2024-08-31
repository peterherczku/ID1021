#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <limits.h>
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

long duplicates(int n) {
    struct timespec t_start, t_stop;
    int *array_a = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) array_a[i] = rand()%(n*2);
    int *array_b = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) array_b[i] = rand()%(n*2);
    int sum = 0;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    for (int i = 0; i < n; i++) {
        int key = array_a[i];
        for (int j = 0; j < n; j++) {
            if (key == array_b[j]) {
                sum++;
                break;
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    return wall;
}

int main(int argc, char *argv[]) {
    for (int n = 100; n < 5000; n+=100) {
        long min = LONG_MAX;
        for(int j = 0; j < 10; j++) {
            long wall = duplicates(n);
            if (wall < min) min = wall;
        }
        printf("%d\t%0.2f\n", n, (double)min);
    }

}