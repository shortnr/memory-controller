#ifndef DATATYPES_H
#define DATATYPES_H

#include <iostream>

struct addmap{
	int row, hcol, bg, bank, lcol;
};

struct reference
{
	int requestTime, cmd, row, hcol, bg, bank, lcol; //from CPU
	int qTime; //how long has item been in queue in DIMM clocks
	bool processed = false;
	reference * next = NULL;
};

static char reqTypes[3][18] = {"Data READ", "Data WRITE", "Instruction FETCH"};

enum Command {ACT, PRE, RD, WR, REF};

#endif
