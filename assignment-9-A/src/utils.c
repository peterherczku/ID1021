//
// Created by molna on 2024. 10. 25..
//
#include "utils.h"


priority_queue* create_queue() {
    priority_queue* queue = (priority_queue*)malloc(sizeof(priority_queue));
    queue->paths = (path**)malloc(sizeof(path*) * 2);
    queue->capacity = 2;
    queue->size = 0;
    return queue;
}

path* create_path(city* from, city* to, int distance) {
    path* p = (path*)malloc(sizeof(path));
    p->city = to;
    p->previous_stop = from;
    p->distance = distance;
    return p;
}

void swap(path** a, path** b) {
    path* temp = *a;
    *a = *b;
    *b = temp;
}

void enqueue(priority_queue* queue, path* p) {
    if(queue->size == queue->capacity) {
        path** new_array = (path**)malloc(sizeof(path*) * queue->capacity * 2);
        for(int i = 0; i < queue->size; i++) {
            new_array[i] = queue->paths[i];
        }
        free(queue->paths);
        queue->paths = new_array;
        queue->capacity = queue->capacity * 2;
    }

    int index = queue->size;
    queue->paths[index] = p;

    while(index != 0 && queue->paths[index]->distance < queue->paths[(index -1)/2]->distance) {
        swap(&queue->paths[index], &queue->paths[(index - 1)/2]);
        index = (index - 1) / 2;
    }

    queue->size++;
}

path* dequeue(priority_queue* queue) {
    if(queue->size == 0) return NULL;

    path* p = queue->paths[0];
    queue->paths[0] = queue->paths[queue->size - 1];
    queue->size--;

    int i = 0;
    while (2 * i + 1 < queue->size) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < queue->size && queue->paths[left]->distance < queue->paths[smallest]->distance)
            smallest = left;

        if (right < queue->size && queue->paths[right]->distance < queue->paths[smallest]->distance)
            smallest = right;

        if (smallest != i) {
            swap(&queue->paths[i], &queue->paths[smallest]);
            i = smallest;
        } else {
            break;
        }
    }

    return p;
}

int is_empty(priority_queue* queue) {
    return queue->size == 0;
}

dynamic_array* create_array() {
    dynamic_array* arr = (dynamic_array*)malloc(sizeof(dynamic_array));
    arr->size = 0;
    arr->capacity = 2;
    arr->array = (city**) malloc(sizeof(city*)*2);
    return arr;
}
void add(dynamic_array* array, city* i) {
    if (array->size == array->capacity) {
        city** new_array = (city**)malloc(sizeof(city*) * array->capacity * 2);
        for(int i = 0; i < array->size; i++) {
            new_array[i] = array->array[i];
        }
        free(array->array);
        array->array = new_array;
        array->capacity = array->capacity * 2;
    }
    array->array[array->size] = i;
    array->size++;
}
int contains(dynamic_array* array, city* data) {
    for (int i = 0; i < array->size; i++) {
        if (array->array[i] == data) {
            return 1;
        }
    }
    return 0;
}