#include "constants.h"
#include "queue.h"

class Controller
{
public:
    Controller();
    bool IsEmpty();
    bool IsFull();
    void Add(int requestTime, int cmd, addmap & inRef);
    void ProcessRequests();
    void DisplayAll();

private:
    Queue bankGroups[4];
    char totalEnqueued;
};
