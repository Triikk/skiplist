#include <limits.h>
#include "skiplist.h"
#include <stdlib.h>
#include <stdio.h>


/* Generates a random height for the node. */
static int rand_height(){
    int level = 1;
    while(rand() < RAND_MAX / 2 && level < SKIPLIST_HEIGHT){
        level++;
    };
    return level;
}


lnode* lnode_create(int key, int value){
    lnode* node = (lnode*)malloc(sizeof(*node));
    if(node == NULL){
        return NULL;
    }
    node->key = key;
    node->value = value;
    node->height = -1;
    node->next = NULL;
    return node;
}

void skiplist_insert(skiplist* slist, lnode* node){
    int h,i;
    lnode* tmp;

    tmp = slist->list;
    i = slist->height;
    h = rand_height();
    node->height = h;
    node->next = (lnode**)malloc(h * sizeof(lnode*));

    /* go down until height h */
    for(i--; i >= h; i--){
        while(tmp->next[i] != NULL && tmp->next[i]->key < node->key){
            tmp = tmp->next[i];
        }  
    }

    for(h--; h >= 0; h--){
        while(tmp->next[h] != NULL && tmp->next[h]->key < node->key){
            tmp = tmp->next[h];
        }
        node->next[h] = tmp->next[h];
        tmp->next[h] = node;
    }
}

void skiplist_delete(skiplist* slist, lnode* node){
    int h = slist->height;
    lnode* tmp = slist->list;
    for(h--; h >= 0; h--){
        while(tmp->next[h] != NULL && tmp->next[h]->key < node->key){
            tmp = tmp->next[h];
        }
        if(tmp->next[h] == node){
            tmp->next[h]= node->next[h];
        }
    }
    free(node->next);
    free(node);
}

lnode* skiplist_search(skiplist* slist, int key){
    lnode* tmp = slist->list;
    int h;
    for(h = slist->height - 1; h >= 0; h--){
        while(tmp->next[h] != NULL && tmp->next[h]->key <= key){
            tmp = tmp->next[h];
        }
        if(tmp->key == key){
            return tmp;
        } 
    } 
    return NULL; 
}

skiplist* skiplist_create(){
    skiplist* slist = (skiplist*)malloc(sizeof(*slist));
    int i;
    lnode* head;

    if(slist == NULL){
        return NULL;
    }

    slist->height = SKIPLIST_HEIGHT;

    /* head is used as a sentinel */
    head = lnode_create(INT_MIN, 0); 
    head->next = (lnode**)malloc(SKIPLIST_HEIGHT * sizeof(lnode*));

    for(i = 0; i < SKIPLIST_HEIGHT; i++){
        head->next[i] = NULL;
    }

    slist->list = head;

    return slist;
}

void skiplist_print(skiplist* slist){
    int h = slist->height;
    lnode* tmp;
    for(h--; h >= 0; h--){
        tmp = slist->list;
        while(tmp != NULL){
            printf("(%d,%d)->", tmp->key, tmp->value);
            tmp = tmp->next[h];
        }
        printf("NULL\n");
    }
}

void skiplist_free(skiplist* slist){
    lnode* curr = slist->list;
    lnode* tmp;
    while(curr->next[0] != NULL){
        curr = curr->next[0];
    }
    curr = slist->list;

    while(curr != NULL){
        tmp = curr;
        curr = curr->next[0];
        free(tmp->next);
        free(tmp);
    }
    free(slist);
}