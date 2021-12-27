#ifndef MACROS
#define MACROS

#define BURST_TIME(process) process->info.burst_t
#define ARRIVAL_TIME(process) process->info.arrival_t
#define PRIORITY(process) process->info.priority
#define ID(process) process->info.id
#define STATE(process) process->info.state
#define COMPLETION_TIME(process) process->info.completion_time
#define TURN_AROUND_TIME(process) process->info.turn_around_time
#define WAIT_TIME(process) process->info.wait_time

#endif
