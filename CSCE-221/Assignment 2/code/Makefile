# a simple makefile for compiling C++ files

# optimization is on
CC = c++
# for debuging use this 
#CC = c++ -g -O0

all: sort

sort: bubble-sort.o insertion-sort.o selection-sort.o shell-sort.o \
option.o sort.o radix-sort.o
	$(CC) -o sort bubble-sort.o insertion-sort.o selection-sort.o \
	       shell-sort.o option.o sort.o radix-sort.o

prog: prog.cpp
	$(CC) prog.cpp -o prog

option.o: option.h option.cpp
	$(CC) -c option.cpp

bubble-sort.o: sort.h bubble-sort.cpp
	$(CC) -c bubble-sort.cpp

insertion-sort.o: sort.h insertion-sort.cpp
	$(CC) -c insertion-sort.cpp

selection-sort.o: sort.h selection-sort.cpp
	$(CC) -c selection-sort.cpp

shell-sort.o: sort.h shell-sort.cpp
	$(CC) -c shell-sort.cpp

radix-sort.o: sort.h radix-sort.cpp
	$(CC) -c radix-sort.cpp

sort.o: sort.h option.h sort.cpp
	$(CC) -c sort.cpp

clean:
	/bin/rm -f *.o sort prog
