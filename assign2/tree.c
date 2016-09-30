/**
 * TREE ADT
 * Stores and manages a collection of strings using either a binary search tree or a red black tree.
 * Uses tree: definitions of tree data structure
 * Uses mylib: memory allocation and getword functions.
 * @Author foxre274 gaoha773 scrca599
 * @Date 10/Sep/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

typedef enum {RED, BLACK} tree_colour;

struct treenode{
    char *key; /* The value stored in this tree */
    int frequency; /* The number of the times the word occurs (duplicate) */
    tree_colour colour; /* Red or Black*/
    tree left; /* Left subtree */
    tree right; /* Right subtree */
};

static tree_t tree_type = BST; /* Default tree type */

/**
 * Finds the maximum value of two integers.
 * Used by static depth method. 
 * @param a first integer for comparison. 
 * @param b second integer for comparison. 
 * 
 * @return largest of the values. 
 */
static int max(int a,int b){
    if(a > b)
        return a;
    else
        return b;
}

/**
 * Helper method for tree_depth function. 
 * 
 * @param c tree to find the depth of. 
 * 
 * @return height of largest subtree. 
 */
static int depth(tree c){
    if(c == NULL) {
        return 0;
    }
    return  max(depth(c->left),depth(c->right))+1;
}

/**
 * Finds the depth of a tree. 
 * Recursive method, finding the depth of the right and left subtree. 
 * 
 * @param c tree to find the depth of. 
 * 
 * @return 0 if the tree is empty, or the depth of the largest 
 * left or right subtree. 
 */

int tree_depth (tree c){

    if (c == NULL){
        return 0;
    }

    return depth(c)-1;
}

/**
 * Search for the given word in the tree.
 * It will recursively search for the value through the left or right 
 * subtree based on the comparison between the word and the value of node.
 * 
 * @param b the tree to be searched.
 * @param str the word to be found.
 * 
 * @return 1 if found, 0 if not.
 */ 
int tree_search(tree b, char *str){
    
    if (b == NULL){
        return 0;
    }
    if (strcmp(b->key,str)==0){
        return 1;
    }
    if (strcmp(b->key,str) > 0){
        return tree_search(b->left, str);
    }
    else {
         return tree_search(b->right,str);
    }
}

/**
 * Sets the tree type (BST by default)
 * 
 * @param type the type of tree to be used. 
 * 
 * @return a new tree initialised to a NULL value. 
 */ 
tree tree_new(tree_t type){
    tree_type = type;
    return NULL;
}

/**
 * Rotates the right subtree by creating a temporary pointer
 * to the root, shifts the root pointer to the left sub tree, 
 * sets the left tree's inorder successor as the left child of
 * the root, and resets the root pointer. 
 * 
 * Used by tree fix function. 
 * 
 * @param r the tree to be rotated.
 * 
 * @returns the rotated tree.
 */
static tree right_rotate(tree r){
    tree temp = r;
    r = temp->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}
/**
 * Rotates the left subtree by creating a temporary pointer
 * to the root, shifts the root pointer to the right sub tree, 
 * sets the right tree's inorder predecessor as the right child
 * of the root, and resets the root pointer. 
 * 
 * Used by tree fix function. 
 * 
 * @param r the tree to be rotated.
 * 
 * @returns the rotated tree.
 */

static tree left_rotate(tree r){
    tree temp = r;
    r = temp->right;
    temp ->right = r->left;
    r->left = temp;
    return r;
}

/**
 * Checks for two successive red nodes and rebalances 
 * the RBT depending on the value of the "Uncle".
 * Using a top down approach:
 * Case 1 - Uncle red: make root red and roots children black.
 * Case 2 - Uncle black and second consecutive red is inner child: rotate so
 * inner child becomes outer child and becomes case 3.
 * Case 3 - Uncle is black and consective red is an outer child:
 * Swap root and first consecutive red color, rotate to balance. 
 * 
 * @param r tree that needs to be balanced. 
 * 
 * @return balanced tree. 
 */ 

