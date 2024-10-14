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
    char *zip;
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
        a.zip = strtok(copy, ",");
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

int linear_search(codes* postnr, char* zip) {
    for(int i = 0; i < postnr->n; i++) {
        area a = postnr->areas[i];
        if (strcmp(a.zip, zip) == 0) return 1;
    }
    return 0;
}


void bench(codes* c, char* postnummer, int tries, int repeat) {
    struct timespec t_start, t_stop;
        long min = LONG_MAX;
        for (int k = 0; k < tries; k++) {
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            for (int i = 0; i < repeat; i++) {
                linear_search(c, postnummer);
            }
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < min) min = wall;
        }
        printf("%s\t%0.5f\n", postnummer, (double) min / repeat / 1000.0);

}

int main() {
    codes* c = read_postcodes("./string_zip/postnummer.csv");
    
    bench(c, "111 15", 20, 10000);
    bench(c, "984 99", 20, 10000);
    return 0;
}