#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <sys/timeb.h>
#include "stack.h"

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

int main() {
    stack* st = new_stack();
    tree* tr = create_tree(100);
    print_tree_new(tr);
    return 0;
}