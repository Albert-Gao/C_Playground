#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "rbt.h"

void print_key(char *s) {
    printf("%s ", s);
}

rbt my_new_rbt(){
    rbt tree = rbt_new();
    tree = rbt_insert(tree,"D");
    tree = rbt_insert(tree,"B");
    tree = rbt_insert(tree,"F");
    tree = rbt_insert(tree,"A");
    tree = rbt_insert(tree,"C");
    tree = rbt_insert(tree,"E");
    return tree = rbt_insert(tree,"G");
}

int main(void){
    rbt tree;
    rbt tree1;
    rbt tree2;
    printf("\nCreating binary search tree via rbt_new()... done!\n\n");

    tree = my_new_rbt();
    tree1 = my_new_rbt();
    tree2 = my_new_rbt();
    printf("Inserting data to red black tree via rbt_insert()... done!\n\n");

    printf("Check the results via rbt_search():\n");
    printf("Is there a -D- ? ");
    printf("%d\n",rbt_search(tree, "D"));

    printf("Is there a -B- ? ");
    printf("%d\n",rbt_search(tree, "B"));

    printf("Is there a -F- ? ");
    printf("%d\n",rbt_search(tree, "F"));

    printf("Is there a -A- ? ");
    printf("%d\n",rbt_search(tree, "A"));

    printf("Is there a -C- ? ");
    printf("%d\n",rbt_search(tree, "C"));

    printf("Is there a -E- ? ");
    printf("%d\n",rbt_search(tree, "E"));

    printf("Is there a -G- ? ");
    printf("%d\n\n",rbt_search(tree, "G"));

    /*Test the traverse*/
    printf("rbt_preorder()\nshould output (D B A C F E G)\n");
    rbt_preorder(tree,print_key);
    printf("\n\n");

    printf("rbt_inorder()\nshould output (A B C D E F G)\n");
    rbt_inorder(tree,print_key);
    printf("\n\n");

    /*Test the delete*/
    printf("rbt_delete() -C-;\nshould output (A B D E F G)\n");
    tree = rbt_delete(tree,"C");
    rbt_inorder(tree,print_key);
    printf("\n\n");

    printf("rbt_delete() -B-;\nshould output (A C D E F G)\n");
    tree1 = rbt_delete(tree1,"B");
    rbt_inorder(tree1,print_key);
    printf("\n\n");

    printf("rbt_delete() -D-;\nshould output (A B C E F G)\n");
    tree2 = rbt_delete(tree2,"D");
    rbt_inorder(tree2,print_key);
    printf("\n\n");

    tree = rbt_free(tree);
    tree1 = rbt_free(tree1);
    tree2 = rbt_free(tree2);

    return EXIT_SUCCESS;
}
