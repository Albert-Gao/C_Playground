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

rbt rbt_delete(rbt b, char *str){
    if (b==NULL){
        /*Deleting a not-exist key should have no effect. */
        return b;
    } else if (strcmp(str, b->key) < 0){
        /*If key is smaller, delete it from the left subtree.*/
        b->left = rbt_delete(b->left, str);
    } else if (strcmp(str, b->key) > 0){
        /*If key is larger, delete it from the right subtree.*/
        b->right = rbt_delete(b->right, str);
    } else {
        /*If the key match the current node, remove the node.*/
        if (b->left == NULL && b->right == NULL){
            /*if it is a leaf*/
            free(b->key);
            free(b);
            b = NULL;
        } else if (b->left != NULL && b->right == NULL){
            /*if only one child(left), move left up*/
            rbt temp = b;
            b = b->left;
            free(temp->key);
            free(temp);
        } else if (b->left == NULL && b->right != NULL){
            /*if only one child(right), move right up*/
            rbt temp = b;
            b = b->right;
            free(temp->key);
            free(temp);
        } else {
            /*if node has two children, copy the min_right then move right up*/
            rbt min_right = b->right;
            while(min_right->left!=NULL){
                min_right = min_right->left;
            }
            strcpy(b->key, min_right->key);
            b->right = rbt_delete(b->right, min_right->key);
        }
    }
    return b;
}

rbt rbt_free(rbt b){
    free( b->key );
    if (b->left != NULL) rbt_free(b->left);
    if (b->right != NULL) rbt_free(b->right);
    free(b);
    return b;
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
    return b;
}

rbt rbt_new(){
    return NULL;
}

void rbt_preorder(rbt b, void f(char *str)){
    if (b == NULL) return;
    f(b->key);
    rbt_preorder(b->left, f);
    rbt_preorder(b->right, f);
}

void rbt_inorder(rbt b, void f(char *str)){
    if (b == NULL) return;
    rbt_inorder(b->left, f);
    f(b->key);
    rbt_inorder(b->right, f);
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
