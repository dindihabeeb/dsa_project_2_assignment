#include "main.h"

/* Undirected: store the time in both [a][b] and [b][a] */
void add_edge(int adj[V][V], char a, char b, int ms)
{
    adj[a - 'A'][b - 'A'] = ms;
    adj[b - 'A'][a - 'A'] = ms;
}

/* Each gateway is enqueued at most once, so V slots are enough */
static void enqueue(queue *q, int x)
{
    q->items[q->rear++] = x;
}

static int dequeue(queue *q)
{
    return q->items[q->front++];
}

static int is_empty(const queue *q)
{
    return q->front == q->rear;
}

/* BFS from start. order[] receives the gateways in the order they are
 * discovered, hops[] each gateway's distance in links from start (-1 if
 * unreachable). Returns how many gateways were discovered. */
int bfs(int adj[V][V], int start, int *order, int *hops)
{
    queue q = { { 0 }, 0, 0 };
    int n = 0;

    for (int i = 0; i < V; i++)
        hops[i] = -1;

    hops[start] = 0;
    order[n++] = start;
    enqueue(&q, start);

    while (!is_empty(&q)) {
        int u = dequeue(&q);

        for (int v = 0; v < V; v++) {
            if (adj[u][v] != 0 && hops[v] == -1) {
                hops[v] = hops[u] + 1;
                order[n++] = v;
                enqueue(&q, v);
            }
        }
    }
    return n;
}
