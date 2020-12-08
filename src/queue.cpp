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

    // Delete target and decrement count.
    current->processed = true;
    count -= 1;
}

// Returns the request time of the oldest request in the queue
int Queue::request_time() {
    if (!head) {
        return -1;
    }

    reference* current = head;

    // Traverse the queue
    while (current->processed==true) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    return current->requestTime;
}

// Processes the oldest request in the queue. Open page policy, only precharges
// and activates if request is to a different row.
int Queue::process_request(int current_time, FILE* ofp,
                           bool sameBankGroup, int timeSinceLastCommand) {
    reference* current = head;

    // Traverses queue until the oldest unserviced memory reference
    while (current->processed == true) {
        if (current->next == NULL) {
            return current_time;
            printf("\n----------------------EMPTY------------------------\n\n");
        }
        current = current->next;
    }

    int time = current_time;

    // Clear "precharged" flag if reference to different row
    if (banks[current->bank].activeRow!=-1) {
        if (banks[current->bank].activeRow != current->row) {
            banks[current->bank].precharged = false;
        }
    }

    // Precharges if necessary and outputs PRE command to output file
    if(banks[current->bank].precharged==false){
        if(time % 2 == 1) time += 1;
        write_out(time, PRE, current, ofp);
        time += 2 * (tRP);
        banks[current->bank].precharged = true;
    }

    // Activates new row if necessary and outputs ACT command to output file
    if(banks[current->bank].activeRow != current->row){
        if(time % 2 == 1) time += 1;
        write_out(time, ACT, current, ofp);
        time += 2 * (tRCD);
        banks[current->bank].activeRow = current->row;
    }

    // Outputs RD (for read or fetch), or WR (for write) command to the
    // output file
    if (current->cmd == 0) {  //if READ
        if(current->bank == lastBankRef) {
            if(!sameBankGroup && timeSinceLastCommand / 2 < tCCD_S) {
              // Reference to different BG; tCCD_S
              time += 2 * (tCCD_L - timeSinceLastCommand / 2);
            }
            else if (sameBankGroup && timeSinceLastCommand / 2 < tCCD_L) {
              // Reference to same BG; tCCD_L
              time += 2 * (tCCD_S - timeSinceLastCommand / 2);
            }
        }
        if(time % 2 == 1) time += 1;
        write_out(time, RD, current, ofp);
        time += 2 * (tCAS + 4);
    }
    else if (current->cmd == 1) { //if WRITE
        if(time % 2 == 1) time += 1;
        write_out(time, WR, current, ofp);
        time += 2 * (tCWD + 4);
    }
    else if (current->cmd == 2) { //if Instruction Fetch
      if(current->bank == lastBankRef) {
          if(!sameBankGroup && timeSinceLastCommand / 2 < tCCD_S) {
            // Reference to different BG; tCCD_S
            time += 2 * (tCCD_L - timeSinceLastCommand / 2);
          }
          else if (sameBankGroup && timeSinceLastCommand / 2 < tCCD_L) {
            // Reference to same BG; tCCD_L
            time += 2 * (tCCD_S - timeSinceLastCommand / 2);
          }
      }
        if(time % 2 == 1) time += 1;
        write_out(time, RD, current, ofp);
        time += 2 * (tCAS + 4);
    }
    lastBankRef = current->bank;
    return time;
}

// Writes DRAM command out to output file
void Queue::write_out(int time, int cmd, reference* request, FILE* ofp) {
    int column = (request->hcol << 3) + request->lcol;

    if (cmd == PRE) { //PRE
        fprintf(ofp, "%-6d PRE %X %X\n", time, request->bg, request->bank);
    }
    else if (cmd == ACT) { //ACT
        fprintf(ofp, "%-6d ACT %X %X %-4X\n", time, request->bg, request->bank, request->row);
    }
    else if (cmd == RD) { //RD
        fprintf(ofp, "%-6d RD  %X %X %-2X\n", time, request->bg, request->bank, request->hcol);
    }
    else if (cmd == WR) { //WR
        fprintf(ofp, "%-6d WR  %X %X %-2X\n", time, request->bg, request->bank, request->hcol);
    }
    else if (cmd == REF) { //REF
        fprintf(ofp, "REF\n");
    }
    return;
}
