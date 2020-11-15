CC = g++
CFLAGS = -g -std=c++11
LDFLAGS = -lm

memcon: main.o queue.o
	$(CC) $(LDFLAGS) -o memcon main.o queue.o
main.o: main.cpp
	$(CC) $(CFLAGS)  -c main.cpp
queue.o: queue.cpp queue.h
	$(CC) $(CFLAGS)  -c queue.cpp
