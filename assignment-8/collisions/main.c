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

void collisions(codes *postnr, int mod) {
    int mx = 20;
    int data[mod];
    int cols[mx];
    for(int i = 0; i < mod; i++) {
        data[i] = 0;
    }
    for(int i = 0; i < mx; i++) {
        cols[i] = 0;
    }
    for (int i = 0; i < postnr->n; i++) {
        int index = (postnr->areas[i].zip)%mod;
        data[index]++;
    }
    int sum = 0;
    for(int i = 0; i < mod; i++) {
        sum += data[i];
        if (data[i] < mx)
        cols[data[i]]++;
    }
    printf("%d (%d) : ", mod, sum);
    for (int i = 1; i < mx; i++) {
        printf("%6d ",cols[i]);
    }
    printf("\n");
}

void bench(codes* c) {
    collisions(c, 10000);
    collisions(c, 20000);
    collisions(c, 13513);
    collisions(c, 13600);
    collisions(c, 14000);
}

int main() {
    codes* c = read_postcodes("./int_zip/postnummer.csv");
    bench(c);
    return 0;
}