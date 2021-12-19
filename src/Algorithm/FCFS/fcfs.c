#include "fcfs.h"

extern Trace** trace_array;

void FCFS(Heap* ProcessHeap){
	// waiting time for first process is 0
	int clock = 0, idx_trace = 0;
	Process* running_process = NULL;

    trace_array = malloc(ProcessHeap->size*2*sizeof(*trace_array));

	// calculating waiting time
	printf("ID\tCompletion time\n");
	while(is_empty(ProcessHeap) == -1){
		if(get_arrival_t(peak_min(ProcessHeap)) <= clock){
			running_process = remove_process(ProcessHeap);
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