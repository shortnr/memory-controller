#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;


struct node
{
	char * line;
	node * next = NULL;
};

class queue
{
public:
	queue();
	void add(char * line_in);
	void display_all();
	~queue();

private:
	node * head;
};