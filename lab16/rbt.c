#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbt.h"
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

/*
#define MAX(x, y) ((x > y) ? x : y)
int a = MAX(4, 3);
*/

struct rbt_node {
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
};

rbt right_rotate(rbt r){
    rbt temp = r;
    r = r->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}

rbt left_rotate(rbt r) {
    rbt temp = r;
    r = r->right;
    temp->right = r->left;
    r->left = temp;
    return r;
}

rbt rbt_free(rbt b){
    free( b->key );
    if (b->left != NULL) rbt_free(b->left);
    if (b->right != NULL) rbt_free(b->right);
    free(b);
    return b;
}

rbt rbt_fix(rbt r){
    if ( IS_RED(r->left) && IS_RED(r->left->left) ) {
        if (IS_RED(r->right)){
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else if(IS_BLACK(r->right)) {
            r = right_rotate(r);
            r->colour = BLACK;
            r->right->colour = RED;
        }
    } else if ( IS_RED(r->left) && IS_RED(r->left->right) ){
        if (IS_RED(r->right)){
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else if(IS_BLACK(r->right)) {
            r->left = left_rotate(r->left);
            r = right_rotate(r);
            r->colour = BLACK;
            r->right->colour = RED;
        }
    } else if ( IS_RED(r->right) && IS_RED(r->right->left) ){
        if (IS_RED(r->left)){
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else if(IS_BLACK(r->left)) {
            r->right = right_rotate(r->right);
            r  = left_rotate(r);
            r->colour = BLACK;
            r->left->colour = RED;
            r->right->colour = RED;
        }
    } else if ( IS_RED(r->right) && IS_RED(r->right->right) ){
        if (IS_RED(r->left)){
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK; 
        } else if(IS_BLACK(r->left)) {
            r = left_rotate(r);
            r->colour = BLACK;
            r->left->colour = RED;
            r->right->colour = RED; 
        }
    }
    return r;
}

rbt rbt_insert(rbt b, char *str){
    /* create a new tree */
    if (b == NULL){
        b = emalloc(sizeof *b);
        b->left = NULL;
        b->right = NULL;
        b->colour = RED;
        b->key = emalloc((strlen(str)+1)*sizeof str[0]);
        strcpy(b->key,str);
    } else if (strcmp(b->key,str) == 0){
        /* we already have this value; */
        return NULL;
    } else if (strcmp(str,b->key) > 0){
        /*the new value is greater than the old*/
        b->right = rbt_insert(b->right,str);
    } else if (strcmp(str,b->key) < 0){
        /*the new value is less then the old*/
        b->left = rbt_insert(b->left,str);
    }
    return rbt_fix(b);
}

rbt rbt_new(){
    return NULL;
}


void rbt_preorder(rbt b){
    if (b == NULL) return;    
    printf("%-7s: %s\n",(IS_RED(b))?"red:":"black:",b->key);
    rbt_preorder(b->left);
    rbt_preorder(b->right);
}



void rbt_inorder(rbt b){
    if (b == NULL) return;
    rbt_preorder(b->left);
    printf("%-7s: %s\n",(IS_RED(b))?"red:":"black:",b->key);
    rbt_preorder(b->right);
}

int rbt_search(rbt b, char *str){
    if (b == NULL){
        return 0;
    } else if (strcmp(str, b->key) == 0){
        return 1;
    } else if (strcmp(str, b->key) > 0){
        return rbt_search(b->right,str);
    } else if (strcmp(str, b->key) < 0){
        return rbt_search(b->left,str);
    }
    return 0;
}
