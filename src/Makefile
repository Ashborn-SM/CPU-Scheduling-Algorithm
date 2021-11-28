TARGET: exe

CFLAGS=-c -Wall
CURRENT_DIR=.
PRE-EMPTIVE_PATH=Algorithm/Pre-emptive-Scheduling
LIB_PATH=../
INCLUDE_ALL_HEADER_PATH=-I$(CURRENT_DIR) -I$(LIB_PATH) -I$(PRE-EMPTIVE_PATH)

lib.o: $(LIB_PATH)/heap.c
	$(CC) -I$(LIB_PATH) $(CFLAGS) $< -o $(LIB_PATH)/$@

pre-emptive-scheduling.o: $(PRE-EMPTIVE_PATH)/pre-emptive-scheduling.c
	$(CC) $(INCLUDE_ALL_HEADER_PATH) $(CFLAGS) $< -o $(PRE-EMPTIVE_PATH)/$@

main.o: main.c
	$(CC) $(INCLUDE_ALL_HEADER_PATH) $(CFLAGS) $< -o $@

clean:
	rm main.o
	rm $(LIB_PATH)/heap.o
	rm $(PRE-EMPTIVE_PATH)/pre-emptive-scheduling.o
