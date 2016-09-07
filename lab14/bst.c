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

bst bst_delete(bst b, char *str){
    if (b==NULL){
        /*Deleting a not-exist key should have no effect. */
    } else if (strcmp(str, b->key) < 0){
        /*If the key is smaller, delete the key from the left subtree.*/
        b->left = bst_delete(b->left, str);
    } else if (strcmp(str, b->key) > 0){
        /*If the key is larger, delete the key from the right subtree.*/
        b->right = bst_delete(b->right, str);
    } else {
        /*If the key match the current node, splice out the node.*/
        if (b->left == NULL && b->right == NULL){
            /*if it is a leaf*/
            free(b->key);
            bst_free(b);
            b = NULL;
        } else if (b->left != NULL && b->right == NULL){
            /*if only one child(left)*/
            bst temp = b->left;
            free(b->key);
            free(b);
            b = temp;

        } else if (b->left == NULL && b->right != NULL){
            /*if only one child(right)*/
            bst temp = b->right;
            free(b->key);
            free(b);
            b = temp;
        } else {
            /*if node has two children*/
            bst temp = b->right;
            while(temp->left!=NULL){
                temp = temp->left;
            }
            strcpy(b->key, temp->key);
            temp = bst_delete(temp, temp->key);
        }
    }
    return b;
}

bst bst_free(bst b){
    free(b->key);
    if (b->left!=NULL){
        bst_free(b->left);
    }
    if (b->right!=NULL) {
        bst_free(b->right);
    }
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
    } else if (strcmp(b->key,str)==0){
        /* we already have this value; */
        return NULL;
    } else if (strcmp(str,b->key)>0){
        /*the new value is greater than the old*/
        b->right = bst_insert(b->right,str);
    } else if (strcmp(str,b->key)<0){
        /*the new value is less then the old*/
        b->left = bst_insert(b->left,str);
    }
    return b;
}

bst bst_new(){
    return NULL;
}

void bst_preorder(bst b, void f(char *str)){
    if (b == NULL){
        return;
    }

    f(b->key);
    bst_preorder(b->left, f);
    bst_preorder(b->right, f);
}

void bst_inorder(bst b, void f(char *str)){
    if (b == NULL){
        return;
    }

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
