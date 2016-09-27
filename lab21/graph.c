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

struct graphec{
    vertex *vertices;
    int **edges;
    int size;
};

graph graph_new(int size){
    int i,j;
    graph g = emalloc(sizeof * g);
    g->size = size;
    g->vertices = emalloc(g->size * sizeof g->vertices[0]);
    g->edges = emalloc(g->size * sizeof(int*));
    
    for (i=0;i<size;i++){
        g->vertices[i]->predecessor = -1;
        g->vertices[i]->distance = -1;
        g->vertices[i]->state = UNVISITED;
        g->vertices[i]->finish = 0;
        
        g->edges = emalloc(size * sizeof g->edges[0]);
        g->edges[i] = emalloc(size * sizeof g->edges[0][0]);

        for(j=0; j<size; j++){
            g->edges[i][j]=0;
        }       
    }

    return g;
}

void graph_free(graph g){
    int i;
    free(g->vertices);
    for (i=0; i<g->size; i++){
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

void graph_add_edge(graph g, int u, int v){
    g->edges[u][v]=1;
}

void graph_bi_add_edge(graph g, int u, int v){
    g->edges[u][v]=1;
    g->edges[v][u]=1;
}

void graph_print(graph g){
    int i,j;
    printf("Print Graph as an adjacency list:");
    for (i=0; i<g->size; i++){
        printf("%d | ",i);
        for (j=0;j<g->size;j++){
            if (g->edges[i][j]!=0) printf("%d, ",j);
        }
        printf("\n");
    }
}

typedef enum {UNVISITED, VISITED_SELF, VISITED_DESCENDANTS} state_t;

struct vertex {
    int predecessor;
    int distance;
    state_t state;
    int finish;
};


void graph_bfs(graph g, int source){
    int i;
    queue q = queue_new();

    g->vertices[source]->state = VISITED_SELF;
    g->vertices[distance] = 0;
    enqueue(q,source);
    
    while(q->length != 0){
        int u = dequeue(q,source);
        for(i=0; i<g->size; i++){
            if(g->edges[i][u]==1 && g->vertices[i]->state==UNVISITED ){
                g->vertices[i]->state = VISITED_SELF;
                g->vertices[i]->distance = 1 + g->vertices[u]->distance;
                g->vertices[i]->predecessor = u;
                enqueue(q,i);
            }
            g->vertices[u]->state =  VISITED_DESCENDANTS;
        }
    }
}