static tree tree_fix (tree r){

    if (IS_RED( r->left)){

        if (IS_RED(r->left->left)){

            if (IS_RED(r->right)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            }


            else if (IS_BLACK(r->right)){
                r = right_rotate(r);
                r->colour = BLACK;
                r->right->colour = RED;
            }
        }


        else if (IS_RED(r->left->right)){

            if (IS_RED(r->right)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            }

            else if (IS_BLACK(r->right )){
                r->left = left_rotate(r->left);
                r = right_rotate(r);
                r->colour = BLACK;
                r->right->colour = RED;
            }
        }
    }

    if (IS_RED(r->right)){
        if(IS_RED(r->right->left)){

            if (IS_RED(r->left)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            }

            else if (IS_BLACK(r->left)){
                r->right = right_rotate(r->right);
                r = left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
            }
        }

        else if (IS_RED(r->right->right)){

            if (IS_RED(r->left)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            }

            else if (IS_BLACK(r->left)){
                r= left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
            }
        }
    }

    return r;
}

/**
 * The helper method to insert a word into a tree.
 * It will recursively find a position for the value through the left or right 
 * subtree based on the comparion between the word and the value of node.
 * If the tree is RBT, tree fix is called to re-balance the tree. 
 * 
 * @param b the tree used to search
 * @param str the word need to find
 * 
 * @return the tree with the new word inserted. 
 */
static tree insert(tree b, char *str){

    if (b == NULL){
        b = emalloc(sizeof * b);
        b -> key = emalloc(strlen(str)+1);
        b -> colour = RED;
        b-> frequency = 1;
        b->right = NULL;
        b->left = NULL;
        strcpy(b->key, str);
        return b;
    }

    else if (strcmp(b->key,str) > 0){
        b->left = insert(b->left, str);
        if (tree_type == RBT){
            b = tree_fix(b);
        }
        return b;
    }

    else if (strcmp(b->key, str) < 0){
        b->right = insert(b->right,str);
        if (tree_type == RBT){
            b = tree_fix(b);
        }
        return b;
    }

    else {
        b->frequency++;
        return b;
    }
}

/**
 * To insert a word in a tree.
 * It will fix the root colour and invoke the helper method.
 * 
 * @param b the tree to insert the new value into.
 * @param str the string to insert into the tree.
 * 
 * @return tree with new value inserted and balanced. 
 * 
 */
tree tree_insert (tree b, char *str){
    if (b != NULL){
        b->colour = BLACK;
    }
    return (insert(b,str));
}

/**
 * Traverse the tree using preorder, which means visit the root first.
 * 
 * @param b the tree to traverse.
 * @param f the function which will be invoked while traversing.
 */ 
void tree_preorder(tree b, void f(int f, char *w)){
    if (b == NULL){
        return;
    }
    f(b->frequency, b->key);
    tree_preorder(b->left,f);
    tree_preorder(b->right,f);
}

/**
 * free the memory occupied by the tree.
 * we will visit every subtree to make sure no leak happens.
 * 
 * @param b the tree to be freed.
 */ 
void tree_free(tree b){
    free( b->key );
    if (b->left != NULL) tree_free(b->left);
    if (b->right != NULL) tree_free(b->right);
    free(b);
    b = NULL;
}

/**
 * Traverses the tree writing a DOT description about connections, and
 * possibly colours, to the given output stream.
 *
 * @param t the tree to output a DOT description of.
 * @param out the stream to write the DOT output to.
 */
static void tree_output_dot_aux(tree t, FILE *out) {
    if(t->key != NULL) {
        fprintf(out, "\"%s\"[label=\"{<f0>%s:%d|{<f1>|<f2>}}\"color=%s];\n",
                t->key, t->key, t->frequency,
                (RBT == tree_type && RED == t->colour) ? "red":"black");
    }
    if(t->left != NULL) {
        tree_output_dot_aux(t->left, out);
        fprintf(out, "\"%s\":f1 -> \"%s\":f0;\n", t->key, t->left->key);
    }
    if(t->right != NULL) {
        tree_output_dot_aux(t->right, out);
        fprintf(out, "\"%s\":f2 -> \"%s\":f0;\n", t->key, t->right->key);
    }
}

/**
 * Output a DOT description of this tree to the given output stream.
 * DOT is a plain text graph description language (see www.graphviz.org).
 * You can create a viewable graph with the command
 *
 *    dot -Tpdf < graphfile.dot > graphfile.pdf
 *
 * You can also use png, ps, jpg, svg... instead of pdf
 *
 * @param t the tree to output the DOT description of.
 * @param out the stream to write the DOT description to.
 */

void tree_output_dot(tree t, FILE *out) {
    fprintf(out, "digraph tree {\nnode [shape = Mrecord, penwidth = 2];\n");
    tree_output_dot_aux(t, out);
    fprintf(out, "}\n");
}
