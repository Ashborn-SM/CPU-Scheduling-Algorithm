#include "pre-emptive-scheduling.h"

extern Trace** trace_array;

/**
 * @brief compare priority of the processes
 * @param process_a
 * @param process_b
 * @return 0 process_a > process_b
 * @return -1 process_b >= process_a
 */
int compare_priority(void* process_a, void* process_b){
	int a_p = PRIORITY(((Process*)process_a)); 
	int b_p = PRIORITY(((Process*)process_b));	

	return a_p >= b_p? 0: -1;
}

/**
 * @brief check if the given process exist in the given array
 * @param process
 * @param preempting_p_array
 * @return 0 exists
 * @return -1 do not exist
 */
int unique(Process* process, Process** preempting_p_array){
	static size_t size = 0;
	int idx = size;
	while(idx++ != size){
		if(process == preempting_p_array[idx]){ 
			return -1; 
		}
	}
	preempting_p_array[size++] = process;
	return 0;
}	

/**
 * @brief pre-emptive scheduling algorithm
 * @param ProcessHeap all the availble process
 * @return void
 */
void PreEmptiveScheduling(Heap* ProcessHeap){
	int CSWITCH_FLAG = 1;

	int clock = 0;

	Process* running_process = NULL, * prev_running_process = NULL;

	Process* preemting_p_array[ProcessHeap->size];

	Heap* PriorityProcessHeap = malloc(sizeof(*PriorityProcessHeap));
	Heap* PendingProcess = malloc(sizeof(*PendingProcess));

	init_process_heap(PriorityProcessHeap);
	init_process_heap(PendingProcess);

	// TRACER
	trace_array = malloc(ProcessHeap->size*2*sizeof(*trace_array));
	int idx_trace = 0;

	register_key_compare(PriorityProcessHeap, compare_priority);
	register_key_compare(PendingProcess, compare_priority);

	while(is_empty(PriorityProcessHeap) == -1 || is_empty(ProcessHeap) == -1){
		prev_running_process = running_process;
	
		// PROCESS ARRIVAL
		if(is_empty(ProcessHeap) == -1 && get_arrival_t(peak_min(ProcessHeap)) <= clock){
			insert_process(remove_process(ProcessHeap), PriorityProcessHeap);
		}

		running_process = peak_min(PriorityProcessHeap);

		// CONTEXT SWITCH
		if(prev_running_process != NULL && is_equal(running_process, prev_running_process) == -1 && CSWITCH_FLAG){
			UpdateNContextSwitch(prev_running_process);

			// PRE-EMPTION
			if(unique(running_process, preemting_p_array) == 0){
				insert_process(prev_running_process, PendingProcess);
				UpdateNPreemption(PendingProcess);
			}
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

		CSWITCH_FLAG = 1;

		// PROCESS TERMINATION
		if(CheckProcessTermination(running_process) == 0){

			if(peak_min(PriorityProcessHeap) == peak_min(PendingProcess)){
				remove_process(PendingProcess);
			}

			remove_process(PriorityProcessHeap);
			CSWITCH_FLAG = 0;
		}
		clock++;
	}

	UpdateTrace(get_id(running_process), -1, clock, trace_array[idx_trace-1]);
	trace_array[idx_trace] = NULL;

	printf("Clock: %i\n", clock);
}
