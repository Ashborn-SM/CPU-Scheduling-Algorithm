TARGET: exe

lib: lib/heap.c
	gcc -I lib/ -c lib/heap.c -o lib/heap.o

clean:
	rm lib/heap.o
