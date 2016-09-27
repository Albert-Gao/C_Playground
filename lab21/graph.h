#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>

typedef struct graphrec *graph;
typedef struct vertex vertex;

extern graph graph_new(int size);
extern void graph_free(graph g);
extern void graph_add_edge(graph g, int u, int v);
extern void graph_bi_add_edge(graph g, int u, int v);
extern void graph_print(graph g);
extern void graph_bfs(graph g, int source);

#endif
