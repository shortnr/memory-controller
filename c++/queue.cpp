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

void queue::add(int time, int cmd, unsigned long address)
{
    if(head == NULL)
    {
        head = new node;
	    head->time = time;
	    head->cmd = cmd;
        head->address = address;
	    head->next = NULL;
    }
    else
    {
        node * current = head;
        while(current->next != NULL)
            current = current->next;
    	current->next = new node;
    	current = current->next;
	    current->time = time;
	    current->cmd = cmd;
    	current->address = address;
    	current->next = NULL;
    }
}

void queue::display_all()
{
    node * temp = head;
    cout << "display all function\n";
    while(temp != NULL)
    {
        cout << "time: " << temp->time << " cmd: " << temp->cmd << " address: " << temp->address << "\n";
        temp = temp->next;
    }
}
