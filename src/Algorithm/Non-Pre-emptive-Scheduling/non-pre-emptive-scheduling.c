#include "non-pre-emptive-scheduling.h"


extern Trace** trace_array;

void NonPreEmptiveScheduling(P_Array* Process_Array, int (*compare)(void*, void*)){
	// waiting time for first process is 0
	int clock = 0, idx_trace = 0, avg_wait_time = 0, avg_turn_around_time = 0, size = Process_Array->size, idx = 0;
	Process* running_process = NULL;
	P_Array* Array = malloc(sizeof(*Array));

	init_process_array(Array);
	register_key_compare(Array, compare);
	trace_array = malloc(Process_Array->size*2*sizeof(*trace_array));

	while(is_empty(Process_Array) == -1 || is_empty(Array) == -1){

		while(idx<=clock && is_empty(Process_Array) == -1){
			if(get_arrival_t(peak_min(Process_Array)) <= clock){
				void* prcoess =  remove_process(Process_Array);
				insert_process(prcoess, Array);
			}
			idx++;
		}

		if(get_arrival_t(peak_min(Array)) <= clock && get_arrival_t(peak_min(Array)) != -1){
			running_process = remove_process(Array);
		}
		else{
            // trace
			trace_array[idx_trace] = malloc(sizeof(**trace_array));
			UpdateTrace("n\\a", clock, -1, trace_array[idx_trace++]);

			clock++;
			continue;
		}
		// trace
		trace_array[idx_trace] = malloc(sizeof(**trace_array));
		UpdateTrace(get_id(running_process), clock, -1, trace_array[idx_trace++]);

		clock += BURST_TIME(running_process);

		COMPLETION_TIME(running_process) = clock;
		TURN_AROUND_TIME(running_process) = COMPLETION_TIME(running_process)- ARRIVAL_TIME(running_process);
		WAIT_TIME(running_process) = TURN_AROUND_TIME(running_process)-BURST_TIME(running_process);
		
		avg_turn_around_time += TURN_AROUND_TIME(running_process);
		avg_wait_time += WAIT_TIME(running_process);
		
	}
	UpdateTrace(get_id(running_process), -1, clock, trace_array[idx_trace-1]);
	trace_array[idx_trace] = NULL;


	printf("\nAverage trun-around time: %f\n", (float)avg_turn_around_time/size);
	printf("Average wait time: %f\n", (float)avg_wait_time/size);		
}
