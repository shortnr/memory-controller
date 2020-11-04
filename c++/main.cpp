// ECE 485/585 Final Project

#include "queue.h"
#include <fstream>
#include <string>

const int SIZE=20;

void read_in(queue & list);

int main(void)
{
	queue list;
	read_in(list);
	//list.display_all();
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
			in.get(time, SIZE, ' ');
			in.ignore(SIZE, ' ');
			in.get(cmd, SIZE, ' ');
			in.ignore(SIZE, ' ');
			in.get(address, SIZE, '\n');
			int itime = atoi(time);
			cout << "Time: " << itime << endl;
			int icmd = atoi(cmd);
			if(icmd==0)
				cout << "op: Data READ\n";
			else if(icmd==1)
				cout << "op: Data WRITE\n";
			else if(icmd==2)
				cout << "op: Instruction FETCH\n";
			else
				cout << "Invalid op number " << icmd << endl;
			unsigned long iaddress = strtoul(address,0,16);
			cout << "Address: 0x" << iaddress << "\n\n";
			//list.add(itime, icmd, iaddress); adds to queue
		}
		in.close();
		in.clear();
	}
	else
		cout << "Could not open specified text document\n";
}
