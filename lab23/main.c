#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {
   
    int d = 0;
    int i = 0;
    int x = 0;
    graph my_graph = NULL;


    if (1 == scanf("%d", &d)) {
        my_graph = graph_new(d);
    }
    while (2 == scanf("%d%d", &i, &x)) {
        graph_add_edge(my_graph, i, x);
    }

    /*
    graph my_graph = graph_new(8);

    graph_bi_add_edge(my_graph, 0, 1);
    graph_bi_add_edge(my_graph, 0, 4);
    
    graph_bi_add_edge(my_graph, 1, 0);
    graph_bi_add_edge(my_graph, 1, 5);
    
    graph_bi_add_edge(my_graph, 2, 3);
    graph_bi_add_edge(my_graph, 2, 5);
    graph_bi_add_edge(my_graph, 2, 6);
    
    graph_bi_add_edge(my_graph, 3, 2);
    graph_bi_add_edge(my_graph, 3, 6);
    graph_bi_add_edge(my_graph, 3, 7);
    
    graph_bi_add_edge(my_graph, 4, 0);

    graph_bi_add_edge(my_graph, 5, 1);
    graph_bi_add_edge(my_graph, 5, 2);
    graph_bi_add_edge(my_graph, 5, 6);

    graph_bi_add_edge(my_graph, 6, 2);
    graph_bi_add_edge(my_graph, 6, 3);
    graph_bi_add_edge(my_graph, 6, 5);
    graph_bi_add_edge(my_graph, 6, 7);

    graph_bi_add_edge(my_graph, 7, 3);
    graph_bi_add_edge(my_graph, 7, 6);
    */
    
    graph_dfs(my_graph);
    graph_print(my_graph);
    graph_free(my_graph);
    return EXIT_SUCCESS;
}
