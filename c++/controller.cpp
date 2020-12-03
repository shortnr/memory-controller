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

int Controller::ProcessRequests(int current_time, FILE* ofp)
{

    int req_times[4];
    int temp = 0;
    int currentTime = current_time;
    int item = 0;
    int i = 0;

    for (i = 0;i < 4;i++) {  //obtains request times of head-node requests
        req_times[i] = bankGroups[i].request_time();
        if (req_times[i] > -1) {
            temp = req_times[i];
        }
    }

    for (i = 0;i < 4;i++) { //checks which has the min request time
        if ((req_times[i] > -1) && (req_times[i] <= temp)) {
            temp = req_times[i];
            item = i;
        }
    }
    //printf("temp: %d\n\n", temp);
    currentTime = bankGroups[item].process_request(currentTime, ofp);

    fprintf(ofp, "\n");

    bankGroups[item].Remove(temp);

    return currentTime;
   
}

void Controller::updateQ() 
{
    totalEnqueued = 0;
    for (int i = 0; i < 4; i++) {
        totalEnqueued += bankGroups[i].Size();
        if (bankGroups[i].Size()) bankGroups[i].UpdateTime();
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
