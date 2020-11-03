#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;


struct node
{
	int time;
	int cmd;
	char * address;
	node * next = NULL;
};

class queue
{
public:
	queue();
	void add(int time, int cmd, char * address);
	void display_all();
	~queue();

private:
	node * head;
};
