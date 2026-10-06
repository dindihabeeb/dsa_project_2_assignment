#include <stdio.h>
#include "main.h"

int main(void)
{
    const int scores[] = { 56, 23, 91, 34, 72, 48, 85, 17, 63, 79, 42 };
    int n = sizeof scores / sizeof scores[0];
    max_heap h;

    printf("=== 1. Build the Max-Heap ===\n\n");
    build_heap(&h, scores, n);
    printf("\nMax-Heap after construction:\n");
    print_heap(&h);

    printf("=== 2. Urgent container X (priority 100) arrives ===\n\n");
    heap_insert(&h, 'X', 100);
    printf("\nMax-Heap after inserting X:\n");
    print_heap(&h);

    printf("=== 3. Container X is cancelled ===\n\n");
    heap_remove(&h, 'X');
    printf("\nMax-Heap after removing X:\n");
    print_heap(&h);

    return 0;
}
