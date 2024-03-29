// ECE 485/585 Final Project

#include "queue.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <bitset>

using namespace std;


/*
 *	mapit(long long addr) - determines and maps the vals of each field 
 *							and returns a struct of type addmap the holds
 *							the fields: row, high col, BG, bank, and low col
 *							
 *	@param	long long addr - is the full hex address parsed from input file.
 */
struct addmap mapit(long long addr);
int queue_total(queue bg0, queue bg1, queue bg2, queue bg3); //

int main(int argc, char *argv[])
{
    char ifile_name[64];  //will hold the input file name
    char ofile_name[64];  //will hold the output file name
    int dflag=0;          //debugging flag. (default 0; debug mode off)

    //Checks the number of entered arguments
    if(argc<5){
        printf("Error: Missing argument(s)\n\tUse: -i <input_filename> -o <output_filename>\n\tUse: -d flag to enable debug mode\n");
        exit(-1);
    }
    else if(argc>6){
        printf("Error: Too many arguments\n\tUse: -i <input_filename> -o <output_filename>\n\tUse: -d flag to enable debug mode\n");
        exit(-1);
    }

    int i=0;  //loop index

    int iarg=0, oarg=0;  //used to check if -i and -o are present as arguments
    for(i=1; i<argc;i++){   //This loops check if '-i' and '-o' are present
        if (strcmp(argv[i],"-i")==0){
            iarg=1;
        }
        if (strcmp(argv[i],"-o")==0){
            oarg=1;
        }
    }

    if(iarg==0){
        printf("Error: Missing '-i <filename>' argument\n\tUse: -i <input_filename> -o <output_filename>\n\tUse: -d flag to enable debug mode\n");
        exit(-1);
    }
    if(oarg==0){
        printf("Error: Missing '-o <filename>' argument\n\tUse: -i <input_filename> -o <output_filename>\n\tUse: -d flag to enable debug mode\n");
        exit(-1);
    }


    for(i=1; i<argc; i++){
        //Checks for input file name
        if((strcmp(argv[i],"-i")==0)&& (i<(argc-1))){
            if((strcmp(argv[i+1],"-o")!=0)&&(strcmp(argv[i+1],"-d")!=0)){
                strcpy(ifile_name,argv[i+1]);
                i++;
            }
        }

        //Checks for output file name
        else if((strcmp(argv[i],"-o")==0)&& (i<(argc-1))){
            if((strcmp(argv[i+1],"-i")!=0)&&(strcmp(argv[i+1],"-d")!=0)){
                strcpy(ofile_name,argv[i+1]);
                i++;
            }
        }

        //Checks for Debugging flag
        else if(strcmp(argv[i],"-d")==0){
            dflag = 1;  //set debug mode ON; default OFF
        }

        else{
            printf("Error: Invalid or Missing argument(s) found\n\tUse: -i <input_filename> -o <output_filename>\n\tUse: -d flag to enable debug mode\n");
            exit(-1);
        }
    }

    //printf("input: %s\noutput: %s\ndflag: %d\n",ifile_name,ofile_name,dflag);
	
 /********************************-----------------------------------------------------------------------------********************************/
    queue bg0, bg1, bg2, bg3; // creates 4 queues for each bank group
    struct addmap temp;
    int current_time = 0; // time kept track in this function
    bool pendingRQ = false;
    int time_diff;
    FILE *ifp;       //input file pointer
    FILE *ofp;       //output file pointer
    int request_time=-1, op=-1;    //request_time will hold the time of an instruction and op will hold the type of instruction
    char cmd[64];           //Used in Switch/Case to determine the commands name (READ, WRITE, FETCH)
    long long addrs;    //addrs will hold the hexadecimal address value
	char buff[1024];

    ifp = fopen(ifile_name,"r");

    if(ifp==NULL){
        cout << "Error: Couldn't open input file\n" << endl;
        exit(-1);
    }
	
	ofp = fopen(ofile_name,"w");
	
	if(ofp==NULL){
        cout << "Error: Couldn't open output file\n" << endl;
		fclose(ifp);
        exit(-1);
    }

    //Do While() loop parses the inputs from a file (Cycle, Operation, and Address)
    do{
    	if((bg0.size() + bg1.size() + bg2.size() + bg3.size()) < 16) // if queues total not full
    	{
    		if(!pendingRQ)
    		{
        		fscanf(ifp,"%d %d 0x%llX", &request_time, &op, &addrs);
        		//if statement below checks the validity of operation digit.
       			if((op>2) || (op<0)){
        	    	printf("Error: Invalid Operation at Time %d\n", request_time);
       	    		fclose(ifp);
       	    		exit(-1);
        		}
        		//Determine the commands name (i.e. op=0 -> Data READ)
        		switch(op){
            		case 0: strcpy(cmd,"Data READ");
                	    break;
            		case 1: strcpy(cmd,"Data WRITE");
                	    break;
            		case 2: strcpy(cmd,"Instruction FETCH");
                	    break;
        		}
				temp = mapit(addrs);  //temp struct will acquire mapping vals with the function mapit()
				if(dflag==1){ //if debugging flag (-d) is present, then print parsed inputs.
            		printf("Time: %d\nOperation: %d (%s)\nAddress: 0x%09llX\n", request_time, op, cmd, addrs);
					printf("row: %d | Hi_col: %d | BG: %d | Bank: %d | Low_col: %d\n", temp.row, temp.hcol, temp.bg, temp.bank, temp.lcol);
				}
				pendingRQ = true;
			}
			if(pendingRQ)
			{
				if((bg0.size() + bg1.size() + bg2.size() + bg3.size()) == 0) {// all queues are empty
					current_time = request_time; //skip ahead in time
				}
				if(current_time >= request_time)
				{
					time_diff = current_time - request_time;//currently saved as CPU clocks..
					if(temp.bg == 0){
						bg0.add(request_time, time_diff, op, temp);
						pendingRQ = false;
					}
					else if(temp.bg == 1){
						bg1.add(request_time, time_diff, op, temp);
						pendingRQ = false;
					}
					else if(temp.bg == 2){
						bg2.add(request_time, time_diff, op, temp);
						pendingRQ = false;
					}
					else if(temp.bg == 3){
						bg3.add(request_time, time_diff, op, temp);
						pendingRQ = false;
					}
				}
			}
		}

		if(current_time % 2 == 0) //DRAMTick
		{
			//process_request(); sets queue status registers, writes out when time counts down
			if(bg0.size())//if size isn't 0
				bg0.update_time(); //adds one to each item in queue
			if(bg1.size())//if size isn't 0
				bg1.update_time(); //adds one to each item in queue
			if(bg2.size())//if size isn't 0
				bg2.update_time(); //adds one to each item in queue
			if(bg3.size())//if size isn't 0
				bg3.update_time(); //adds one to each item in queue
		}
		current_time++;
		//update timings bg0();
	}while(!feof(ifp) || pendingRQ); //|| (queue_total(bg0, bg1, bg2, bg3) != 0) //end of do while loop

    fclose(ifp); //close the input file
	fclose(ofp); //close the output file

	bg0.display_all();
	cout << "bg0 count: " << bg0.size() << endl;
	bg1.display_all();
	cout << "bg1 count: " << bg1.size() << endl;
	bg2.display_all();
	cout << "bg2 count: " << bg2.size() << endl;
	bg3.display_all();
	cout << "bg3 count: " << bg3.size() << endl;
    return 0;
}


/*
 *	mapit(long long addr) - determines and maps the vals of each field 
 *							and returns a struct of type addmap the holds
 *							the fields: row, high col, BG, bank, and low col
 *							
 *	@param	long long addr - is the full hex address parsed from input file.
 */
struct addmap mapit(long long addr){
	struct addmap mapped;
	mapped.row = ((addr >> 17));
	mapped.hcol = ((addr & 0x00001FC00) >> 10);
	mapped.bg = ((addr & 0x0000000C0) >> 6);
	mapped.bank = ((addr & 0x000000300) >> 8);
	mapped.lcol = ((addr & 0x000000038) >> 3);
	return mapped;
}