#include "constants.h"
#include "datatypes.h"

class Bank
{
public:
    Bank();
    bool IsAvailable();
    void TimeStep();

private:
    bool precharged, busy;
    int activeRow, timeUntilAvail;
    Command lastCommand;
};
