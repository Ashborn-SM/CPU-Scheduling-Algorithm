#include "fcfs.h"

extern Trace** trace_array;

void FCFS(P_Array* Process_Array){
	// waiting time for first process is 0
	int clock = 0, idx_trace = 0;
	Process* running_process = NULL;

    trace_array = malloc(Process_Array->size*2*sizeof(*trace_array));

	// calculating waiting time
	printf("ID\tCompletion time\n");
	while(is_empty(Process_Array) == -1){
		if(get_arrival_t(peak_min(Process_Array)) <= clock){
			running_process = remove_process(Process_Array);
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

		printf("%s    %i\n", ID(running_process), clock+ BURST_TIME(running_process));

		clock += BURST_TIME(running_process);
	}
    UpdateTrace(get_id(running_process), -1, clock, trace_array[idx_trace-1]);
    trace_array[idx_trace] = NULL;
}