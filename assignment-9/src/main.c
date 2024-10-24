#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

int MOD = 500;
int BUFFER = 1024;

typedef struct city {
    wchar_t* name;
    struct connection* connections;
    int connections_size;
} city;

struct connection {
    city* destination;
    int minutes;
} typedef connection;

struct map {
    city** cities;
    int modulo;
    int size;
} typedef map;

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
    wcscat(newName, name);
    city* c = (city*) malloc(sizeof(city));
    c->name = newName;
    c->connections = (connection*) malloc(sizeof(connection));
    c->connections_size = 0;
    cities[index] = c;
    return c;
}

void connect(city* src, city* dst, int dist) {
    connection* conn = (connection*) malloc(sizeof(connection));
    conn->minutes = dist;
    conn->destination = dst;
    src->connections[src->connections_size] = *conn;
    src->connections_size++;
    connection* newArray = (connection*) malloc(sizeof (connection)*src->connections_size);
    for(int i = 0; i < src->connections_size; i++) {
        newArray[i] = src->connections[i];
    }
    src->connections = newArray;
}

map *graph(char *file) {
    setlocale(LC_ALL,"en_US.UTF-8");
    city** cities = (city**)malloc(sizeof(city*) * MOD);
    map *trains = (map*)malloc(sizeof(map));
    trains->cities = cities;
    // Open a file in read mode
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL)
        return NULL;

    wchar_t ws[BUFFER];
    while(fgetws(ws, BUFFER, fptr) != NULL) {
        wchar_t *copy = (wchar_t*) malloc(sizeof(wchar_t) * (wcslen(ws) + 1));
        wchar_t* cpy;
        wcscpy(copy, ws);

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

int main() {
    map* map = graph("trains.csv");
    city* city = lookup(map->cities, L"Stockholm");
    //printf("%d", city->connections_size);
    printf("from: %S, to: %S in minutes: %d\n", city->name, city->connections[1].destination->name, city->connections[1].minutes);
    //printf("%d\n", hash(L"Stockholm", MOD));
    //printf("%S\n", map->cities[158]->name);
    return 0;
}