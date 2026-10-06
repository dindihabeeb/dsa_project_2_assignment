#include <stdio.h>
#include <string.h>
#include "main.h"

#define PARENT(i) (((i) - 1) / 2)
#define LEFT(i)   (2 * (i) + 1)
#define RIGHT(i)  (2 * (i) + 2)

#define CELL 6 /* width of one node label in the tree drawing */

/* Swap whole structs so the ID always travels with its priority */
static void swap(max_heap *h, int i, int j)
{
    container tmp = h->items[i];

    printf("    swap %c(%d) <-> %c(%d)\n", h->items[i].id, h->items[i].priority,
           h->items[j].id, h->items[j].priority);
    h->items[i] = h->items[j];
    h->items[j] = tmp;
}

/* Upward heapify: move node i up while it beats its parent. O(log n) */
static void sift_up(max_heap *h, int i)
{
    while (i > 0 && h->items[i].priority > h->items[PARENT(i)].priority) {
        swap(h, i, PARENT(i));
        i = PARENT(i);
    }
}

/* Downward heapify: move node i down to the larger child until both
 * children are smaller. O(log n) */
static void sift_down(max_heap *h, int i)
{
    for (;;) {
        int largest = i, l = LEFT(i), r = RIGHT(i);

        if (l < h->size && h->items[l].priority > h->items[largest].priority)
            largest = l;
        if (r < h->size && h->items[r].priority > h->items[largest].priority)
            largest = r;
        if (largest == i)
            return;
        swap(h, i, largest);
        i = largest;
    }
}

/* Copy the scores into the array in the given order (the "initial binary
 * tree"), labelling them A, B, C, ..., then heapify bottom-up from the last
 * internal node. O(n) */
void build_heap(max_heap *h, const int *scores, int n)
{
    if (n > HEAP_CAPACITY)
        n = HEAP_CAPACITY;
    h->size = n;
    for (int i = 0; i < n; i++) {
        h->items[i].id = 'A' + i;
        h->items[i].priority = scores[i];
    }

    printf("Initial binary tree (array order, before heapify):\n");
    print_heap(h);

    printf("Heapify (sift-down from the last internal node to the root):\n");
    for (int i = PARENT(n - 1); i >= 0; i--) {
        printf("  sift_down at index %d, %c(%d)\n", i, h->items[i].id,
               h->items[i].priority);
        sift_down(h, i);
    }
}

/* Append at the next free slot, then heapify up. Returns 0 if full. */
int heap_insert(max_heap *h, char id, int priority)
{
    if (h->size == HEAP_CAPACITY) {
        printf("Heap is full, %c not inserted.\n", id);
        return 0;
    }
    h->items[h->size].id = id;
    h->items[h->size].priority = priority;
    h->size++;

    printf("  %c(%d) placed at index %d, sift_up:\n", id, priority, h->size - 1);
    sift_up(h, h->size - 1);
    return 1;
}

/* Remove a container by ID: find it (O(n)), overwrite it with the last
 * element, shrink the heap, then re-heapify from that slot. The moved
 * element may be larger than its new parent (sift up) or smaller than a
 * child (sift down); only one of the two will do anything.
 * Returns 0 if the ID is not in the heap. */
int heap_remove(max_heap *h, char id)
{
    int i;

    for (i = 0; i < h->size; i++)
        if (h->items[i].id == id)
            break;
    if (i == h->size) {
        printf("Container %c not found.\n", id);
        return 0;
    }

    printf("  %c(%d) found at index %d\n", id, h->items[i].priority, i);
    h->size--;
    if (i == h->size)       /* it was the last element: nothing to fix */
        return 1;

    h->items[i] = h->items[h->size];
    printf("  last element %c(%d) moved to index %d, re-heapify:\n",
           h->items[i].id, h->items[i].priority, i);
    if (i > 0 && h->items[i].priority > h->items[PARENT(i)].priority)
        sift_up(h, i);
    else
        sift_down(h, i);
    return 1;
}

/* Print the array, then draw the tree level by level, centring each node
 * over the span of the bottom level it covers. */
void print_heap(const max_heap *h)
{
    int levels = 0, width;

    if (h->size == 0) {
        printf("  (empty)\n\n");
        return;
    }

    printf("  Index:    ");
    for (int i = 0; i < h->size; i++)
        printf("%5d", i);
    printf("\n  ID:       ");
    for (int i = 0; i < h->size; i++)
        printf("%5c", h->items[i].id);
    printf("\n  Priority: ");
    for (int i = 0; i < h->size; i++)
        printf("%5d", h->items[i].priority);
    printf("\n\n");

    while ((1 << levels) - 1 < h->size)
        levels++;
    width = (1 << (levels - 1)) * CELL;

    for (int lvl = 0, start = 0; lvl < levels; lvl++, start = 2 * start + 1) {
        int count = 1 << lvl, span = width / count, col = 0;
        char label[16];

        printf("  ");
        for (int k = 0; k < count && start + k < h->size; k++) {
            const container *c = &h->items[start + k];
            int len = snprintf(label, sizeof label, "%c:%d", c->id, c->priority);
            int pos = k * span + (span - len) / 2;

            printf("%*s%s", pos - col, "", label);
            col = pos + len;
        }
        printf("\n");
    }
    printf("\n");
}
