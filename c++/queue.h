#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

/*
 * Struct addmap used to hold the mapped vals from a hex address.
 * Struct type used by function to return an addmap struct with mapped vals.
*/
struct addmap{
	int row, hcol, bg, bank, lcol;
};

struct node
{
	int time, cmd;
	int row, hcol, bg, bank, lcol;
	node * next = NULL;
};

class queue
{
public:
	queue();
	void add(int time, int cmd, addmap & temp);
	int size();
	void display_all();
	~queue();

private:
	node * head;
	int count = 0;
};
