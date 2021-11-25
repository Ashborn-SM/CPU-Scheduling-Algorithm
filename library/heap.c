// Min-Heap structure definition

#include "heap.h"
#include <stdlib.h>

typedef struct heap_t{
	void** array_p, size, capacity;	
	int (*key_compare)(void*, void*);
};

void memswap(void** a, void** b){
	void* temp = *a;
	*a = *b;
	*b = temp;
}

void init_process_heap(Heap* process_heap){
	process_heap->size = 0;
	process_heap->capacity = 2;
	process_heap->array_p = malloc(sizeof(void*)*process_heap->capacity+1);
}

void allocate(Heap* process_heap){
	process_heap->capacity *= 2;
	void** new_array = malloc(sizeof(void*)*process_heap->capacity+1);
	for(int i=0; i<process_heap->size; i++){
		new_array[i] = process_heap->array_p[i];
	}
	free(process_heap->array_p);
	process_heap->array_p = new_array;
}

void heapifyUP(Heap* process_heap, int size){
	if(size > 1){
		if(key_compare(process_heap->array_p[size/2], process_heap->array_p[size] == 0)){
			memswap(process_heap->array_p[size/2], process_heap->array_p[size]);
			heapifyUP(process_heap, size/2);
		}
	}
}

void insert_process(void* process, Heap* process_heap){
	if(process_heap->size == process_heap->capacity){
		allocate(process_heap);
	}
	process_heap->array_p[++process_heap->size] = process;
	heapifyUP(process_heap, process_heap->size);
}
