/**
 * @file scheduling.c
 * @brief 
 * @author Ashborn-SM
 */

#include "include.h"
#include "FCFS/fcfs.h"
#include "Pre-emptive-Scheduling/pre-emptive-scheduling.h"
#include "Non-Pre-emptive-Scheduling/non-pre-emptive-scheduling.h"

int compare_arrival(void* a, void* b){
	int p1 = ARRIVAL_TIME(((Process*)a));
	int p2 = ARRIVAL_TIME(((Process*)b));

	return p1 < p2? 0: -1;
}

int compare_burst(void* a, void* b){
	int p1 = BURST_TIME(((Process*)a));
	int p2 = BURST_TIME(((Process*)b));

	return p1 < p2? 0: -1;
}

int compare_priority(void* process_a, void* process_b){
	int a_p = PRIORITY(((Process*)process_a)); 
	int b_p = PRIORITY(((Process*)process_b));	

	return a_p < b_p? 0: -1;
}

Trace** trace_array;
int main(){
	P_Array* process_array = malloc(sizeof(P_Array)); 
	init_process_array(process_array);

	#ifdef RUN_FCFS
		register_key_compare(process_array, compare_arrival);
		
		Process* p1 = NewProcess(0, 4, 5, "P1 ");
		Process* p2 = NewProcess(0, 6, 4, "P2 ");
		Process* p3 = NewProcess(0, 0, 3, "P3 ");
		Process* p4 = NewProcess(0, 6, 2, "P4 ");
		Process* p5 = NewProcess(0, 5, 4, "P5 ");

		insert_process(p1, process_array);
		insert_process(p2, process_array);
		insert_process(p3, process_array);
		insert_process(p4, process_array);
		insert_process(p5, process_array);

		FCFS(process_array);

		Process* array[] = {p1, p2, p3, p4, p5};

		printf("\nID\tCompletion time   Turn-around time  Waiting time\n");
		for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++){
			Process* running_process = array[i];
			printf("%s\t\t%i", ID(running_process), COMPLETION_TIME(running_process));
			printf("\t\t%i", TURN_AROUND_TIME(running_process));
			printf("\t\t%i\n", WAIT_TIME(running_process));
		}
		render(trace_array);
	#endif

	#ifdef RUN_SJF
		register_key_compare(process_array, compare_arrival);
		
		Process* p1 = NewProcess(0, 2, 2, "P1 ");
		Process* p2 = NewProcess(0, 0, 1, "P2 ");
		Process* p3 = NewProcess(0, 2, 3, "P3 ");
		Process* p4 = NewProcess(0, 3, 5, "P4 ");
		Process* p5 = NewProcess(0, 2, 4, "P5 ");

		insert_process(p1, process_array);
		insert_process(p2, process_array);
		insert_process(p3, process_array);
		insert_process(p4, process_array);
		insert_process(p5, process_array);

		NonPreEmptiveScheduling(process_array, compare_burst);

		Process* array[] = {p1, p2, p3, p4, p5};

		printf("\nID\tCompletion time   Turn-around time  Waiting time\n");
		for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++){
			Process* running_process = array[i];
			printf("%s\t\t%i", ID(running_process), COMPLETION_TIME(running_process));
			printf("\t\t%i", TURN_AROUND_TIME(running_process));
			printf("\t\t%i\n", WAIT_TIME(running_process));
		}
		render(trace_array);
	#endif

	#ifdef RUN_NPE
		register_key_compare(process_array, compare_arrival);

		Process* p1 = NewProcess(2, 0, 5, "P1 ");
		Process* p2 = NewProcess(1, 2, 3, "P2 ");
		Process* p3 = NewProcess(3, 0, 4, "P3 ");

		insert_process(p1, process_array);
		insert_process(p2, process_array);
		insert_process(p3, process_array);

		NonPreEmptiveScheduling(process_array, compare_priority);

		Process* array[] = {p1, p2, p3};

		printf("\nID\tCompletion time   Turn-around time  Waiting time\n");
		for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++){
			Process* running_process = array[i];
			printf("%s\t\t%i", ID(running_process), COMPLETION_TIME(running_process));
			printf("\t\t%i", TURN_AROUND_TIME(running_process));
			printf("\t\t%i\n", WAIT_TIME(running_process));
		}
		render(trace_array);
	#endif

	#ifdef RUN_PE
		register_key_compare(process_array, compare_arrival);

	{
		Process* p1 = NewProcess(2, 0, 5, "P1 ");
		Process* p2 = NewProcess(1, 2, 3, "P2 ");

		insert_process(p1, process_array);
		insert_process(p2, process_array);

		PreEmptiveScheduling(process_array);

		Process* arr_p[] = {p1, p2};

		for(int i=0; i<sizeof(arr_p)/sizeof(arr_p[0]); i++){
			printf("%s-> Context Switch : %i, ", ID(arr_p[i]), arr_p[i]->N_context_switch);
			printf("Pre-emption : %i\n", arr_p[i]->N_preemption);
			printf("\n");
		}
		render(trace_array);		
	}

		//------------------------------------------------------------------------------------------------


	{
		Process* p1 = NewProcess(3, 0, 5, "P1 ");
		Process* p2 = NewProcess(2, 2, 4, "P2 ");
		Process* p3 = NewProcess(1, 5, 2, "P3 ");

		insert_process(p1, process_array);
		insert_process(p2, process_array);
		insert_process(p3, process_array);

		PreEmptiveScheduling(process_array);

		Process* arr[] = {p1, p2, p3};

		for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++){
			printf("%s-> Context Switch : %i, ", ID(arr[i]), arr[i]->N_context_switch);
			printf("Pre-emption : %i\n", arr[i]->N_preemption);
			printf("\n");
		}
		render(trace_array);		
	}
		
		//-----------------------------------------------------------------------------------------------------------
	
	{
		
		Process* p1 = NewProcess(2, 0, 5, "P1 ");
		Process* p2 = NewProcess(1, 2, 3, "P2 ");
		Process* p3 = NewProcess(3, 0, 4, "P3 ");

		insert_process(p1, process_array);
		insert_process(p2, process_array);
		insert_process(p3, process_array);

		PreEmptiveScheduling(process_array);

		Process* arr_p[] = {p1, p2, p3};

		for(int i=0; i<sizeof(arr_p)/sizeof(arr_p[0]); i++){
			printf("%s-> Context Switch : %i, ", ID(arr_p[i]), arr_p[i]->N_context_switch);
			printf("Pre-emption : %i\n", arr_p[i]->N_preemption);
			printf("\n");
		}
		render(trace_array);
	}

	#endif

	return 0;
}

