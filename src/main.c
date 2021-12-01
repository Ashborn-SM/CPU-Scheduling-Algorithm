/**
 * @file scheduling.c
 * @brief 
 * @author Ashborn-SM
 */

#include <stdio.h>
#include "heap.h"
#include "macro.h"
#include "process/process.h"
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

int main(){
	Process* p1 = NewProcess(3, 0, 5, "P1");
	Process* p2 = NewProcess(2, 2, 3, "P2");
	Process* p3 = NewProcess(1, 5, 2, "P3");
	/*
	Process* p5 = NewProcess(4, 4, 5, "P5");
	Process* p6 = NewProcess(10, 5, 15, "P6");
	Process* p7 = NewProcess(9, 15, 8, "P7");
	*/

	Heap* process_heap = malloc(sizeof(Heap));
	init_process_heap(process_heap);
	register_key_compare(process_heap, compare);

	insert_process(p1, process_heap);
	insert_process(p2, process_heap);
	insert_process(p3, process_heap);
	/*
	insert_process(p4, process_heap);
	insert_process(p5, process_heap);
	insert_process(p6, process_heap);
	insert_process(p7, process_heap);
	*/
	PreEmptiveScheduling(process_heap);

	printf("%i %i %i\n", p1->N_preemption, p2->N_preemption,
	p3->N_preemption);
	printf("%i %i %i", p1->N_context_switch, p2->N_context_switch,
	p3->N_context_switch);


	return 0;
}

