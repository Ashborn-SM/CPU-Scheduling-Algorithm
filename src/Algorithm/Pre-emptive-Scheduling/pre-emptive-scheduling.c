#include "pre-emptive-scheduling.h"

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

	return a_p < b_p? 0: -1;
}

/**
 * @brief check if the given process exist in the given array
 * @param process
 * @param preempting_p_array
 * @return 0 exists
 * @return -1 do not exist
 */
int unique(Process* process, P_Array* p_array){
	int idx = 0;
	while(idx != p_array->size){
		if(is_equal(process, p_array->array_p[++idx]) == 0){ 
			return -1; 
		}
	}
	return 0;
}	

/**
 * @brief pre-emptive scheduling algorithm
 * @param ProcessP_Array all the availble process
 * @return void
 */
void PreEmptiveScheduling(P_Array* ProcessArray){
	int CSWITCH_FLAG = 1;

	int clock = 0;

	Process* running_process = NULL, * prev_running_process = NULL;

	P_Array* PriorityProcessArray = malloc(sizeof(*PriorityProcessArray));
	P_Array* PendingProcessArray = malloc(sizeof(*PendingProcessArray));
	P_Array* PreemptingProcessArray = malloc(sizeof(*PreemptingProcessArray));

	init_process_array(PriorityProcessArray);
	init_process_array(PendingProcessArray);
	init_process_array(PreemptingProcessArray);

	// TRACER
	trace_array = malloc(ProcessArray->size*2*sizeof(*trace_array));
	int idx_trace = 0;

	register_key_compare(PriorityProcessArray, compare_priority);
	register_key_compare(PendingProcessArray, compare_priority);
	register_key_compare(PreemptingProcessArray, compare_priority);

	while(is_empty(PriorityProcessArray) == -1 || is_empty(ProcessArray) == -1){
		prev_running_process = running_process;
		
		// PROCESS ARRIVAL
		if(is_empty(ProcessArray) == -1 && get_arrival_t(peak_min(ProcessArray)) <= clock){
			insert_process(remove_process(ProcessArray), PriorityProcessArray);
		}

		running_process = peak_min(PriorityProcessArray);

		// SWITCH
		if(prev_running_process != NULL && is_equal(running_process, prev_running_process) == -1){

			// CONTEXT SWITCH
			if(CSWITCH_FLAG){
				UpdateNContextSwitch(prev_running_process);

				// PENDING PROCESS
				if(unique(prev_running_process, PendingProcessArray) == 0){
					insert_process(prev_running_process, PendingProcessArray);
				}
			}

			// PRE-EMPTING PROCESS
			if(unique(running_process, PreemptingProcessArray) == 0){
				int start = PendingProcessArray->current_idx;
				if(is_equal(peak_min(PriorityProcessArray), peak_min(PendingProcessArray)) == 0){
					start += 1;
				}
				insert_process(running_process, PreemptingProcessArray);
				UpdateNPreemption(PendingProcessArray, start);
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

		clock++;

		// PROCESS TERMINATION
		if(CheckProcessTermination(running_process) == 0){

			// REMOVING THE PENDING PROCESS
			if(is_equal(peak_min(PendingProcessArray), peak_min(PriorityProcessArray)) == 0){
				remove_process(PendingProcessArray);
			}

			// UPDATE COMPLETION TIME
			COMPLETION_TIME(running_process) = clock;

			remove_process(PriorityProcessArray);
			CSWITCH_FLAG = 0;
		}
	}

	UpdateTrace(get_id(running_process), -1, clock, trace_array[idx_trace-1]);
	trace_array[idx_trace] = NULL;
}
