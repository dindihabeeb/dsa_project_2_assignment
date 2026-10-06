#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "main.h"

/* Read a gateway name, re-prompting until it is one of A..G.
 * Returns its index, or -1 on end of input. */
static int read_gateway(void)
{
    char line[64];

    for (;;) {
        printf("Enter starting gateway: ");
        if (fgets(line, sizeof line, stdin) == NULL)
            return -1;
        line[strcspn(line, "\r\n")] = '\0';

        if (strlen(line) == 1) {
            char c = toupper((unsigned char)line[0]);

            if (c >= 'A' && c < 'A' + V)
                return c - 'A';
        }
        printf("Invalid gateway \"%s\". Valid gateways are A to %c.\n", line,
               'A' + V - 1);
    }
}

int main(void)
{
    int adj[V][V] = { { 0 } };
    int order[V], hops[V];
    int start, n, best = -1;

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

    start = read_gateway();
    if (start == -1) {
        printf("\nNo gateway entered.\n");
        return 1;
    }

    n = bfs(adj, start, order, hops);

    printf("\nBFS order from %c:", 'A' + start);
    for (int i = 0; i < n; i++)
        printf(" %c", 'A' + order[i]);
    printf("\n");

    printf("\nGateways directly connected to %c (one hop), in BFS order:\n",
           'A' + start);
    for (int i = 0; i < n; i++) {
        int g = order[i];

        if (hops[g] != 1)
            continue;
        printf("  %c - %d ms\n", 'A' + g, adj[start][g]);
        if (best == -1 || adj[start][g] > adj[start][best])
            best = g;
    }

    if (best == -1)
        printf("  none\n");
    else
        printf("\nHighest data-transfer time: %c (%d ms)\n", 'A' + best,
               adj[start][best]);

    return 0;
}
