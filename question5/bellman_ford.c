#include <stdio.h>
#include <ctype.h>
#include "main.h"

#define NAME(i) ('A' + (i))

/* Returns the index of a data-center name, or -1 if it is not A..J */
int vertex_index(char name)
{
    int c = toupper((unsigned char)name);

    if (c < 'A' || c >= 'A' + V)
        return -1;
    return c - 'A';
}

/* Add the directed route from -> to. Returns 0 if a name is invalid. */
int add_route(graph *g, char from, char to, int cost)
{
    int u = vertex_index(from), v = vertex_index(to);

    if (u == -1 || v == -1) {
        printf("Invalid route %c -> %c: unknown data center, skipped.\n", from, to);
        return 0;
    }
    if (g->n_edges == MAX_EDGES) {
        printf("Too many routes, %c -> %c skipped.\n", from, to);
        return 0;
    }
    g->edges[g->n_edges++] = (edge){ u, v, cost };
    return 1;
}

void print_graph(const graph *g)
{
    printf("Vertices: ");
    for (int i = 0; i < V; i++)
        printf("%c ", NAME(i));
    printf("\nDirected edges (from -> to : cost):\n");
    for (int i = 0; i < g->n_edges; i++)
        printf("  %c -> %c : %d\n", NAME(g->edges[i].from), NAME(g->edges[i].to),
               g->edges[i].cost);
}

/* Fills dist[] with the minimum cost from src (INF if unreachable) and
 * pred[] with the previous vertex on that path (-1 if none).
 * Returns 1 if a negative-weight cycle is reachable from src, 0 otherwise. */
int bellman_ford(const graph *g, int src, int *dist, int *pred)
{
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[src] = 0;

    /* A shortest path has at most V - 1 edges, so V - 1 rounds of relaxing
     * every edge are enough when there is no negative cycle. */
    for (int round = 1; round <= V - 1; round++) {
        for (int i = 0; i < g->n_edges; i++) {
            const edge *e = &g->edges[i];

            if (dist[e->from] != INF && dist[e->from] + e->cost < dist[e->to]) {
                dist[e->to] = dist[e->from] + e->cost;
                pred[e->to] = e->from;
            }
        }
    }

    /* If any edge can still be relaxed, a reachable negative cycle exists */
    for (int i = 0; i < g->n_edges; i++) {
        const edge *e = &g->edges[i];

        if (dist[e->from] != INF && dist[e->from] + e->cost < dist[e->to])
            return 1;
    }
    return 0;
}

/* Follow pred[] back from dest to src, then print it forwards */
static void print_path(int dest, const int *pred)
{
    int path[V], n = 0;

    for (int v = dest; v != -1 && n < V; v = pred[v])
        path[n++] = v;
    for (int i = n - 1; i >= 0; i--)
        printf("%c%s", NAME(path[i]), i > 0 ? " -> " : "");
}

void print_routing_table(int src, const int *dist, const int *pred)
{
    printf("Source: %c\n\n", NAME(src));
    printf("%-13s %-15s %s\n", "Destination", "Shortest Cost", "Path");
    for (int v = 0; v < V; v++) {
        if (v == src)
            continue;
        if (dist[v] == INF) {
            printf("%-13c %-15s %s\n", NAME(v), "unreachable", "-");
        } else {
            printf("%-13c %-15d ", NAME(v), dist[v]);
            print_path(v, pred);
            printf("\n");
        }
    }
}
