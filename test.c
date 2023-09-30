#include "skiplist.h"
#include <stdio.h>
#include <time.h>
#include <limits.h>

#define NUM_NODES 15
#define MAX_KEY 500
#define MAX_VALUE 200

int main(){
    int height;
    int i;
    skiplist* slist = skiplist_create();
    lnode* tmp;

    srand(time(NULL));

    for(i = 0; i < NUM_NODES; i++){
        /* avoid creating two nodes with the same key */
        tmp = lnode_create(rand() % MAX_KEY, rand() % MAX_VALUE);
        while(skiplist_search(slist, tmp->key) != NULL){
            free(tmp);
            tmp = lnode_create(rand() % MAX_KEY, rand() % MAX_VALUE);
        }
        skiplist_insert(slist, tmp);
    }
    skiplist_print(slist); 

    /* Uncomment the following code for a test with manual insertions and deletions */
    /*
    lnode* n1, *n2, *n3, *n4, *n5;
    n1 = lnode_create(rand() % MAX_KEY, rand() % MAX_VALUE);
    n2 = lnode_create(rand() % MAX_KEY, rand() % MAX_VALUE);
    n3 = lnode_create(rand() % MAX_KEY, rand() % MAX_VALUE);
    n4 = lnode_create(rand() % MAX_KEY, rand() % MAX_VALUE);
    n5 = lnode_create(rand() % MAX_KEY, rand() % MAX_VALUE);
    skiplist_insert(slist, n1);
    skiplist_insert(slist, n2);
    skiplist_insert(slist, n3);
    skiplist_insert(slist, n4);
    skiplist_insert(slist, n5);
    skiplist_print(slist);
    printf("----------------\n");
    skiplist_delete(slist, n3);
    skiplist_delete(slist, n2);
    skiplist_print(slist);
    */

    skiplist_free(slist);
}