// Min-P_Array structure definition

#include "p_array.h"

void memswap(void** a, void** b){
	void* temp = *a;
	*a = *b;
	*b = temp;
}

void sorted_insert(P_Array* process_array){
	for(int i=process_array->size-1; i>=process_array->current_idx+1; i--){
		if(process_array->key_compare(process_array->array_p[i], process_array->array_p[i-1]) == 0){
			memswap(&process_array->array_p[i], &process_array->array_p[i-1]);
		}
	}
}

void init_process_array(P_Array* process_array){
	process_array->size = 0;
	process_array->current_idx = 0;
	process_array->capacity = 2;
	process_array->array_p = malloc(sizeof(void*)*process_array->capacity);
}

int is_empty(P_Array* process_array){
	if(process_array->size == process_array->current_idx){
		return 0;
	}
	return -1;
}

void* peak_min(P_Array* process_array){
	if(is_empty(process_array) == 0){ return NULL; }
	return process_array->array_p[process_array->current_idx];
}

void register_key_compare(P_Array* process_array, int (*compare)(void*, void*)){
	process_array->key_compare = compare;
}

void allocate(P_Array* process_array){
	process_array->capacity *= 2;
	void** new_array = malloc(sizeof(void*)*(process_array->capacity));
	for(int i=0; i<process_array->size; i++){
		new_array[i] = process_array->array_p[i];
	}
	free(process_array->array_p);
	process_array->array_p = new_array;
}

void insert_process(void* process, P_Array* process_array){
	if(process == NULL){
		return;
	}
	if(process_array->size == process_array->capacity){
		allocate(process_array);
	}
	process_array->array_p[process_array->size++] = process;
	sorted_insert(process_array);
}

void* remove_process(P_Array* process_array){
	if(is_empty(process_array) == 0){
		return NULL;
	}
	return process_array->array_p[process_array->current_idx++];
}

/*
//DEBUGGING

typedef struct val{
	int id, value;
}val;

void print(P_Array* process_array){
	while(is_empty(process_array)==-1){
		printf("%i ", ((val*)remove_process(process_array))->id);
	}
}

int compare(void* a, void* b){
	val* x = a;
	val* y = b;
	return x->value < y->value? 0: -1;
}

int main(){
	P_Array* process_array = malloc(sizeof(*process_array));

	init_process_array(process_array);
	register_key_compare(process_array, compare);

	val* a1 = malloc(sizeof(val));
	val* a2 = malloc(sizeof(val));
	val* a3 = malloc(sizeof(val));
	val* a4 = malloc(sizeof(val));

	a1->value = 0;
	a1->id = 1;

	a2->value = 3;
	a2->id = 2;

	a3->value = 2;
	a3->id = 3;

	a4->value = 1;
	a4->id = 4;

	insert_process(a1, process_array);
	insert_process(a2, process_array);
	insert_process(a3, process_array);
	insert_process(a4, process_array);

	print(process_array);

}
*/
