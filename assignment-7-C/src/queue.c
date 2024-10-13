#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "queue.h"

void free_queue(queue *q) {
    queue_node *nxt = q->first;
    while (nxt != NULL) {
        queue_node *tmp = nxt->next;
        free(nxt);
        nxt = tmp;
    }
    free(q);
}

queue *create_queue() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->first = NULL;
    return q;
}

int empty(queue *q) {
    return (q->first == NULL);
}
void enqueue(queue* q, tree_node* v) {
    queue_node *nd = (queue_node*)malloc(sizeof(queue_node));
    nd->value = v;
    nd->next = NULL;
    queue_node *prv = NULL;
    queue_node *nxt = q->first;
    while (nxt != NULL) {
        prv = nxt;
        nxt = nxt->next;
    }
    if (prv != NULL) {
        prv->next = nd;
    } else {
        q->first = nd;
    }
}
tree_node* dequeue(queue *q) {
    tree_node* res = NULL;
    if (q->first != NULL) {
        res = q->first->value;
        queue_node* nd = q->first;
        q->first = nd->next;
        free(nd);
    }
    return res;
}