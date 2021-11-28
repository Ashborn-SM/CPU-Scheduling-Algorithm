#include "lib/heap.h"
#include "macro.h"
#include "process/process.h"

int compare_priority(void* process_a, void* process_b);
void PreEmptiveScheduling(Heap* ProcessHeap);
