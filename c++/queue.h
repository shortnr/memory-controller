#include <iostream>
#include <cstring>
#include <cctype>
#include <stdio.h>
using namespace std;

#define PRE 0
#define ACT 1
#define RD 2
#define WR 3
#define REF 4

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
	int q_time; //how long has item been in queue in DIMM clocks
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
	void remove_req(node * req);
	~queue();// calls remove_all()

//private:
	node * head;
	int count = 0; //how many items in queue
	int time_till_avail = 0;//will be used in process_request()
	bool busy = false;//will be used in process_request()
	bool precharged = false;//will be used in process_request()
	int active_row=-1;//will be used in process_request()
	bool remove_all(node * head);

};
