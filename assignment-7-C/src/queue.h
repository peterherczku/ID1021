typedef struct tree_node {
    int value;
    struct tree_node* left;
    struct tree_node* right;
} tree_node;

typedef struct tree {
    tree_node *root;
} tree;


typedef struct queue_node {
    tree_node* value;
    struct queue_node *next;
} queue_node;


typedef struct queue {
    queue_node *first;
} queue;

void free_queue(queue *q);
queue *create_queue();
int empty(queue *q);
void enqueue(queue* q, tree_node* v);
tree_node* dequeue(queue *q);