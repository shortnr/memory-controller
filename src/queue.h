#include <iostream>
#include <stdio.h>
#include "bank.h"
#include "constants.h"
#include "datatypes.h"

using namespace std;

class Queue
{
public:
	// Constructor
	Queue();

	// Adds memory reference to queue
	void Add(reference * inRef);

	// Returns the size of the queue
	int Size();

	// Returns the request time of oldest reference in queue
	int request_time(); //return request time of head element/node

	// Displays all reference in queue; debug only
	void DisplayAll();

	// Determines oldest reference and issues all DRAM commands to
	// process that reference
	int process_request(int current_time, FILE* ofp,
											bool sameBankGroup, int timeSinceLastCommand);

	// Writes DRAM command out to output file
	void write_out(int time, int cmd, reference * request, FILE *ofp);

	// "Removes" a request from the queue
	void Remove(int referenceToDelete);

	// Destructor
	~Queue();// calls remove_all()

private:
	reference *head;
	Bank banks[4];
	int count = 0; //how many items in queue
	bool RemoveAll(reference * & head);
	int lastBankRef = -1;
};
