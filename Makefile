CC = g++
CFLAGS = -c -Wall

PJ3: PJ3.o graph.o heap.o
PJ3.o: PJ3.cpp graph.o graph.h data_structures.h
graph.o: graph.cpp graph.h heap.h data_structures.h
heap.o: heap.h heap.cpp data_structures.h
.PHONY: clean
clean	:
	rm -f  *.o PJ3
.PHONY: all
all: clean PJ3
