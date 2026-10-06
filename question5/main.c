#include <stdio.h>
#include "main.h"

int main(void)
{
    graph g = { .n_edges = 0 };
    int dist[V], pred[V];
    int src = vertex_index('A');

    add_route(&g, 'A', 'B', 6);
    add_route(&g, 'A', 'D', 16);
    add_route(&g, 'B', 'C', 6);
    add_route(&g, 'B', 'D', 6);
    add_route(&g, 'B', 'J', 7);
    add_route(&g, 'C', 'G', -9);
    add_route(&g, 'D', 'E', 7);
    add_route(&g, 'D', 'J', 8);
    add_route(&g, 'E', 'F', 10);
    add_route(&g, 'E', 'I', -2);
    add_route(&g, 'F', 'G', 4);
    add_route(&g, 'F', 'I', 2);
    add_route(&g, 'G', 'H', 13);
    add_route(&g, 'I', 'F', 2);
    add_route(&g, 'J', 'E', 3);

    printf("=== 1. Data-center network (weighted directed graph) ===\n");
    print_graph(&g);

    printf("\n=== 2-4. Bellman-Ford from A ===\n");
    if (bellman_ford(&g, src, dist, pred)) {
        printf("Negative-weight cycle detected.\n");
        printf("Shortest-path results may be undefined.\n");
        return 0;
    }
    printf("No negative-weight cycle detected.\n");

    printf("\n=== 5. Routing table ===\n");
    print_routing_table(src, dist, pred);

    return 0;
}
