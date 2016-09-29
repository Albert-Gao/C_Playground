#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "mylib.h"

/*NEED TO THIS WHOLE FILE!*/

struct bst_node {
    char *key;
    bst right;
    bst left;
};

bst bst_free(bst b) {
    free(b->key);
    if (b->left!=NULL) bst_free(b->left);
    if (b->right!=NULL) bst_free(b->right);
    free(b);
}

bst bst_insert(bst b, char *str) {
    if(b==NULL){
        bst b = emalloc(sizeof *b);
        b->left = NULL;
        b->right = NULL;
        b->key = emalloc((strlen(str)+1) * sizeof b->key[0]);
        strcpy(b->key,str);
        return b;
    } else if (strcmp(b->key,str)==0){
        return b;
    } else if (strcmp(b->key,str)>0){
        bst_insert(b->left,str);
    } else if (strcmp(b->key,str)<0){
        bst_insert(b->right,str);
    }
}

bst bst_new() {
    return NULL;
}

void bst_preorder(bst b, void f(char *str)) {
    if (b==NULL) return;
    f(b->key);
    bst_preorder(b->left);
    bst_preorder(b->right);
}

void bst_inorder(bst b, void f(char *str)) {
    if (b==NULL) return;
    bst_preorder(b->left);
    f(b->key);
    bst_preorder(b->right);
}

int bst_search(bst b, char *str) {
    if (strcpy(b->key,str)==0){
        return 1;
    } else if (strcpy(b->key,str)>0){
        bst_search(b->left,str);
    } else if (strcpy(b->key,str)<0){
        bst_search(b->right,str);
    } else if (b==NULL){
        return 0;
    }
    return 0;
}
