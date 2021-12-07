/**
 * @file scheduling.c
 * @brief 
 * @author Ashborn-SM
 */

#include <stdio.h>
#include "heap.h"
#include "macro.h"
#include "process/process.h"
#include "process/trace.h"
#include "Pre-emptive-Scheduling/pre-emptive-scheduling.h"

int compare(void* a, void* b){
	int p1 = ARRIVAL_TIME(((Process*)a));
	int p2 = ARRIVAL_TIME(((Process*)b));

	return p1 >= p2? 0: -1;
}

void print(Heap* process_heap){
	while(is_empty(process_heap) != 0){
		printf("%i ",
		ARRIVAL_TIME(((Process*)remove_process(process_heap))));
	}
}

Trace** trace_array;

int main(){
	Process* p1 = NewProcess(3, 0, 8, "P1");
	Process* p2 = NewProcess(4, 1, 2, "P2");
	Process* p3 = NewProcess(4, 3, 4, "P3");
	Process* p4 = NewProcess(5, 4, 1, "P4");
	Process* p5 = NewProcess(2, 5, 6, "P5");
	Process* p6 = NewProcess(6, 6, 5, "P6");
	Process* p7 = NewProcess(1, 10, 1, "P7");

	Heap* process_heap = malloc(sizeof(Heap));
	init_process_heap(process_heap);
	register_key_compare(process_heap, compare);

	insert_process(p1, process_heap);
	insert_process(p2, process_heap);
	insert_process(p3, process_heap);
	insert_process(p4, process_heap);
	insert_process(p5, process_heap);
	insert_process(p6, process_heap);
	insert_process(p7, process_heap);

	PreEmptiveScheduling(process_heap);

	Process* arr_p[] = {
		p1, p2, p3, p4, p5, p6, p7
	};

	for(int i=0; i<sizeof(arr_p)/sizeof(arr_p[0]); i++){
		printf("Number of context switch in %s: %i, ", ID(arr_p[i]), arr_p[i]->N_context_switch);
		printf("Number of pre-emption in %s: %i\n", ID(arr_p[i]), arr_p[i]->N_preemption);
		printf("\n");
	}

	render(trace_array, 7);
	return 0;
}

