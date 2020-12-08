CC = g++
CFLAGS = -g -std=c++11
LDFLAGS = -lm

memcon: main.o controller.o queue.o bank.o
	$(CC) $(LDFLAGS) -o memcon main.o controller.o queue.o bank.o
remake: clean memcon
main.o: main.cpp
	$(CC) $(CFLAGS)  -c main.cpp
controller.o: controller.cpp controller.h queue.h
	$(CC) $(CFLAGS)  -c controller.cpp
queue.o: queue.cpp queue.h
	$(CC) $(CFLAGS)  -c queue.cpp
bank.o: bank.cpp bank.h
	$(CC) $(CFLAGS)  -c bank.cpp
clean:
	rm *.o memcon

