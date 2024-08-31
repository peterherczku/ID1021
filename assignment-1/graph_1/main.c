#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <limits.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}

long bench(int n, int loop) {
    struct timespec t_start, t_stop;
    int *array = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) array[i] = i;

    int *idx = (int*)malloc(loop * sizeof(int));
    for (int i = 0; i < loop; i++) idx[i] = rand() % n;

    int sum = 0;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    for (int i = 0; i < loop; i++) sum += array[idx[i]];
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    free(array);
    free(idx);
    return wall;
}

int compare(const void *a, const void *b) {
    long long_a = *(const long*)a;
    long long_b = *(const long*)b;
    return (long_a > long_b) - (long_a < long_b);
}

double findMedian(long arr[], int n) {
    qsort(arr, n, sizeof(long), compare);

    if (n % 2 == 1) {
        return arr[n / 2];
    } else {
        return (arr[(n - 1) / 2] + arr[n / 2]) / 2.0;
    }
}

int main(int argc, char *argv[]) {
    int loop = 1000;
    int k = 10;
    for (int i = 0; i < 15; i++) {
        int n = (int) floor(pow(2, i)) * 1000;
        long min = LONG_MAX;
        long max = 0;
        long total = 0;
        for (int j = 0; j < k; j++) {
            long wall = bench(n, loop);
            if (wall < min) min = wall;
            if (wall > max) max = wall;
            total += wall;
        }

        printf("%d\t%0.2f\t%0.2f\t%0.2f\n",
               n, (double)min/loop, (double)max/loop, (double)total/loop/k);
    }

    /* for(int i = 0; i < 7; i++) {
         int n = sizes[i];
         int loop = 1000;
         int k = 1000;
         long min = LONG_MAX;

         long* results = (long*)malloc(sizeof(long)*k);
         for (int i = 0; i < k; i++) {
             long wall = bench(n, loop);
             if (wall < min) min = wall;
             results[i] = wall;
         }
         double median = findMedian(results, k);
         printf("median time: %0.2f ns/operation \t minimum time: %0.2f ns/operation \n", (double)median/loop, (double)min/loop);
         free(results); // Don't forget to free allocated memory
     }*/

    return 0;
}
