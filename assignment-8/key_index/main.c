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

area **read_postcodes(char *file) {
    area **areas = (area**)malloc(sizeof(area*)*1000000);
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
        area *a = (area*)malloc(sizeof(area));
        char *zip = strtok(copy, ",");
        a->zip = atoi(zip)*100 + atoi(zip+3);
        a->name = strtok(NULL, ",");
        a->pop = atoi(strtok(NULL, ","));
        // update the array of areas
        areas[a->zip] = a;
        k++;
    } 
    fclose(fptr);

    return areas;
}

int lookup(area** area, int zip) {
    return area[zip] != NULL;
}


void bench(area** areas, int postnummer, int tries, int repeat) {
    struct timespec t_start, t_stop;
        long min = LONG_MAX;
        for (int k = 0; k < tries; k++) {
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            for (int i = 0; i < repeat; i++) {
                lookup(areas, postnummer);
            }
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < min) min = wall;
        }
        printf("%d\t%0.5f\n", postnummer, (double) min / repeat / 1000.0);

}

int main() {
    area** areas = read_postcodes("./int_zip/postnummer.csv");

    bench(areas, 11115, 20, 20000);
    bench(areas, 98499, 20, 20000);
    return 0;
}