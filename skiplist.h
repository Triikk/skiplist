#include <stdlib.h>

#define SKIPLIST_HEIGHT 10

typedef struct lnode {
    int key; /* identifier of the node (must be unique) */
    int value;
    int height; 
    struct lnode** next; /* x->next[i] is a pointer to x->next at height i */
} lnode;

typedef struct skiplist {
    int height;         /* maximum height */
    struct lnode* list; /* pointer to the head of the list */ 
} skiplist;


/* Creates a new node.
Returns the pointer to the node if the creation is successful, NULL otherwise. */
lnode* lnode_create(int key, int value);


/* Creates a list.
Returns the pointer to the skiplist if the creation is successful, NULL otherwise. */
skiplist* skiplist_create();

/* Insertion of a node */
void skiplist_insert(skiplist* slist, lnode* node);

/* Deletion of a node */
void skiplist_delete(skiplist* slist, lnode* node);

/* Search for a node in the list.
Returns a pointer to the node if found, NULL otherwise. */
lnode* skiplist_search(skiplist* slist, int key);

/* Prints a string representation of the list */
void skiplist_print(skiplist* slist);

/* Free the memory used by the list */
void skiplist_free(skiplist* slist);