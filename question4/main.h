#ifndef MAIN_H
#define MAIN_H

#define V 7 /* gateways A..G */

typedef struct {
    int items[V];
    int front, rear;
} queue;

/* bfs.c */
void add_edge(int adj[V][V], char a, char b, int ms);
int bfs(int adj[V][V], int start, int *order, int *hops);

#endif
