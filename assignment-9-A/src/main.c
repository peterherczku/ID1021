#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "utils.h"
#include <time.h>
#include <sys/timeb.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

int MOD = 1000;
int BUFFER = 1024;

int hash(wchar_t *name, int mod) {
    int h = 0;
    int i = 0;
    unsigned char c = 0;
    while ((c = name[i]) != 0) {
        h = (h * 31 + c) % mod;
        i++;
    }
    return h;
}

city* lookup(city** cities, wchar_t* name) {
    int index = hash(name, MOD);
    while(1) {
        if (cities[index] == NULL) break;
        if (wcscmp(name, cities[index]->name) == 0) {
            return cities[index];
        }
        index++;
    }

    wchar_t* newName = (wchar_t*) malloc(sizeof(wchar_t)* (wcslen(name) + 1));
    wcscpy(newName, name);
    city* c = (city*) malloc(sizeof(city));
    c->name = newName;
    c->connections = (connection**) malloc(sizeof(connection*));
    c->connections_size = 0;
    cities[index] = c;
    return c;
}

void connect(city* src, city* dst, int dist) {
    connection* conn = (connection*) malloc(sizeof(connection));
    conn->minutes = dist;
    conn->destination = dst;
    src->connections[src->connections_size] = conn;
    src->connections_size++;
    connection** newArray = (connection**) malloc(sizeof (connection*)*src->connections_size);
    for(int i = 0; i < src->connections_size; i++) {
        newArray[i] = src->connections[i];
    }
    src->connections = newArray;
}

map *graph(char *file) {
    city** cities = (city**)malloc(sizeof(city*) * MOD);
    map *trains = (map*)malloc(sizeof(map));
    trains->cities = cities;
    // Open a file in read mode
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL)
        return NULL;

    wchar_t copy[BUFFER];
    while(fgetws(copy, BUFFER, fptr) != NULL) {
        wchar_t* cpy;

        // divide the copy into the three parts

        city *src = lookup(cities,wcstok(copy, L",", &cpy));
        city *dst = lookup(cities, wcstok(NULL, L",", &cpy));
        unsigned int dist = wcstol(wcstok(NULL, L",", &cpy), NULL, 10);
        //printf("%d", dist);
        // add the connection
        connect(src, dst, dist);
        connect(dst, src, dist);
    }
    fclose(fptr);
    return trains;
}

int dijkstra(city* from, city* to, int* doneSize) {
    priority_queue *queue = create_queue();
    enqueue(queue, create_path(NULL, from, 0));

    dynamic_array* arr = create_array();

    while (!is_empty(queue)) {
        path* p = dequeue(queue);
        city* c = p->city;

        if(c == to) return p->distance;
        if(!contains(arr, c)) {
            add(arr, c);
            *(doneSize)+=1;

            for(int i = 0; i < c->connections_size; i++) {
                connection* conn = c->connections[i];
                if(contains(arr, conn->destination)) continue;
                int res = p->distance + conn->minutes;
                path* newp = create_path(c, conn->destination, res);
                enqueue(queue, newp);
            }
        }
    }

    return -1;
}


int main(int argc, char*argv[]) {
    setlocale(LC_ALL,"en_US.UTF-8");
    map *trains = graph("europe.csv");
    if(argc < 3) {
        printf("usage: %s <from> <to> <limit>\n", argv[0]);
        exit(1);
    }
    wchar_t *arg1 = (wchar_t *)malloc((mbstowcs(NULL, argv[1], 0) + 1) * sizeof(wchar_t));
    wchar_t *arg2 = (wchar_t *)malloc((mbstowcs(NULL, argv[2], 0) + 1) * sizeof(wchar_t));
    mbstowcs(arg1, argv[1], (mbstowcs(NULL, argv[1], 0) + 1));
    mbstowcs(arg2, argv[2], (mbstowcs(NULL, argv[2], 0) + 1));

    city *from = lookup(trains->cities, arg1);
    city *to = lookup(trains->cities, arg2);
    int doneSize = 0;
    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    int s = dijkstra(from, to, &doneSize);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    if (s > 0)
        printf("From: %S to %S, shortest path %d found in %.2fus\tdone: %d\n", arg1, arg2, s, ((double)wall)/1000, doneSize);
    else
        printf("From: %S to %S, no path found\n", arg1, arg2);
}