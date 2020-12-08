#include <iostream>
#include <stdio.h>
#include "bank.h"
#include "constants.h"
#include "datatypes.h"

using namespace std;

class Queue
{
public:
	Queue();
	void Add(reference * inRef);
	void UpdateTime();
	int Size();
	int request_time(); //return request time of head element/node
	void DisplayAll();
	int process_request(int current_time, FILE* ofp,
											bool sameBankGroup, int timeSinceLastCommand);
	void write_out(int time, int cmd, reference * request, FILE *ofp);
	void Remove(int referenceToDelete);
	~Queue();// calls remove_all()

private:
	reference *head;
	Bank banks[4];
	int count = 0; //how many items in queue
	bool RemoveAll(reference * & head);
	int lastBankRef = -1;
};
