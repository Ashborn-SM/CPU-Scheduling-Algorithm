#include <stdlib.h>
#include <string.h>
#include "process.h"

/**
 * @brief create new process
 * @param burst_t burst time of the process
 * @param arrival_t arrival time of the process
 * @param priority priority of the process
 * @return new process
 */
Process* NewProcess(int priority, int arrival_t, int burst_t, char* ID){
	Process* p = malloc(sizeof(*p));

	p->info.id = ID;
	p->info.priority = priority;
	p->info.burst_t = burst_t;
	p->info.arrival_t = arrival_t;
	p->info.state = 0;
	p->info.completion_time = 0;

	p->N_context_switch = 0;
	p->N_preemption = 0;

	return p;
}

/**
 * @brief return the id of the process
 * @param process
 * @return id
 */
char* get_id(Process* process){
	if(process == NULL){ return NULL; }
	return ID(process);
}
/**
 * @brief return the arrival time of the process
 * @param process
 * @return arrival time
 */
int get_arrival_t(Process* process){
	if(process == NULL){ return -1; }
	return ARRIVAL_TIME(process);
}

/**
 * @brief update the execution state of the process
 * @param process process to be updated
 * @return void
 */
void UpdateState(Process* process){
	if(process == NULL){ return; }
	STATE(process)++;
}

/**
 * @brief check if the process is ready to be terminated
 * @param process 
 * @return 0 process should be terminated
 * @return -1 process should not be terminated yet
 */
int CheckProcessTermination(Process* process){
	Process* p = process;
	if(process == NULL){ return -1; }
	else if(STATE(p) == BURST_TIME(p)){
		return 0;
	}
	return -1;
}

/**
 * @brief check if the two process are the same
 * @param process_a first process
 * @param process_b second process
 * @return 0 if two process are the same
 * @return -1 if two process are different
 */
int is_equal(Process* process_a, Process* process_b){
	if(process_a == NULL || process_b == NULL){
		return -1;
	}
	if(strcmp(ID(process_a), ID(process_b)) == 0){
		return 0;
	}
	return -1;
}

/**
 * @brief update the number of context swithces happend
 * to the process
 * @param process
 * @retrun void
 */
void UpdateNContextSwitch(Process* process){
	process->N_context_switch++;
}

/**
 * @brief update the number of pre-emption happend
 * to the process
 * @param process_heap heap of pending process
 * @retrun void
 */
void UpdateNPreemption(Heap* pending_heap, int start){
	for(int i=start; i<=pending_heap->size; i++){
		((Process*)pending_heap->array_p[i])->N_preemption++;
	}
}
