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
    bst tree = my_new_bst();
    bst tree1 = my_new_bst();
    bst tree2 = my_new_bst();

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
    printf("%d\n",bst_search(tree, "G"));

    /*Test the traverse*/
    printf("Preorder:(D B A C F E G)\n");
    bst_preorder(tree,print_key);
    printf("\n\n");

    printf("Inorder:(A B C D E F G)\n");
    bst_inorder(tree,print_key);
    printf("\n\n");

    /*Test the delete*/
    printf("Delete -C-:(A B D E F G)\n");
    tree = bst_delete(tree,"C");
    bst_inorder(tree,print_key);
    printf("\n\n");

    printf("Delete -B-:(A C D E F G)\n");
    tree = bst_delete(tree1,"B");
    bst_inorder(tree1,print_key);
    printf("\n\n");
    
    printf("Delete -D-:(A B C E F G)\n");
    tree = bst_delete(tree2,"B");
    bst_inorder(tree2,print_key);
    printf("\n\n");

    bst_free(tree);
    bst_free(tree1);
    bst_free(tree2);

    return EXIT_SUCCESS;
}
