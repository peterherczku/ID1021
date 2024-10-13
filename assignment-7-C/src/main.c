#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <sys/timeb.h>
#include "queue.h"

tree* construct_tree() {
        tree *tr = (tree*)malloc(sizeof(tree));
        tr->root = NULL;
        return tr;
}

tree_node* construct_node(int val) {
    tree_node *nd = (tree_node*)malloc(sizeof(tree_node));
    nd->value = val;
    nd->left = NULL;
    nd->right = NULL;
    return nd;
}
void free_node(tree_node *nd) {
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
    tree_node *curr = tr->root;
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

void bfs(tree* tr) {
    queue* q = create_queue();
    enqueue(q, tr->root);
    while (!empty(q)) {
        tree_node* curr = dequeue(q);
        if(curr == NULL) break;
        printf("%d ", curr->value);
        if(curr->left != NULL) enqueue(q, curr->left);
        if(curr->right != NULL) enqueue(q, curr->right);
    }
}

tree* create_tree(int size) {
    tree* tr = construct_tree();
    tree_node* root = construct_node(1);
    tree_node* two = construct_node(2);
    tree_node* three = construct_node(3);
    tree_node* four = construct_node(4);
    tree_node* five = construct_node(5);
    tree_node* six = construct_node(6);
    tree_node* seven = construct_node(7);
    tree_node* eight = construct_node(8);
    four->left = eight;
    two->left = four;
    two->right = five;
    three->left = six;
    three->right = seven;
    root->left = two;
    root->right = three;
    tr->root = root;
    return tr;
}

int main() {
    tree* tr = create_tree(1);
    bfs(tr);
    return 0;
}