#include <stdlib.h>
#include <wchar.h>

typedef struct city {
    wchar_t* name;
    struct connection** connections;
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

struct path {
    city* city;
    city* previous_stop;
    int distance;
} typedef path;

struct priority_queue {
    path** paths;
    int size;
    int capacity;
} typedef priority_queue;

struct dynamic_array {
    city** array;
    int size;
    int capacity;
} typedef dynamic_array;

priority_queue* create_queue();
path* create_path(city* from, city* to, int distance);

void swap(path** a, path** b);

void enqueue(priority_queue* queue, path* p);

path* dequeue(priority_queue* queue);

int is_empty(priority_queue* queue);

dynamic_array* create_array();
void add(dynamic_array* array, city* c);
int contains(dynamic_array* array, city* c);