// Header file for the min-array structure

#ifndef P_ARRAY
#define P_ARRAY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct array_t{
	void** array_p;
	int size, capacity, current_idx;
	int (*key_compare)(void*, void*);
}P_Array;


void init_process_array(P_Array* process_array);
void insert_process(void* process, P_Array* process_array);
void* remove_process(P_Array* process_array);
void deallocate_array(P_Array* process_array);
int is_empty(P_Array* process_array);
void register_key_compare(P_Array* process_array, int (*compare)(void*, void*));
void* peak_min(P_Array* process_array);

#endif
