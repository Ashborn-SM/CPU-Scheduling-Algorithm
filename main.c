/**
 * @file scheduling.c
 * @brief 
 * @author Ashborn-SM
 */

#include <stdio.h>

/**
 * @struct PCB
 * @brief process-control-block of the process
 */
typedef struct{
	char* id;      // Process ID
	int priority;  // Priority of the process
	int burst_t;   // CPU burst time of the process
	int arrival_t; // Arrival time of the process
	int state;     // State of the process before interrupt
}PCB;

/**
 * @struct process
 * @breif process
 */
typedef struct{
	PCB info;             // Information of the process
	int N_context_switch; // Number of context switch
	int N_preemption;     // Number of pre-emption
}process;


/**
 * @brief create new process
 * @param burst_t burst time of the process
 * @param arrival_t arrival time of the process
 * @param priority priority of the process
 * @return new process
 */
process new_process(int burst_t, int arrival_t, int priority, char* ID){
	process p = {
		.info = {
			ID, priority, burst_t, arrival_t, .state = 0,
		}, 
		.N_context_switch = 0,
		.N_preemption = 0,
	};

	return p;
}

int main(){
	process* pending = malloc(sizeof(int)*2); // All the interrupted/pending processes

	// Process Creation
	process p1 = new_process(5, 0, 2, "P1");
	process p2 = new_process(3, 2, 1, "P2");
}
