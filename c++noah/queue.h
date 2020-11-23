#include <iostream>
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
	void DisplayAll();
	void Remove(int referenceToDelete);
	~Queue();// calls remove_all()

private:
	reference *head;
	Bank banks[4];
	int count = 0; //how many items in queue
	bool RemoveAll(reference * & head);
};
