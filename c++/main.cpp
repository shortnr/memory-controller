// ECE 485/585 Final Project

#include "queue.h"
#include <fstream>
//#include <string>

const int SIZE=20;

void read_in(queue & list);

int main(void)
{
	queue list;
	read_in(list);
	list.display_all();
	return 0;
}

void read_in(queue & list)
{
	char time[5];
	char cmd[2];
	char address[12];
	ifstream in;
	in.open("input.txt");
	if(in)
	{
		in.get(address, SIZE, '\n'); //used to prime the pump. first line isn't used
		while(in && !in.eof())
		{
			in.ignore(SIZE, '\n');
			in.get(time, 5, ' ');
			in.ignore(5, ' ');
			in.get(cmd, 2, ' ');
			in.ignore(2, ' ');
			in.get(address, 12, '\n');
			int itime = atoi(time);
			int icmd = atoi(cmd);
			list.add(itime, icmd, address);
		}
		in.close();
		in.clear();
	}
}
