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
		((Process*)remove_process(process_heap))->N_context_switch);
	}
}

int main(){
	Process* p1 = NewProcess(1, 0, 2, "P1");
	Process* p2 = NewProcess(7, 1, 6, "P2");
	Process* p3 = NewProcess(3, 2, 3, "P3");
	Process* p4 = NewProcess(6, 3, 5, "P4");
	Process* p5 = NewProcess(5, 4, 4, "P5");
	Process* p6 = NewProcess(15, 5, 10, "P6");
	Process* p7 = NewProcess(8, 15, 9, "P7");

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
	printf("sdf");

	print(process_heap);

	return 0;
}

