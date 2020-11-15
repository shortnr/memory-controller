#include "queue.h"

//this is the constructor
queue::queue()
{
    head = NULL;
}

//this is the destructor
queue::~queue()
{
    node * current;
    while(head)
    {
        current = head->next;
        delete head;
        head = current;
    }
}

int queue::size()
{
    int size = count;
    return size;
}

void queue::add(int time, int cmd, addmap & temp)
{
    if(head == NULL)
    {
        cout << "head == NULL\n\n";
        ++count;
        head = new node;
	    head->time = time;
	    head->cmd = cmd;
        head->row = temp.row;
        head->hcol = temp.hcol;
        head->bg = temp.bg;
        head->bank = temp.bank;
        head->lcol = temp.lcol;
	    head->next = NULL;
        cout << "now that head has been updated, these are its fields\n";
        printf("Time: %d\nOperation: %d\n",head->time, head->cmd);
        printf("row: %d | Hi_col: %d | BG: %d | Bank: %d | Low_col: %d\n\n", head->row, head->hcol, head->bg, head->bank, head->lcol);
    }
    else
    {
        node * x = head;
        cout << "Lets check on head again\n";
        printf("Time: %d\nOperation: %d\n",x->time, x->cmd);
        printf("row: %d | Hi_col: %d | BG: %d | Bank: %d | Low_col: %d\n\n", x->row, x->hcol, x->bg, x->bank, x->lcol);
        ++count;
        while(x->next != NULL){
            cout << "traversal\n";
            x = x->next;
        }
    	x->next = new node;
    	x = x->next;
	    x->time = time;
	    x->cmd = cmd;
        x->row = temp.row;
        x->hcol = temp.hcol;
        x->bg = temp.bg;
        x->bank = temp.bank;
        x->lcol = temp.lcol;
    	x->next = NULL;
    }
}

void queue::display_all()
{
    node * temp = head;
    char cmd[64];           //Used in Switch/Case to determine the commands name (READ, WRITE, FETCH)
    cout << "\nBank Group " << temp->bg << "'s Queue contains:\n";
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
        printf("Time: %d\nOperation: %d (%s)\n",temp->time, temp->cmd, cmd);
        printf("row: %d | Hi_col: %d | BG: %d | Bank: %d | Low_col: %d\n\n",temp->row, temp->hcol, temp->bg, temp->bank, temp->lcol);
        temp = temp->next;
    }
}
