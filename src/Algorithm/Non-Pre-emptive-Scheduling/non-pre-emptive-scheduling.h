#ifndef NON_PRE_EMPTIVE
#define NON_PRE_EMPTIVE

#include "p_array.h"
#include "macro.h"
#include "process/trace.h"
#include "process/process.h"

void NonPreEmptiveScheduling(P_Array* ProcessHeap, int (*compare)(void*, void*));

#endif
