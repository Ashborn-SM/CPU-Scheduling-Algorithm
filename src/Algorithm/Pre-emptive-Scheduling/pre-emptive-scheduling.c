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
 * @brief pre-emptive scheduling algorithm
 * @param ProcessHeap all the availble process
 * @return void
 */
void PreEmptiveScheduling(Heap* ProcessHeap){
	int clock = 0, CSWITCH_FLAG = 1, PREEMPTION_FLAG = 1;
	Heap* PriorityProcessHeap = malloc(sizeof(*PriorityProcessHeap));
	Heap* PendingProcess = malloc(sizeof(*PendingProcess));
	void* running_process = NULL, * prev_running_process = NULL;

	register_key_compare(PriorityProcessHeap, compare_priority);
	register_key_compare(PendingProcess, compare_priority);

	// TRACER
	trace_array = malloc(ProcessHeap->size*2*sizeof(*trace_array));
	int idx_trace = 0;

	while(is_empty(PriorityProcessHeap) == -1 || is_empty(ProcessHeap) == -1){
		prev_running_process = running_process;
	
		if(is_empty(ProcessHeap) == -1 && get_arrival_t(peak_min(ProcessHeap)) <= clock){
			void* arrived_process = remove_process(ProcessHeap);
			insert_process(arrived_process, PriorityProcessHeap);
		}
		running_process = peak_min(PriorityProcessHeap);
		if(prev_running_process != NULL && is_equal(running_process, prev_running_process) == -1 && CSWITCH_FLAG){
			UpdateNContextSwitch(prev_running_process);
			insert_process(prev_running_process, PendingProcess);
			UpdateNPreemption(PendingProcess);
			PREEMPTION_FLAG = 0;
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
		if(CheckProcessTermination(running_process) == 0){
			if(peak_min(PriorityProcessHeap) == peak_min(PendingProcess)){
				remove_process(PendingProcess);
			}
			remove_process(PriorityProcessHeap);
			if(PREEMPTION_FLAG){
				UpdateNPreemption(PendingProcess);
			}
			PREEMPTION_FLAG = 1;
			CSWITCH_FLAG = 0;
		}
		clock++;
	}

	UpdateTrace(get_id(running_process), -1, clock, trace_array[idx_trace-1]);
	trace_array[idx_trace] = NULL;

	printf("Clock: %i\n", clock);
}
