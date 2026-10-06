#ifndef MAIN_H
#define MAIN_H

#define HEAP_CAPACITY 64

typedef struct {
    char id[8];
    char name[32];
    int priority;
} patient;

typedef struct {
    patient items[HEAP_CAPACITY];
    int size;
} max_heap;

/* heap.c */
void heapify(max_heap *h, int i);
void build_heap(max_heap *h, const patient *records, int n);
int extract_max(max_heap *h, patient *out);
int heap_insert(max_heap *h, patient p);
int heap_delete(max_heap *h, const char *id);
void print_heap(const max_heap *h);

#endif
