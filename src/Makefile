TARGET: exe

RUN = 
MACRO=RUN_$(RUN)

#FLAGS
CFLAGS=-c -Wall
DFLAGS=-g3

#PATH
PROCESS_PATH=./process
ALGORITHM_PATH=./Algorithm
LIB_PATH=../lib

#INCLUDE_LIB
INCLUDE_ALGORITHM=-I./ -I$(LIB_PATH)
INCLUDE_MAIN=-I$(ALGORITHM_PATH) -I$(LIB_PATH) -I./

OBJ_EXE = lib.o process.o trace.o fcfs.o main.o pre-emptive-scheduling.o non-pre-emptive-scheduling.o

#BUILD
lib.o: $(LIB_PATH)/p_array.c
	$(CC) -I$(LIB_PATH) $(CFLAGS) $< -o $@

process.o: $(PROCESS_PATH)/process.c
	$(CC) -I./ -I$(LIB_PATH) $(CFLAGS) $< -o $@

trace.o: $(PROCESS_PATH)/trace.c
	$(CC) -I./ $(CFLAGS) $< -o $@

main.o: main.c
	$(CC) $(INCLUDE_MAIN) $(CFLAGS) $< -D $(MACRO) -o $@

exe: $(OBJ_EXE)
	$(CC) $^ -o $@
	./exe

#CPU-SCHEDULING ALGORITHM
pre-emptive-scheduling.o: $(ALGORITHM_PATH)/Pre-emptive-Scheduling/pre-emptive-scheduling.c
	$(CC) $(INCLUDE_ALGORITHM) $(CFLAGS) $< -o $@

fcfs.o: $(ALGORITHM_PATH)/FCFS/fcfs.c
	$(CC) $(INCLUDE_ALGORITHM) $(CFLAGS) $< -o $@

non-pre-emptive-scheduling.o: $(ALGORITHM_PATH)/Non-Pre-emptive-Scheduling/non-pre-emptive-scheduling.c
	$(CC) $(INCLUDE_ALGORITHM) $(CFLAGS) $< -o $@

#DEBUG
debug: CFLAGS+=$(DFLAGS)
debug: exe

#CLEAR 
c:
	rm *.o exe
cm:
	rm main.o
