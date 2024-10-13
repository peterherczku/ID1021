#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <sys/timeb.h>
#include "stack.h"

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

tree* construct_tree() {
        tree *tr = (tree*)malloc(sizeof(tree));
        tr->root = NULL;
        return tr;
}

node *construct_node(int val) {
    node *nd = (node*)malloc(sizeof(node));
    nd->value = val;
    nd->left = NULL;
    nd->right = NULL;
    return nd;
}
void free_node(node *nd) {
    if (nd != NULL) {
        free_node(nd->right);
        free_node(nd->left);
        free(nd);
    }
}

void free_tree(tree *tr) {
    if (tr->root != NULL) {
        free_node(tr->root);
    }
    free(tr);
}

void add_node(node* nd, int value) {
    if (nd->value == value) return;
    if (value < nd->value) {
        if (nd->left == NULL) {
            nd->left = construct_node(value);
        } else {
            add_node(nd->left, value);
        }
    } else {
        if (nd->right == NULL) {
            nd->right = construct_node(value);
        } else {
            add_node(nd->right, value);
        }
    }
}

void add_recursive(tree *tr, int value) {
    if(tr->root == NULL) tr->root = construct_node(value);
    else add_node(tr->root, value);
}

void add(tree *tr, int value) {
    if(tr->root == NULL) {
        tr->root = construct_node(value);
        return;
    }
    node *curr = tr->root;
    while(1) {
        if(curr->value == value) break;
        if(value < curr->value) {
            if (curr->left == NULL) {
                curr->left = construct_node(value);
                break;
            }

            curr = curr->left;
        }
        if(value > curr->value) {
            if (curr->right == NULL) {
                curr->right = construct_node(value);
                break;
            }

            curr = curr->right;
        }
    }
}

bool lookup(tree *tr, int value) {
    if(tr->root == NULL) return false;
    node *curr = tr->root;
    while(1) {
        if (curr->value == value) return true;
        if (value < curr->value && curr->left != NULL) {
            curr = curr->left;
        } else if(value > curr->value && curr->right != NULL) {
            curr = curr->right;
        } else {
            return false;
        }
    }
}

tree* create_tree(int size) {
    tree* tr = construct_tree();
    for (int i = 1; i < size + 1; i++) {
        add(tr, i);
    }
    return tr;
}

int* random_values(int size) {
    int* arr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand()%(size);
    }
    return arr;
}

void print(node *nd) {
    if (nd != NULL) {
        print(nd->left);
        printf("%d ", nd->value);
        print(nd->right);
    }
}

void print_tree_new(tree *tr) {
    stack *stk = new_stack();
    node *cur = tr->root;
    
    while(cur->left != NULL ) {
        push(stk, cur);
        cur = cur->left;
    }

    while(cur != NULL) {
        printf("%d ", cur->value);

        if(cur->right != NULL) {
            cur = cur->right;
            while(cur->left != NULL) {
                push(stk, cur);
                cur = cur->left;
            }
        } else {
            cur = pop(stk);
        }
    }
}

void print_tree(tree *tr) {
      if (tr->root != NULL)
        print(tr->root);
      printf("\n");
}

void bench(int tries, int repeat, int max, int steps) {
    struct timespec t_start, t_stop;
    for(int i = 1; i <= (max / steps); i++) {
        int size = i * steps;
        long min = LONG_MAX;
        for (int k = 0; k < tries; k++) {
            tree* tr = create_tree(size);
            int* randomValues = random_values(size);
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            for (int i = 0; i < repeat; i++) {
                lookup(tr, randomValues[i]);
            }
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            if (wall < min) min = wall;
            free_tree(tr);
        }
        printf("%d\t%0.5f\n", size, (double) min / repeat);
    }
}

int main() {
    bench(20, 100, 25000, 1000);
    return 0;
}