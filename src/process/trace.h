#ifndef TRACE
#define TRACE

#include "macro.h"

typedef struct{
    char* id;
    int start_t;
    int end_t;
    int completion_time;
}Trace;

void print_box(Trace* trace);
void UpdateTrace(char* id, int start_t, int end_t, Trace* trace);
void UpdateTraceCTime(int completion_time, Trace* trace);
void render(Trace** trace_array);

#endif
