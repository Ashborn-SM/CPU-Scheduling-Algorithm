#include "non-pre-emptive-scheduling.h"

extern Trace** trace_array;

/**
 * @brief compare priority of the processes
 * @param process_a
 * @param process_b
 * @return 0 process_a > process_b
 * @return -1 process_b >= process_a
 */
static int compare_priority(void* process_a, void* process_b){
	int a_p = PRIORITY(((Process*)process_a)); 
	int b_p = PRIORITY(((Process*)process_b));	

	return a_p >= b_p? 0: -1;
}

/**
 * @brief non-pre-emptive scheduling algorithm
 * @param ProcessHeap all the availble process
 * @return void
 */
void NonPreEmptiveScheduling(Heap* ProcessHeap){
	int clock = 0, TERMINATION_FLAG = 1;

	Process* running_process = NULL, * prev_running_process = NULL;

	Heap* PriorityProcessHeap = malloc(sizeof(*PriorityProcessHeap));
	init_process_heap(PriorityProcessHeap);
	register_key_compare(PriorityProcessHeap, compare_priority);

	// TRACER
	trace_array = malloc(ProcessHeap->size*2*sizeof(*trace_array));
	int idx_trace = 0;

	while(is_empty(PriorityProcessHeap) == -1 || is_empty(ProcessHeap) == -1 || !TERMINATION_FLAG){
		prev_running_process = running_process;
	
		// PROCESS ARRIVAL
		if(is_empty(ProcessHeap) == -1 && get_arrival_t(peak_min(ProcessHeap)) <= clock){
			insert_process(remove_process(ProcessHeap), PriorityProcessHeap);
		}

		if(TERMINATION_FLAG){
			running_process = remove_process(PriorityProcessHeap);
		}

		UpdateState(running_process);

		// TRACER
		if(prev_running_process == NULL || is_equal(running_process, prev_running_process) == -1){
			
			// Updating the end time of the previous process
			if(prev_running_process != NULL){
				UpdateTrace(get_id(prev_running_process), -1, clock, trace_array[idx_trace-1]);
			}

			// Updating the start time of the current process
			trace_array[idx_trace] = malloc(sizeof(**trace_array));
			UpdateTrace(get_id(running_process), clock, -1, trace_array[idx_trace]);
			idx_trace++;
		}

		TERMINATION_FLAG = 0;

		// PROCESS TERMINATION
		if(CheckProcessTermination(running_process) == 0){
			TERMINATION_FLAG = 1;
		}
		clock++;
	}

	UpdateTrace(get_id(running_process), -1, clock, trace_array[idx_trace-1]);
	trace_array[idx_trace] = NULL;
}
