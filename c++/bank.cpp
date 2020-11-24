#include "bank.h"

Bank::Bank()
{
    precharged = true;
    busy = false;
    activeRow = -1;
    timeUntilAvail = 0;
    lastCommand = PRE;
}

bool Bank::IsAvailable()
{
    return !busy;
}

void Bank::TimeStep()
{
    if(timeUntilAvail > 0) timeUntilAvail--;
    else busy = false;
}
