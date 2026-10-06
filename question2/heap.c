#include <stdio.h>
#include <string.h>
#include "main.h"

#define PARENT(i) (((i) - 1) / 2)
#define LEFT(i)   (2 * (i) + 1)
#define RIGHT(i)  (2 * (i) + 2)

/* Swap whole records so ID, name and priority always stay together */
static void swap(max_heap *h, int i, int j)
{
    patient tmp = h->items[i];

    h->items[i] = h->items[j];
    h->items[j] = tmp;
}

static void sift_up(max_heap *h, int i)
{
    while (i > 0 && h->items[i].priority > h->items[PARENT(i)].priority) {
        swap(h, i, PARENT(i));
        i = PARENT(i);
    }
}

/* Downward heapify: push node i down until it is larger than both children */
void heapify(max_heap *h, int i)
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

/* The records in given order form the initial binary tree; heapify every
 * internal node from the last one up to the root. */
void build_heap(max_heap *h, const patient *records, int n)
{
    if (n > HEAP_CAPACITY)
        n = HEAP_CAPACITY;
    h->size = n;
    for (int i = 0; i < n; i++)
        h->items[i] = records[i];
    for (int i = PARENT(n - 1); i >= 0; i--)
        heapify(h, i);
}

/* Remove the root (highest priority) into *out. Returns 0 if empty. */
int extract_max(max_heap *h, patient *out)
{
    if (h->size == 0)
        return 0;
    *out = h->items[0];
    h->items[0] = h->items[--h->size];
    heapify(h, 0);
    return 1;
}

int heap_insert(max_heap *h, patient p)
{
    if (h->size == HEAP_CAPACITY) {
        printf("Heap is full, %s not inserted.\n", p.id);
        return 0;
    }
    h->items[h->size] = p;
    sift_up(h, h->size++);
    return 1;
}

/* Delete by patient ID: replace it with the last element, shrink, then
 * restore the heap property by moving that element up or down. */
int heap_delete(max_heap *h, const char *id)
{
    int i;

    for (i = 0; i < h->size; i++)
        if (strcmp(h->items[i].id, id) == 0)
            break;
    if (i == h->size) {
        printf("Patient %s not found.\n", id);
        return 0;
    }

    h->items[i] = h->items[--h->size];
    if (i < h->size) {
        if (i > 0 && h->items[i].priority > h->items[PARENT(i)].priority)
            sift_up(h, i);
        else
            heapify(h, i);
    }
    return 1;
}

void print_heap(const max_heap *h)
{
    printf("  %-6s %-6s %-6s %-8s %s\n", "Index", "Level", "ID", "Name", "Priority");
    for (int i = 0, level = 0; i < h->size; i++) {
        if (i == (1 << (level + 1)) - 1)
            level++;
        printf("  %-6d %-6d %-6s %-8s %d\n", i, level, h->items[i].id,
               h->items[i].name, h->items[i].priority);
    }
    printf("\n");
}
