#ifndef MACROS
#define MACROS

#define BURST_TIME(process) process->info.burst_t
#define ARRIVAL_TIME(process) process->info.arrival_t
#define PRIORITY(process) process->info.priority
#define ID(process) process->info.id
#define STATE(process) process->info.state

#endif
