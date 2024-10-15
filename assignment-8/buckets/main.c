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

typedef struct bucket {
    int size;
    int max;
    area **areas;
} bucket;

typedef struct codes {
    bucket* buckets;
    int size;
} codes;

codes *read_postcodes(char *file, int modulo) {
    codes *hashmap = (codes*)malloc(sizeof(codes));
    hashmap->size = modulo;
    bucket *buckets = (bucket*)malloc(sizeof(bucket)*hashmap->size);
    for(int i = 0; i < modulo; i++) {
        buckets[i].areas = (area**)malloc(sizeof(area*));
        buckets[i].size = 0;
        buckets[i].max = 1;
    }
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
        area* a = (area*)malloc(sizeof(area));
        char *zip = strtok(copy, ",");
        a->zip = atoi(zip)*100 + atoi(zip+3);
        a->name = strtok(NULL, ",");
        a->pop = atoi(strtok(NULL, ","));
        // update the array of areas
        int key = a->zip % modulo;
        bucket b = buckets[key];
        if(b.max == b.size) {
            area** areas = b.areas;
            int newMax = b.max*2;
            area** newAreas = (area**)malloc(sizeof(area*)*newMax);
            for (int i = 0; i < b.size; i++) {
                newAreas[i] = areas[i];
            }
            newAreas[b.size] = a;
            b.areas = newAreas;
            b.max = newMax;
            b.size++;
        } else {
            b.areas[b.size++] = a;
        }
        buckets[key] = b;
        k++;
    }
    fclose(fptr);

    hashmap->buckets = buckets;
    hashmap->size = modulo;
    return hashmap;
}

int lookup(codes* c, int postnummer) {
    bucket b = c->buckets[postnummer % c->size];
    for(int i = 0; i < b.size; i++) {
        if(b.areas[i]->zip == postnummer) return 1;
    }
    return 0;
}




void bench(codes* c, int postnummer, int tries, int repeat) {
    struct timespec t_start, t_stop;
        long min = LONG_MAX;
        for (int k = 0; k < tries; k++) {
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            for (int i = 0; i < repeat; i++) {
                lookup(c, postnummer);
            }
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < min) min = wall;
        }
        printf("%d\t%0.5f\n", postnummer, (double) min / repeat / 1000.0);

}

int main() {
    codes* c = read_postcodes("./postnummer.csv", 13600);
    bench(c, 11115, 20, 20000);
    bench(c, 98499, 20, 20000);
    return 0;
}