#ifndef MAIN_H
#define MAIN_H

#define HEAP_CAPACITY 64

typedef struct {
    char id;      /* container ID: 'A', 'B', ... */
    int priority; /* priority score */
} container;

typedef struct {
    container items[HEAP_CAPACITY];
    int size;
} max_heap;

/* heap.c */
void build_heap(max_heap *h, const int *scores, int n);
int heap_insert(max_heap *h, char id, int priority);
int heap_remove(max_heap *h, char id);
void print_heap(const max_heap *h);

#endif
