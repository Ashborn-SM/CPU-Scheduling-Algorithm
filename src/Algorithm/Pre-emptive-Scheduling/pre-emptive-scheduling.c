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
	int clock = 0, CSWITCH_FLAG = 1, PREEMPTION_FLAG = 1;
	Heap* PriorityProcessArray = malloc(sizeof(Heap));
	Heap* PendingProcess = malloc(sizeof(Heap));
	void* running_process = NULL, * prev_running_process = NULL;

	register_key_compare(PriorityProcessArray, compare_priority);
	register_key_compare(PendingProcess, compare_priority);

	while(is_empty(PriorityProcessArray) == -1 || is_empty(ProcessHeap) == -1){
		prev_running_process = running_process;
	
		if(is_empty(ProcessHeap) == -1 && get_arrival_t(peak_min(ProcessHeap)) <= clock){
			insert_process(remove_process(ProcessHeap), PriorityProcessArray);
		}
		running_process = peak_min(PriorityProcessArray);
		if(prev_running_process != NULL && is_equal(running_process, prev_running_process) == -1 && CSWITCH_FLAG){
			UpdateNContextSwitch(prev_running_process);
			insert_process(prev_running_process, PendingProcess);
			UpdateNPreemption(PendingProcess);
			PREEMPTION_FLAG = 0;
		}
		UpdateState(running_process);

		CSWITCH_FLAG = 1;
		if(CheckProcessTermination(running_process) == 0){
			if(peak_min(PriorityProcessArray) == peak_min(PendingProcess)){
				remove_process(PendingProcess);
			}
			remove_process(PriorityProcessArray);
			if(PREEMPTION_FLAG){
				UpdateNPreemption(PendingProcess);
			}
			PREEMPTION_FLAG = 1;
			CSWITCH_FLAG = 0;
		}
		clock++;
	}
	printf("Clock: %i\n", clock);
}
