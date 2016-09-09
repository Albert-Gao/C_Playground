#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "bst.h"

void print_key(char *s) {
    printf("%s ", s);
}

bst my_new_bst(){
    bst tree = bst_new();
    tree = bst_insert(tree,"D");
    tree = bst_insert(tree,"B");
    tree = bst_insert(tree,"F");
    tree = bst_insert(tree,"A");
    tree = bst_insert(tree,"C");
    tree = bst_insert(tree,"E");
    tree = bst_insert(tree,"G");
    return tree;
}

int main(void){
    bst tree;
    bst tree1;
    bst tree2;
    printf("\nCreating binary search tree via bst_new()... done!\n\n");

    tree = my_new_bst();
    tree1 = my_new_bst();
    tree2 = my_new_bst();

    printf("Inserting data to binary search tree via bst_insert()... done!\n\n");

    printf("Check the results via bst_search():\n");
    printf("Is there a -D- ? ");
    printf("%d\n",bst_search(tree, "D"));

    printf("Is there a -B- ? ");
    printf("%d\n",bst_search(tree, "B"));

    printf("Is there a -F- ? ");
    printf("%d\n",bst_search(tree, "F"));

    printf("Is there a -A- ? ");
    printf("%d\n",bst_search(tree, "A"));

    printf("Is there a -C- ? ");
    printf("%d\n",bst_search(tree, "C"));

    printf("Is there a -E- ? ");
    printf("%d\n",bst_search(tree, "E"));

    printf("Is there a -G- ? ");
    printf("%d\n\n",bst_search(tree, "G"));

    /*Test the traverse*/
    printf("bst_preorder()\nshould output (D B A C F E G)\n");
    bst_preorder(tree,print_key);
    printf("\n\n");

    printf("bst_inorder()\nshould output (A B C D E F G)\n");
    bst_inorder(tree,print_key);
    printf("\n\n");

    /*Test the delete*/
    printf("bst_delete() -C-;\nshould output (A B D E F G)\n");
    tree = bst_delete(tree,"C");
    bst_inorder(tree,print_key);
    printf("\n\n");

    printf("bst_delete() -B-;\nshould output (A C D E F G)\n");
    tree1 = bst_delete(tree1,"B");
    bst_inorder(tree1,print_key);
    printf("\n\n");

    printf("bst_delete() -D-;\nshould output (A B C E F G)\n");
    tree2 = bst_delete(tree2,"D");
    bst_inorder(tree2,print_key);
    printf("\n\n");

    tree = bst_free(tree);
    tree1 = bst_free(tree1);
    tree2 = bst_free(tree2);

    return EXIT_SUCCESS;
}
