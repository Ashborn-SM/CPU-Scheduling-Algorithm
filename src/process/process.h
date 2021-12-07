#ifndef PROCESS
#define PROCESS

#include "macro.h"
#include "heap.h"

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
}Process;


Process* NewProcess(int priority, int arrival_t, int burst_t, char* ID);
void UpdateState(Process* process);
int CheckProcessTermination(Process* process);
int is_equal(Process* process_a, Process* process_b);
void UpdateNContextSwitch(Process* process);
void UpdateNPreemption(Heap* process, int start);
int get_arrival_t(Process* process);
char* get_id(Process* process);

#endif
