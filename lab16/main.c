#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "rbt.h"

void print_key(char *s) {
    printf("%s ", s);
}

rbt my_new_rbt(){
    rbt tree = rbt_new();
    tree = rbt_insert(tree,"h");
    tree = rbt_insert(tree,"l");
    tree = rbt_insert(tree,"i");
    tree = rbt_insert(tree,"f");
    tree = rbt_insert(tree,"j");
    tree = rbt_insert(tree,"g");
    tree = rbt_insert(tree,"k");
    tree = rbt_insert(tree,"d");
    tree = rbt_insert(tree,"a");
    tree = rbt_insert(tree,"e");
    tree = rbt_insert(tree,"b");
    tree = rbt_insert(tree,"c");
    return tree;
}

int main(void){
    rbt tree;
    printf("\nCreating red black tree via bst_new()... done!\n\n");

    tree = my_new_rbt();

    printf("Inserting data to binary search tree via rbt_insert()... done!\n\n");

    printf("Check the results via rbt_search():\n");
    printf("Is there a -h- ? ");
    printf("%d\n",rbt_search(tree, "h"));

    printf("Is there a -l- ? ");
    printf("%d\n",rbt_search(tree, "l"));

    printf("Is there a -i- ? ");
    printf("%d\n",rbt_search(tree, "i"));

    printf("Is there a -f- ? ");
    printf("%d\n",rbt_search(tree, "f"));

    printf("Is there a -j- ? ");
    printf("%d\n",rbt_search(tree, "j"));

    printf("Is there a -g- ? ");
    printf("%d\n",rbt_search(tree, "g"));

    printf("Is there a -k- ? ");
    printf("%d\n\n",rbt_search(tree, "k"));

    /*Test the traverse*/
    printf("rbt_preorder()\n");
    rbt_preorder(tree);
    printf("\n\n");

    printf("rbt_inorder()\n");
    rbt_inorder(tree);
    printf("\n\n");

    tree = rbt_free(tree);

    return EXIT_SUCCESS;
}
