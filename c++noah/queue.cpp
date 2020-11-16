#include "queue.h"

//this is the constructor
queue::queue()
{
    head = NULL;
}

//this is the destructor
queue::~queue()
{
    if(remove_all(head));
}

//recursive remove all
bool queue::remove_all(node * & head)
{
    if(!head) return 0;
    bool value = remove_all(head->next);
    delete head;
    head = NULL;
    return value;
}

//used to check size of queue
int queue::size()
{
    int size = count;
    return size;
}

//adds one DIMM clock to each item in queue
//eventually will decrease time_till_avail by 1
void queue::update_time()
{
    node * current = head;
    while(current)
    {
        ++current->q_time;
        current = current->next;
    }
}

//adds item to end of list, plan on doing sorted insert
void queue::add(int request_time, int time_diff, int cmd, addmap & temp)
{
    if(head == NULL)
    {
        ++count;
        head = new node;
	    head->request_time = request_time;
        head->q_time = time_diff; 
	    head->cmd = cmd;
        head->row = temp.row;
        head->hcol = temp.hcol;
        head->bg = temp.bg;
        head->bank = temp.bank;
        head->lcol = temp.lcol;
	    head->next = NULL;
    }
    else
    {
        node * current = head;
        ++count;
        while(current->next != NULL){
            current = current->next;
        }
    	current->next = new node;
    	current = current->next;
	    current->request_time = request_time;
        current->q_time = time_diff; 
	    current->cmd = cmd;
        current->row = temp.row;
        current->hcol = temp.hcol;
        current->bg = temp.bg;
        current->bank = temp.bank;
        current->lcol = temp.lcol;
    	current->next = NULL;
    }
}

//used for debugging
void queue::display_all()
{
    node * temp = head;
    char cmd[64];           //Used in Switch/Case to determine the commands name (READ, WRITE, FETCH)
    cout << "\nBank Group " << temp->bg << "'s Queue contains:\n\n";
    while(temp != NULL)
    {
        //Determine the commands name (i.e. op=0 -> Data READ)
        switch(temp->cmd){
            case 0: strcpy(cmd,"Data READ");
                    break;
            case 1: strcpy(cmd,"Data WRITE");
                    break;
            case 2: strcpy(cmd,"Instruction FETCH");
                    break;
        }
        printf("request_time: %d CPU clocks\nTime in Queue: %d DIMM clocks\nOperation: %d (%s)\n",temp->request_time, temp->q_time, temp->cmd, cmd);
        printf("row: %d | Hi_col: %d | BG: %d | Bank: %d | Low_col: %d\n\n",temp->row, temp->hcol, temp->bg, temp->bank, temp->lcol);
        temp = temp->next;
    }
}
