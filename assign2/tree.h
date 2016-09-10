#ifndef TREE_H_
#define TREE_H_

typedef struct treenode *tree;

typedef enum tree_e {BST, RBT} tree_t;
typedef enum {RED, BLACK} tree_colour;

extern tree tree_insert(tree b, char *str);
extern tree tree_new(tree_t type);
extern void tree_free(tree b);
extern void tree_preorder(tree b, void f(int f, char *w));
extern void tree_inorder(tree b, void f(tree a));
extern void tree_postorder(tree b, void f(tree a));
extern void node_print(tree b);
extern void tree_print(tree b, void f());
extern int tree_search(tree b, char *str);
extern tree tree_delete(tree b, char *str);
extern int tree_depth (tree c);
extern void tree_output_dot(tree t, FILE *out);
#endif





