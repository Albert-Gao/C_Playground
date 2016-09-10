#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "mylib.h"


#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

/*typedef enum {RED, BLACK} tree_colour;*/

struct treenode{
    char *key;
    int frequency;
    tree_colour colour;
    tree left;
    tree right;
};

static tree_t tree_type = BST;

static int max(int a,int b){
    if(a > b)
        return a;
    else
        return b;
}

static int depth(tree c){
    if(c == NULL) {
        return 0;
    }
    return  max(depth(c->left),depth(c->right))+1;
}

int tree_depth (tree c){

    if (c == NULL){
        return 0;
    }

    return depth(c)-1;
}

int tree_search(tree b, char *str){
    /* Base cases - Not found and found. */

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


tree tree_new(tree_t type){
    tree_type = type;
    return NULL;
}

static tree right_rotate(tree r){
    tree temp;
    temp = r;
    r = temp->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}

static tree left_rotate(tree r){
    tree temp;
    temp = r;
    r = temp->right;
    temp ->right = r->left;
    r->left = temp;
    return r;
}

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


static tree insert(tree b, char *str){


    if (b == NULL){
        b = emalloc(sizeof * b);
        b -> key = emalloc(strlen(str)+1);
        b -> colour = RED;
        b-> frequency = 1;
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

    /* only other case is if strcmp == 0*/
    else {
        b->frequency++;
        return b;
    }
}

tree tree_insert (tree b, char *str){
    if (b != NULL){
        b->colour = BLACK;
    }
    return (insert(b,str));
}


void node_print(tree b){
    printf("%s",b->key);
    }

/* Used to print the tree. */
void tree_preorder(tree b, void f(int f, char *w)){
    if (b == NULL){
        return;
    }
    f(b->frequency, b->key);
    tree_preorder(b->left,f);
    tree_preorder(b->right,f);
}

/* used for deleteing nodes*/
void tree_postorder(tree b, void f(tree a)){

    if (b == NULL){
        return;
    }
    tree_postorder(b->left,f);
    tree_postorder(b->right,f);
    f(b);

}

static void free_node (tree b){
    /* printf("Node %s freed\n", b->key);*/
    free(b->key);
    free(b);

    /* Set to NULL or other methods base cases won't work. */
    b = NULL;
}

void tree_free(tree b){
    tree_postorder(b,free_node );
}


void tree_inorder(tree b, void f(tree a)){

    if (b == NULL){
        return;
    }

    tree_inorder(b->left,f);
    f(b);
    tree_inorder (b->right,f);
}
/**                                                                                                                            * Traverses the tree writing a DOT description about connections, and                                                         * possibly colours, to the given output stream.                                                                               *                                                                                                                             * @param t the tree to output a DOT description of.                                                                           * @param out the stream to write the DOT output to.                                                                           */
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
/**                                                                                                                            * Output a DOT description of this tree to the given output stream.                                                           * DOT is a plain text graph description language (see www.graphviz.org).                                                      * You can create a viewable graph with the command                                                                            *                                                                                                                             *    dot -Tpdf < graphfile.dot > graphfile.pdf                                                                                *                                                                                                                             * You can also use png, ps, jpg, svg... instead of pdf                                                                        *                                                                                                                             * @param t the tree to output the DOT description of.                                                                         * @param out the stream to write the DOT description to.                                                                      */

    void tree_output_dot(tree t, FILE *out) {
        fprintf(out, "digraph tree {\nnode [shape = Mrecord, penwidth = 2];\n");
        tree_output_dot_aux(t, out);
        fprintf(out, "}\n");
    }

















































