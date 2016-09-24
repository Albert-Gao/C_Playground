#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "mylib.h"

struct bst_node {
    char *key;
    bst left;
    bst right;
};

bst bst_free(bst b){
    free( b->key );
    if (b->left != NULL) bst_free(b->left);
    if (b->right != NULL) bst_free(b->right);
    free(b);
    return b;
}

bst bst_insert(bst b, char *str){
    /* create a new tree */
    if (b == NULL){
        b = emalloc(sizeof *b);
        b->left = NULL;
        b->right = NULL;
        b->key = emalloc((strlen(str)+1)*sizeof str[0]);
        strcpy(b->key,str);
    } else if (strcmp(b->key,str) == 0){
        /* we already have this value; */
        return NULL;
    } else if (strcmp(str,b->key) > 0){
        /*the new value is greater than the old*/
        b->right = bst_insert(b->right,str);
    } else if (strcmp(str,b->key) < 0){
        /*the new value is less then the old*/
        b->left = bst_insert(b->left,str);
    }
    return b;
}

bst bst_new(){
    return NULL;
}

void bst_preorder(bst b, void f(char *str)){
    if (b == NULL) return;
    f(b->key);
    bst_preorder(b->left, f);
    bst_preorder(b->right, f);
}

void bst_inorder(bst b, void f(char *str)){
    if (b == NULL) return;
    bst_inorder(b->left, f);
    f(b->key);
    bst_inorder(b->right, f);
}

int bst_search(bst b, char *str){
    if (b == NULL){
        return 0;
    } else if (strcmp(str, b->key) == 0){
        return 1;
    } else if (strcmp(str, b->key) > 0){
        return bst_search(b->right,str);
    } else if (strcmp(str, b->key) < 0){
        return bst_search(b->left,str);
    }
    return 0;
}