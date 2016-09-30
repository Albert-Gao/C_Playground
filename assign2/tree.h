/**
 * TREE ADT Interface
 * Stores and manages a collection of strings using either a binary search tree or a red black tree.
 * Uses tree: definitions of tree data structure
 * Uses mylib: memory allocation and getword functions.
 * @Author foxre274 gaoha773 scrca599
 * @Date 10/Sep/2016
 */

#ifndef TREE_H_
#define TREE_H_

typedef struct treenode *tree;
typedef enum tree_e {BST, RBT} tree_t;

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
extern tree tree_insert(tree b, char *str);


/**
 * Sets the tree type (BST by default)
 * 
 * @param type the type of tree to be used. 
 * 
 * @return a new tree initialised to a NULL value. 
 */
extern tree tree_new(tree_t type);

/**
 * free the memory occupied by the tree.
 * we will visit every subtree to make sure no leak happens.
 * 
 * @param b the tree to be freed.
 */ 
extern void tree_free(tree b);

/**
 * Traverse the tree using preorder, which means visit the root first.
 * 
 * @param b the tree to traverse.
 * @param f the function which will be invoked while traversing.
 */ 
extern void tree_preorder(tree b, void f(int f, char *w));

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
extern int tree_search(tree b, char *str);

/**
 * Finds the depth of a tree. 
 * Recursive method, finding the depth of the right and left subtree. 
 * 
 * @param c tree to find the depth of. 
 * 
 * @return 0 if the tree is empty, or the depth of the largest 
 * left or right subtree. 
 */
extern int tree_depth (tree c);
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

extern void tree_output_dot(tree t, FILE *out);
#endif





