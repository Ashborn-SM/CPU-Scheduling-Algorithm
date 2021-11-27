// Header file for the min-heap structure

#ifndef MIN_HEAP
#define MIN_HEAP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct heap_t Heap;

void init_process_heap(Heap* process_heap);
void insert_process(void* process, Heap* process_heap);
void* remove_process(Heap* process_heap);
void deallocate_heap(Heap* process_heap);
int is_empty(Heap* process_heap);
void register_key_compare(Heap* process_heap, int (*compare)(void*, void*));
void* peak_min(Heap* process_heap);

#endif
