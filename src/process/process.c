#include "process.h"
#include "macro.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief create new process
 * @param burst_t burst time of the process
 * @param arrival_t arrival time of the process
 * @param priority priority of the process
 * @return new process
 */
Process* NewProcess(int priority, int arrival_t, int burst_t, char* ID){
	Process* p = malloc(sizeof(Process));

	p->info.id = ID;
	p->info.priority = priority;
	p->info.burst_t = burst_t;
	p->info.arrival_t = arrival_t;
	p->info.state = 0;

	p->N_context_switch = 0;
	p->N_preemption = 0;

	return p;
}

/**
 * @brief return the id of the process
 * @param process
 * @return id
 */
char* get_id(void* process){
	return ID(((Process*)process));
}
/**
 * @brief return the arrival time of the process
 * @param process
 * @return arrival time
 */
int get_arrival_t(void* process){
	return ARRIVAL_TIME(((Process*)process));
}

/**
 * @brief update the execution state of the process
 * @param process process to be updated
 * @return void
 */
void UpdateState(void* process){
	STATE(((Process*)process))++;
}

/**
 * @brief check if the process is ready to be terminated
 * @param process 
 * @return 0 process should be terminated
 * @return -1 process should not be terminated yet
 */
int CheckProcessTermination(void*process){
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
int is_equal(void* process_a, void* process_b){
	Process* a = process_a;
	Process* b = process_b;
	if(strcmp(ID(a), ID(b)) == 0){
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
void UpdateNContextSwitch(void* process){
	((Process*)process)->N_context_switch++;
}

/**
 * @brief update the number of pre-emption happend
 * to the process
 * @param process_heap heap of pending process
 * @retrun void
 */
void UpdateNPreemption(void* pending_heap){
	Heap* p_heap = pending_heap;
	for(int i=1; i<=p_heap->size; i++){
		((Process*)p_heap->array_p[i])->N_preemption++;
	}
}