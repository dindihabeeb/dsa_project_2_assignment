#ifndef MAIN_H
#define MAIN_H

#include <limits.h>

#define V 10 /* data centers A..J */
#define MAX_EDGES 64
#define INF INT_MAX

typedef struct {
    int from, to; /* vertex indices: 0 = A, 1 = B, ... */
    int cost;
} edge;

/* Weighted directed graph stored as an edge list */
typedef struct {
    edge edges[MAX_EDGES];
    int n_edges;
} graph;

/* bellman_ford.c */
int vertex_index(char name);
int add_route(graph *g, char from, char to, int cost);
void print_graph(const graph *g);
int bellman_ford(const graph *g, int src, int *dist, int *pred);
void print_routing_table(int src, const int *dist, const int *pred);

#endif
