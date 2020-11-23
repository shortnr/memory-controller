#include "queue.h"

//this is the constructor
Queue::Queue()
{
    head = NULL;

    // Initializes banks:
    //    prechaged, idle, no active row, last command PRE, timeUntilAvail = 0
    for(int i = 0; i < 4; i++){
        banks[i] = Bank();
    }
}

//this is the destructor
Queue::~Queue()
{
    RemoveAll(head);
}

//recursive remove all
bool Queue::RemoveAll(reference * & head)
{
    if(!head) return 0;
    bool value = RemoveAll(head->next);
    delete head;
    head = NULL;
    return value;
}

//used to check size of queue
int Queue::Size()
{
    return count;
}

//adds one DIMM clock to each item in queue
//eventually will decrease time_till_avail by 1
void Queue::UpdateTime()
{
    reference * current = head;
    while(current)
    {
        ++current->qTime;
        current = current->next;
    }
}

//adds item to end of list, plan on doing sorted insert
void Queue::Add(reference * inRef)
{
    if(head == NULL) head = inRef;
    else {
        reference * current = head;

        while(current->next != NULL){
            current = current->next;
        }
    	current->next = inRef;
    }

    count++;
}

//used for debugging
void Queue::DisplayAll()
{
    reference * temp = head;

    cout << "\nBank Group " << temp->bg << "'s Queue contains:\n\n";
    while(temp != NULL)
    {
        printf("requestTime: %d CPU clocks\nTime in Queue: %d DIMM clocks\nOperation: %d (%s)\n",temp->requestTime, temp->qTime, temp->cmd, reqTypes[temp->cmd]);
        printf("row: %d | Hi_col: %d | BG: %d | Bank: %d | Low_col: %d\n\n",temp->row, temp->hcol, temp->bg, temp->bank, temp->lcol);
        temp = temp->next;
    }
}

// Traverses the queue, deleting the target reference.
void Queue::Remove(int referenceToDelete) {
    reference * previous;
    reference * current = head;
    bool found = false;

    // Traverse queue until target reference is found.
    while(current->requestTime != referenceToDelete) {
        if(current->next == NULL) break;
        previous = current;
        current = current->next;
    }

    // If target reference is not the last reference in the queue,
    // link previous reference to next reference, else NULL.
    if(current->next != NULL) previous->next = current->next;
    else previous->next = NULL;

    // Delete target and decrement count.
    delete current;
    count -= 1;
}
