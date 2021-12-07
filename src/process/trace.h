#ifndef TRACE
#define TRACE

#include "macro.h"

typedef struct{
    char* id;
    int start_t;
    int end_t;
}Trace;

void print_box(Trace* trace);
void UpdateTrace(char* id, int start_t, int end_t, Trace* trace);
void render(Trace** trace_array, int ttl_process);

#endif
