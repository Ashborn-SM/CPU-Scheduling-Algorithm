// Min-Heap structure definition

#include "heap.h"

void memswap(void** a, void** b){
	void* temp = *a;
	*a = *b;
	*b = temp;
}

void init_process_heap(Heap* process_heap){
	process_heap->size = 0;
	process_heap->capacity = 2;
	process_heap->array_p = malloc(sizeof(void*)*(process_heap->capacity+1));
}

int is_empty(Heap* process_heap){
	if(process_heap->size == 0){
		return 0;
	}
	return -1;
}

void* peak_min(Heap* process_heap){
	if(is_empty(process_heap) == 0){ return NULL; }
	return process_heap->array_p[1];
}

void register_key_compare(Heap* process_heap, int (*compare)(void*, void*)){
	process_heap->key_compare = compare;
}

void allocate(Heap* process_heap){
	process_heap->capacity *= 2;
	void** new_array = malloc(sizeof(void*)*(process_heap->capacity+1));
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
	if(process == NULL){
		return;
	}
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
	if(index*2 <= process_heap->size){
		if(process_heap->key_compare(process_heap->array_p[index], process_heap->array_p[child_index]) == 0){
			memswap(&(process_heap->array_p[child_index]), &(process_heap->array_p[index]));
			heapifyDOWN(process_heap, child_index);
		}
	}
}

void* remove_process(Heap* process_heap){
	if(is_empty(process_heap) == 0){
		return NULL;
	}
	memswap(&(process_heap->array_p[1]), &(process_heap->array_p[process_heap->size--]));
	heapifyDOWN(process_heap, 1);
	return process_heap->array_p[process_heap->size+1];
}

/*

//DEBUGGING

typedef struct val{
	int id, value;
}val;

void print(Heap* process_heap){
	while(is_empty(process_heap)==-1){
		printf("%i ", ((val*)remove_process(process_heap))->id);
	}
}

int compare(void* a, void* b){
	val* x = a;
	val* y = b;
	return x->value >= y->value? 0: -1;
}

int main(){
	Heap* process_heap = malloc(sizeof(*process_heap));

	init_process_heap(process_heap);
	register_key_compare(process_heap, compare);

	val* a1 = malloc(sizeof(val));
	val* a2 = malloc(sizeof(val));
	val* a3 = malloc(sizeof(val));
	val* a4 = malloc(sizeof(val));

	a1->value = 1;
	a1->id = 1;

	a2->value = 2;
	a2->id = 2;

	a3->value = 2;
	a3->id = 3;

	a4->value = 3;
	a4->id = 4;

	insert_process(a1, process_heap);
	insert_process(a2, process_heap);
	insert_process(a3, process_heap);
	insert_process(a4, process_heap);

	print(process_heap);

}
*/
