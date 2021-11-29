#include "pre-emptive-scheduling.h"

/**
 * @brief compare priority of the processes
 * @param process_a
 * @param process_b
 * @return 0 process_a >= process_b
 * @return -1 process_b > process_a
 */
int compare_priority(void* process_a, void* process_b){
	int a_p = PRIORITY(((Process*)process_a)); 
	int b_p = PRIORITY(((Process*)process_b));	

	return a_p >= b_p? 0: -1;
}

/**
 * @brief pre-emptive scheduling algorithm
 * @param process_pool all the availble process
 * @return void
 */
void PreEmptiveScheduling(Heap* ProcessHeap){
	int clock = 0;
	Heap* PriorityProcessArray = malloc(sizeof(Heap));
	// Heap* PendingProcessHeap = malloc(sizeof(*PendingProcessHeap));
	void* running_process = NULL, * prev_process = NULL;

	register_key_compare(PriorityProcessArray, compare_priority);
	// register_key_compare(PendingProcessHeap, compare_priority);

	while(is_empty(PriorityProcessArray) == -1 || is_empty(ProcessHeap) == -1){
		prev_process = running_process;
	
		insert_process(remove_process(ProcessHeap), PriorityProcessArray);
		running_process = peak_min(PriorityProcessArray);
		
		if(prev_process != NULL && is_equal(running_process, prev_process) == -1){
			UpdateNContextSwitch(prev_process);
			// UpdateNPreemption(); // Need to implement
		    // insert_process(prev_process, PendingProcessHeap);
		}

		UpdateState(running_process);

		if(CheckProcessTermination(running_process) == 0){
			remove_process(PriorityProcessArray);
			running_process = peak_min(PriorityProcessArray);
		}

		clock++;
	}
}
