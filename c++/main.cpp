// ECE 485/585 Final Project

#include "queue.h"
#include <fstream>

const int SIZE=20;

void read_in(char * line, queue list);

int main(void)
{
	char line[SIZE];
	queue list;
	read_in(line, list);
	list.display_all();
	return 0;
}

void read_in(char * line, queue list)
{
	ifstream in;
	in.open("input.txt");
	if(in)
	{
		in.get(line, SIZE, '\n'); //used to prime the pump. first line isn't used
		while(in && !in.eof())
		{
			in.ignore(SIZE, '\n');
			in.get(line, SIZE, '\n');
			list.add(line);
		}
		in.close();
		in.clear();
	}
}
