#include <stdio.h>
#include "main.h"

int main(void)
{
    int adj[V][V] = { { 0 } };
    edge mst[V - 1];
    int count, total = 0;

    add_edge(adj, 'A', 'B', 6);
    add_edge(adj, 'A', 'D', 12);
    add_edge(adj, 'B', 'D', 5);
    add_edge(adj, 'B', 'C', 11);
    add_edge(adj, 'C', 'D', 17);
    add_edge(adj, 'C', 'G', 25);
    add_edge(adj, 'D', 'E', 22);
    add_edge(adj, 'D', 'F', 15);
    add_edge(adj, 'E', 'F', 10);
    add_edge(adj, 'F', 'G', 22);

    printf("=== 1. Adjacency matrix (cost in $1000s, 0 = no connection) ===\n");
    print_matrix(adj);

    printf("\n=== 2. Kruskal's Algorithm ===\n");
    count = kruskal(adj, mst);

    printf("\n=== 3. Selected connections (MST) ===\n");
    for (int i = 0; i < count; i++) {
        printf("  Station %c - Station %c : %d\n", 'A' + mst[i].u, 'A' + mst[i].v,
               mst[i].cost);
        total += mst[i].cost;
    }
    printf("\nConnections: %d (V - 1 = %d)\n", count, V - 1);
    printf("Total installation cost: %d ($%d,000)\n", total, total);

    return 0;
}
