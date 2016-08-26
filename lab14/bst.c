#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "mylib.h"

struct bst_node {
    char *key;
    bst left;
    bst right;
}

bst bst_delete(bst b, char *str){

}

bst bst_free(bst b){

}

void bst_inorder(bst b, void f(char *str)){
    //if b is NULL then return /* stopping case */
    //inorder traverse the left subtree
    //apply f to b->key
    //inorder traverse the right subtree
}

bst bst_insert(bst b, char *str){

}

bst bst_new(){

}

void bst_preorder(bst b, void f(char *str)){
    //if b is NULL then return /* stopping case */
    //apply f to b->key
    //preorder traverse the left subtree
    int i;

    
    //preorder traverse the right subtree
}

int bst_search(bst b, char *str){

}

