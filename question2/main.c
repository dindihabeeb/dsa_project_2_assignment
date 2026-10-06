#include <stdio.h>
#include "main.h"

int main(void)
{
    const patient records[] = {
        { "P01", "Amina", 72 },
        { "P02", "Daniel", 45 },
        { "P03", "Eric", 91 },
        { "P04", "Grace", 63 },
        { "P05", "Hassan", 88 },
        { "P06", "Irene", 54 },
        { "P07", "Jean", 76 },
    };
    const patient kofi = { "P08", "Kofi", 98 };
    max_heap h, queue;
    patient p;

    printf("=== 1. Max-Heap ===\n");
    build_heap(&h, records, sizeof records / sizeof records[0]);
    print_heap(&h);

    /* Extract from a copy so the heap is still there for tasks 3 and 4 */
    printf("=== 2. Treatment order ===\n");
    queue = h;
    while (extract_max(&queue, &p))
        printf("  Patient %s (%s) - Priority %d\n", p.id, p.name, p.priority);
    printf("\n");

    printf("=== 3. Max-Heap after inserting Kofi (P08, 98) ===\n");
    heap_insert(&h, kofi);
    print_heap(&h);

    printf("=== 4. Max-Heap after removing P08 ===\n");
    heap_delete(&h, "P08");
    print_heap(&h);

    return 0;
}
