#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "graph.h"
#include "queue.h"

typedef enum {UNVISITED, VISITED_SELF, VISITED_DESCENDANTS} state_t;

struct vertex {
    int predecessor;
    int distance;
    state_t state;
    int finish;
};

struct graphrec{
    vertex *vertices;
    int **edges;
    int size;
};

/**
 * Declare a new graph with a predefined size;
 * we will declare the according memory space for array of vertex.
 * and for the edges as well.
 * Furthermore, we'll initialize the vertices and edges.
 */
graph graph_new(int size){
    int i,j;
    graph g = emalloc(sizeof * g);
    g->size = size;
    g->vertices = emalloc(size * sizeof g->vertices[0]);
    g->edges = emalloc(size * sizeof(int*));
    
    for (i=0;i<size;i++){
        g->vertices[i].predecessor = -1;
        g->vertices[i].distance = -1;
        g->vertices[i].state = UNVISITED;
        g->vertices[i].finish = 0;
        
        g->edges[i] = emalloc(g->size * sizeof g->edges[0][0]);

        for(j=0; j<size; j++){
            g->edges[i][j]=0;
        }       
    }

    return g;
}

/**
 * Free the memory space used by the graph struct.
 * We need to every array of edges[index] in order to free the edges.
 */
void graph_free(graph g){
    int i;
    free(g->vertices);
    for (i=0; i<g->size; i++){
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

/**
 * Add edge between two vertex,
 * it means we will set the according edge to 1.
 * This is for the directed graph.
 */
void graph_add_edge(graph g, int u, int v){
    g->edges[u][v]=1;
}

/**
 * Add edge between two vertex,
 * it means we will set the according edge to 1.
 * This is for the undirected graph.
 * Since it is undirected,
 * we need to mark both (a to b) and (b to a). 
 */
void graph_bi_add_edge(graph g, int u, int v){
    g->edges[u][v]=1;
    g->edges[v][u]=1;
}

/**
 * Prints the graph as an adjancency list.
 * Basically means we will print all the
 * vertices which link to the current one.
 */
void graph_print(graph g){
    int i,j;
    printf("Print Graph as an adjacency list:\n");
    for (i=0; i<g->size; i++){
        printf("%d | ",i);
        for (j=0;j<g->size;j++){
            if (g->edges[i][j]!=0) printf("%d, ",j);
        }
        printf("\n");
    }

    printf("\nvertex\tdistance pred\n");
    for(i = 0; i< g->size; i++){
        printf("%d\t%d\t %d\n", i, g->vertices[i].distance, g->vertices[i].predecessor);
    }
}

/**
 * Travese the graph from the root with a breadth first favor
 * which means we will travese all the desendants of a vertex first,
 * then travese its desendant via this way.
 */
void graph_bfs(graph g, int source){
    int i;
    queue q = queue_new();

    g->vertices[source].state = VISITED_SELF;
    g->vertices[source].distance = 0;
    enqueue(q,source);
    
    while(queue_size(q)>0){
        int u = dequeue(q);
        for(i=0; i<g->size; i++){
            if(g->edges[i][u]==1 && g->vertices[i].state==UNVISITED ){
                g->vertices[i].state = VISITED_SELF;
                g->vertices[i].distance = 1 + g->vertices[u].distance;
                g->vertices[i].predecessor = u;
                enqueue(q,i);
            }
            g->vertices[u].state =  VISITED_DESCENDANTS;
        }
    }
    
    queue_free(q);
}
