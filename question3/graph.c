#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define NAME(i) ('A' + (i))

/* Undirected: store the cost in both [a][b] and [b][a] */
void add_edge(int adj[V][V], char a, char b, int cost)
{
    adj[a - 'A'][b - 'A'] = cost;
    adj[b - 'A'][a - 'A'] = cost;
}

void print_matrix(int adj[V][V])
{
    printf("    ");
    for (int j = 0; j < V; j++)
        printf("%4c", NAME(j));
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf("%4c", NAME(i));
        for (int j = 0; j < V; j++)
            printf("%4d", adj[i][j]);
        printf("\n");
    }
}

/* Sort by cost; ties broken by station names so the output is fixed */
static int cmp_edge(const void *a, const void *b)
{
    const edge *x = a, *y = b;

    if (x->cost != y->cost)
        return x->cost - y->cost;
    if (x->u != y->u)
        return x->u - y->u;
    return x->v - y->v;
}

/* Union-find: each station points towards the root of its component */
static int find(int *parent, int i)
{
    while (parent[i] != i) {
        parent[i] = parent[parent[i]]; /* path halving */
        i = parent[i];
    }
    return i;
}

/* Fills mst with the selected edges and returns how many there are */
int kruskal(int adj[V][V], edge *mst)
{
    edge edges[MAX_EDGES];
    int parent[V], n = 0, count = 0;

    /* Each undirected edge appears once in the upper triangle */
    for (int i = 0; i < V; i++)
        for (int j = i + 1; j < V; j++)
            if (adj[i][j] != 0)
                edges[n++] = (edge){ i, j, adj[i][j] };

    qsort(edges, n, sizeof(edge), cmp_edge);
    printf("Connections sorted by increasing cost:\n");
    for (int i = 0; i < n; i++)
        printf("  %c - %c : %d\n", NAME(edges[i].u), NAME(edges[i].v), edges[i].cost);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    printf("\nConsidering connections in order:\n");
    for (int i = 0; i < n && count < V - 1; i++) {
        int ru = find(parent, edges[i].u), rv = find(parent, edges[i].v);

        printf("  %c - %c : %-3d ", NAME(edges[i].u), NAME(edges[i].v), edges[i].cost);
        if (ru == rv) {
            printf("rejected (creates a cycle)\n");
        } else {
            parent[ru] = rv;
            mst[count++] = edges[i];
            printf("selected\n");
        }
    }
    return count;
}
