// Min-Heap structure definition

#include "heap.h"

struct heap_t{
	void** array_p; 
	int size, capacity;	
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

void register_key_compare(Heap* process_heap, int (*compare)(void*, void*)){
	process_heap->key_compare = compare;
}

void allocate(Heap* process_heap){
	process_heap->capacity *= 2;
	void** new_array = malloc(sizeof(void*)*process_heap->capacity+1);
	for(int i=1; i<=process_heap->size; i++){
		new_array[i] = process_heap->array_p[i];
	}
	free(process_heap->array_p);
	process_heap->array_p = new_array;
}

void heapifyUP(Heap* process_heap, int size){
	if(size > 1){
		if(process_heap->key_compare(process_heap->array_p[size/2], process_heap->array_p[size] ) == 0){
			memswap(&(process_heap->array_p[size/2]), &(process_heap->array_p[size]));
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

int child(Heap* process_heap, int index){
	int left = index*2;
	int right = 1+index*2;

	if(right > process_heap->size){
		return left;
	}
	else if(process_heap->key_compare(process_heap->array_p[right], process_heap->array_p[left]) == 0){
		return left;
	}
	return right;
}

void heapifyDOWN(Heap* process_heap, int index){
	int child_index = child(process_heap, index);
	if(index*2 < process_heap->size){
		if(process_heap->key_compare(process_heap->array_p[index], process_heap->array_p[child_index]) == 0){
			memswap(&(process_heap->array_p[child_index]), &(process_heap->array_p[index]));
			heapifyDOWN(process_heap, child_index);
		}
	}
}

void* remove_process(Heap* process_heap){
	void** p = malloc(sizeof(*p));
	memcpy(p, process_heap->array_p[1], sizeof(void*));

	memswap(&(process_heap->array_p[1]), &(process_heap->array_p[process_heap->size--]));
	heapifyDOWN(process_heap, 1);
	return p;
}

/*

DEBUGGING

void print(Heap* process_heap){
	for(int i=1; i<=process_heap->size; i++){
		printf("%i ", *(int*)process_heap->array_p[i]);
	}
}

int compare(void* a, void* b){
	return *(int*)a >= *(int*)b ? 0: -1;
}

int main(){
	Heap* process_heap = malloc(sizeof(*process_heap));

	init_process_heap(process_heap);
	register_key_compare(process_heap, compare);

	int arr[] = {245, 85, 687, 12, 30, 3, 145 , 5};

	for(int i=0; i<8; i++){
		insert_process(arr+i, process_heap);
	}
	
	printf("%i\n", *(int*)remove_process(process_heap));
	printf("%i\n", *(int*)remove_process(process_heap));
	printf("%i\n", *(int*)remove_process(process_heap));
	printf("%i\n", *(int*)remove_process(process_heap));
	printf("%i\n", *(int*)remove_process(process_heap));
	printf("%i\n", *(int*)remove_process(process_heap));
	printf("%i\n", *(int*)remove_process(process_heap));
	printf("%i\n", *(int*)remove_process(process_heap));

	print(process_heap);
}
*/
