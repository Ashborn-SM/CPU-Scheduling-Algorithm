#include "trace.h"
#include <stdio.h>

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
    int idx = 0;
    while(trace_array[idx] != NULL){
        printf("|____|%i\n", trace_array[idx]->start_t);
        printf("|%s  | \n", trace_array[idx]->id);
        idx++;
    }
    printf("|____|%i\n", trace_array[idx-1]->end_t);
}

