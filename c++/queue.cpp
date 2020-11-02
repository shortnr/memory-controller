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

void queue::add(char * line_in)
{
	if(head == NULL)
	{
		head = new node;
		head->line = new char[strlen(line_in) + 1];
		strcpy(head->line, line_in);
		head->next = NULL;
        cout << "head: " << head->line << "\n" ;
	}
	else
	{
		node * current = head;
   		while(current->next != NULL)
        	current = current->next;
    	current->next = new node;
    	current = current->next;
    	current->line = new char[strlen(line_in) + 1];
    	strcpy(current->line, line_in);
    	current->next = NULL;
        cout << "else: " << current->line << "\n";
	}
}
void queue::display_all()
{
    cout << "in display_all\n";
    node temp = head;
    if(temp == NULL)
        cout << "temp is null\n";
    int x = 0;
    while(temp != NULL)
    {
        cout << x << "\t" << temp->line << "\n";
        ++x;
        temp = temp->next;
    }
}