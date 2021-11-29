TARGET: exe

CFLAGS=-c -Wall -g3

#PATH
PROCESS_PATH=./process
ALGORITHM_PATH=./Algorithm
LIB_PATH=../lib

#INCLUDE_LIB
INCLUDE_PRE-EMPTIVE=-I./ -I$(LIB_PATH) 
INCLUDE_MAIN=-I$(ALGORITHM_PATH) $(INCLUDE_PRE-EMPTIVE)

OBJ_EXE=main.o pre-emptive-scheduling.o lib.o process.o

lib.o: $(LIB_PATH)/heap.c
	$(CC) -I$(LIB_PATH) $(CFLAGS) $< -o $@

process.o: $(PROCESS_PATH)/process.c
	$(CC) -I./ $(CFLAGS) $< -o $@

pre-emptive-scheduling.o: $(ALGORITHM_PATH)/Pre-emptive-Scheduling/pre-emptive-scheduling.c
	$(CC) $(INCLUDE_PRE-EMPTIVE) $(CFLAGS) $< -o $@

main.o: main.c 
	$(CC) $(INCLUDE_MAIN) $(CFLAGS) $< -o $@
	
exe: $(OBJ_EXE)
	$(CC) $^ -o $@

debug: $(OBJ_EXE)
	$(CC) $^ -o exe

clean:
	rm *.o exe
