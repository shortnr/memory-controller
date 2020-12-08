#include "constants.h"
#include "queue.h"

class Controller
{
public:
    Controller();
    bool IsEmpty();
    bool IsFull();
    void Add(int requestTime, int cmd, addmap & inRef);
    int ProcessRequests(int current_time, FILE *ofp);
    void updateQ();
    void DisplayAll();

private:
    Queue bankGroups[4];
    char totalEnqueued;
    int lastCommandTime;
    int lastBank, lastBankGroup;
};
