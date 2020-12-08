#include "constants.h"
#include "queue.h"

class Controller
{
public:
    // Constructor
    Controller();

    bool IsEmpty();
    bool IsFull();

    // Adds a memory reference to the controller queue
    void Add(int requestTime, int cmd, addmap & inRef);

    // Determines the next DRAM operation and outputs to file
    int ProcessRequests(int current_time, FILE *ofp);

    // Updates the size of the queue
    void updateQ();

    // Displays all reference in queue in debug mode
    void DisplayAll();

private:
    Queue bankGroups[4];
    char totalEnqueued;
    int lastCommandTime;
    int lastBank, lastBankGroup;
};
