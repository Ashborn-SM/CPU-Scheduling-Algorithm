#include "trace.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void UpdateTrace(char* id, int start_t, int end_t, Trace* trace){

    trace->id = id;
    if(start_t != -1){
        trace->start_t = start_t;
    }
    if(end_t != -1){
        trace->end_t = end_t;
    }
}

void render(Trace** trace_array){
    int idx = 0, start_t = 0, end_t = 0;
    char* id;
    // Trace
    while(trace_array[idx] != NULL){
        id = trace_array[idx]->id;
        start_t= trace_array[idx]->start_t;
        end_t = trace_array[idx]->end_t;

        printf("|_____|%i\n", start_t);
        printf("|%s  |\n", id);
        idx++;
    }
    printf("|_____|%i\n", end_t);
}

