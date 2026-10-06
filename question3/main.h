#ifndef MAIN_H
#define MAIN_H

#define V 7 /* stations A..G */
#define MAX_EDGES (V * (V - 1) / 2)

typedef struct {
    int u, v; /* station indices: 0 = A, 1 = B, ... */
    int cost;
} edge;

/* graph.c */
void add_edge(int adj[V][V], char a, char b, int cost);
void print_matrix(int adj[V][V]);
int kruskal(int adj[V][V], edge *mst);

#endif
