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
    reference * current = head;
    reference* previous;
    bool found = false;

    // Traverse queue until target reference is found.
    while(current->requestTime != referenceToDelete) {
        //printf("Looking for request in queue...\n");
        if(current->next == NULL) break;
        previous = current;
        current = current->next;
    }

    // If target reference is not the last reference in the queue,
    // link previous reference to next reference, else NULL.
    //if (current->next != NULL) { 
    //    previous->next = current->next; 
    //}
    //else { 
    //    //previous = current->next;

    //}
    current->processed = true;

    // Delete target and decrement count.
    //delete current;
    count -= 1;
}

int Queue::request_time() {
    if (!head) {
        return -1; 
    }

    reference* current = head;

    while (current->processed==true) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }
    
    return current->requestTime;
}

int Queue::process_request(int current_time, FILE* ofp) {
    reference* current = head;

    while (current->processed == true) {
        if (current->next == NULL) {
            return current_time;
            printf("\n----------------------EMPTY------------------------\n\n");
        }
        current = current->next;
    }

    int time = current_time;

    if (banks[current->bank].activeRow!=-1) {
        if (banks[current->bank].activeRow != current->row) {
            banks[current->bank].precharged = false;
        }
    }

    if(banks[current->bank].precharged==false){
        time += 2 * (tRP);
        banks[current->bank].precharged = true;
        write_out(time, PRE, current, ofp);
    }

    if(banks[current->bank].activeRow != current->row){
        time += 2 * (tRCD);
        banks[current->bank].activeRow = current->row;
        write_out(time, ACT, current, ofp);
    }

    if (current->cmd == 0) {  //if READ
        time += 2 * (24 + 4);
        write_out(time, RD, current, ofp);
    }
    else if (current->cmd == 1) { //if WRITE
        time += 2 * (20 + 4);
        write_out(time, WR, current, ofp);
    }
    else if (current->cmd == 2) { //if Instruction Fetch
        time += 2 * (24 + 4);
        write_out(time, RD, current, ofp);
    }

    return time;


}

void Queue::write_out(int time, int cmd, reference* request, FILE* ofp) {
    if (cmd == PRE) { //PRE
        fprintf(ofp, "%d\tPRE %X %X\n", time, request->bg, request->bank);
    }
    else if (cmd == ACT) { //ACT
        fprintf(ofp, "%d\tACT %X %X %04X\n", time, request->bg, request->bank, request->row);
    }
    else if (cmd == RD) { //RD
        fprintf(ofp, "%d\tRD %X %X %02X\n", time, request->bg, request->bank, request->hcol);
    }
    else if (cmd == WR) { //WR
        fprintf(ofp, "%d\tWR %X %X %02X\n", time, request->bg, request->bank, request->hcol);
    }
    else if (cmd == REF) { //REF
        fprintf(ofp, "REF\n");
    }
    return;
}
