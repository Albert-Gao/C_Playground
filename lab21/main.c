#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {
    graph my_graph = graph_new(5);

    graph_bi_add_edge(my_graph, 0, 1);
    graph_bi_add_edge(my_graph, 0, 3);
    
    graph_bi_add_edge(my_graph, 1, 0);
    graph_bi_add_edge(my_graph, 1, 2);
    graph_bi_add_edge(my_graph, 1, 4);
    
    graph_bi_add_edge(my_graph, 2, 1);
    graph_bi_add_edge(my_graph, 2, 4);
    
    graph_bi_add_edge(my_graph, 3, 0);
    
    graph_bi_add_edge(my_graph, 4, 1);
    graph_bi_add_edge(my_graph, 4, 2);
    
    graph_bfs(my_graph, 1);
    graph_print(my_graph);
    graph_free(my_graph);
    return EXIT_SUCCESS;
}
