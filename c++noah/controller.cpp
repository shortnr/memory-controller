#include "controller.h"

Controller::Controller()
{
    for(int i = 0; i < 4; i++) {
        bankGroups[i] = Queue();
    }

    totalEnqueued = 0;
}

void Controller::Add(int requestTime, int cmd, addmap & inRef)
{
    reference * newReference = new reference;
    newReference->requestTime = requestTime;
    newReference->qTime = 0;
    newReference->cmd = cmd;
    newReference->row = inRef.row;
    newReference->hcol = inRef.hcol;
    newReference->bg = inRef.bg;
    newReference->bank = inRef.bank;
    newReference->lcol = inRef.lcol;
    newReference->next = NULL;

    bankGroups[newReference->bg].Add(newReference);
}

void Controller::ProcessRequests()
{
    totalEnqueued = 0;
    for(int i = 0; i < 4; i++) {
        totalEnqueued += bankGroups[i].Size();
        if(bankGroups[i].Size()) bankGroups[i].UpdateTime();
    }
}

bool Controller::IsEmpty()
{
    return (totalEnqueued == 0);
}

bool Controller::IsFull()
{
    return (totalEnqueued == CONTROLLER_CAPACITY);
}

void Controller::DisplayAll()
{
    for(int i = 0; i < 4; i++) {
        bankGroups[i].DisplayAll();
        std::cout << "bg" << i << " count: " << bankGroups[i].Size() << endl;
    }
}
