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
	int request_time, cmd, row, hcol, bg, bank, lcol; //from CPU
	int q_time; //
	node * next = NULL;
};

class queue
{
public:
	queue();
	void add(int request_time, int time_diff, int cmd, addmap & temp);
	void update_time();
	int size();
	void display_all();
	~queue();

private:
	node * head;
	int count = 0;
	int time_till_avail = 0;
	bool busy = false;
	bool precharged = false;
	int active_row;
	bool remove_all(node * & head);

};
