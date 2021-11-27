#include "process.h"

/**
 * @brief create new process
 * @param burst_t burst time of the process
 * @param arrival_t arrival time of the process
 * @param priority priority of the process
 * @return new process
 */
process NewProcess(int burst_t, int arrival_t, int priority, char* ID){
	process p = {
		.info = {
			ID, priority, burst_t, arrival_t, .state = 0,
		}, 
		.N_context_switch = 0,
		.N_preemption = 0,
	};

	return p;
}

/**
 * @brief update the execution state of the process
 * @param process process to be updated
 * @return void
 */
void UpdateState(void* process){
	((Process*)process)->info.state++;
}

/**
 * @brief check if the process is ready to be terminated
 * @param process 
 * @return 0 process should be terminated
 * @return -1 process should not be terminated yet
 */
int CheckProcessTermination(void*process){
	Process* p = process;
	if(p->info.state == p->info.burst_t){
		return 0;
	}
	return -1;
}
