#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <sys/timeb.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}
int AREAS = 10000;
int BUFFER = 200;

typedef struct area {
    int zip;
    char *name;
    int pop;
} area;

typedef struct codes {
    area *areas;
    int n;
} codes;

codes *read_postcodes(char *file) {
    codes *postnr = (codes*)malloc(sizeof(codes));
    area *areas = (area*)malloc(sizeof(area)*AREAS);
    FILE *fptr = fopen(file, "r");
    int k = 0;
    char* lineptr = malloc(sizeof(char)*BUFFER);
    size_t n = BUFFER;
    while((k < AREAS) && (getline(&lineptr, &n, fptr) > 0)) {
        char *copy = (char*)malloc(sizeof(char)*n);
        strcpy(copy, lineptr);
        if (n != BUFFER) {
            n = BUFFER;
        }
        // divide the copy into three strings
        area a;
        char *zip = strtok(copy, ",");
        a.zip = atoi(zip)*100 + atoi(zip+3);
        a.name = strtok(NULL, ",");
        a.pop = atoi(strtok(NULL, ","));
        // update the array of areas
        areas[k++] = a;
    } 
    fclose(fptr);

    postnr->areas = areas;
    postnr->n = k;
    return postnr;
}

int linear_search(codes* postnr, int zip) {
    for(int i = 0; i < postnr->n; i++) {
        area a = postnr->areas[i];
        if (a.zip == zip) return 1;
    }
    return 0;
}

int binary_search(codes* postnr, int zip) {
    int length = postnr->n;
    int first = 0;
    int last = length - 1;
    while (1) {
        int index = (first + last) / 2;
        area a = postnr->areas[index];
        if (a.zip == zip) {
            return 1;
        }
        if (a.zip < zip && index < last) {
            first = index + 1;
            continue;
        }
        if (a.zip > zip && index > first) {
            last = index;
            continue;
        }
        break;
    }
    return 0;
}


void bench(codes* c, int postnummer, int tries, int repeat) {
    struct timespec t_start, t_stop;
        long minLinear = LONG_MAX;
        long minBinary = LONG_MAX;
        for (int k = 0; k < tries; k++) {
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            for (int i = 0; i < repeat; i++) {
                linear_search(c, postnummer);
            }
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < minLinear) minLinear = wall;
        }
        for (int k = 0; k < tries; k++) {
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            for (int i = 0; i < repeat; i++) {
                binary_search(c, postnummer);
            }
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < minBinary) minBinary = wall;
        }
        printf("%d\t%0.5f\t%0.5f\n", postnummer, (double) minLinear / repeat / 1000.0, (double) minBinary / repeat / 1000.0);

}

int main() {
    codes* c = read_postcodes("./int_zip/postnummer.csv");

    bench(c, 11115, 20, 20000);
    bench(c, 98499, 20, 20000);
    return 0;
}