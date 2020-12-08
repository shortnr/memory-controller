// ECE 485/585 Final Project

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <bitset>
#include <stdio.h>
#include "controller.h"
#include "constants.h"

using namespace std;

// Function prototypes.
struct addmap mapit(long long addr);

int main(int argc, char *argv[])
{
  // Variables to handle arguments and file I/O.
  char iFileName[64];    // will hold the input file name
  char oFileName[64];    // will hold the output file name
  bool dFlag = false;     //
  bool iFlag = false;     // argument flags
  bool oFlag = false;     //
  FILE *ifp;       //input file pointer
  FILE *ofp;       //output file pointer

  // This loop checks if '-i', '-o', and '-d' are present.
  for(int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0) {
      if ((strcmp(argv[i + 1], "-o") != 0) && (strcmp(argv[i + 1], "-d") != 0)) {
        strcpy(iFileName, argv[i + 1]);
        iFlag = true;
      }
    }
    if (strcmp(argv[i], "-o") == 0) {
      if ((strcmp(argv[i + 1], "-i") != 0) && (strcmp(argv[i + 1], "-d") != 0)) {
        strcpy(oFileName, argv[i + 1]);
        oFlag = true;
      }
    }
    if (strcmp(argv[i], "-d") == 0) dFlag = true;
  }

  // Checks if all arguments are valid. Exit with error if not.
  if (argc < 5 || argc > 6 || !iFlag || !oFlag || (argc % 2 == 0 && !dFlag)) {
    printf("Error: Invalid arguments.\n\tUse: -i <input_filename> "
    "-o <output_filename>\n\tUse: -d flag to enable debug mode\n");
    exit(-1);
  }

  // Open input file. Error and exit on fail.
  if((ifp = fopen(iFileName,"r")) == NULL) {
    cout << "Error: Couldn't open input file\n" << endl;
    exit(-1);
  }

  // Open output file. Error and exit on fail.
  if((ofp = fopen(oFileName,"w")) == NULL) {
    cout << "Error: Couldn't open output file\n" << endl;
    fclose(ifp);
    exit(-1);
  }

  //
  //  "Business end" of main. Declare variables associated with memory
  //  controller logic. Loops, receiving requests in at correct CPU time
  //  (or nearest DRAM time) until queue is full. Processes memory
  //  requests in tandem with receiving requests.
  //
  Controller controller;
  addmap temp;     // Address mapping struct.
  int currentTime = 0;    // Current time in CPU clocks.
  int totalEnqueued = 0;  // Total requests in all queues.
  bool pendingRQ = false; // Is there a request waiting?
  int requestTime = -1;   // Time request was issued.
  int op = -1;            // Type of request (read/write/fetch)
  long long addrs;        // Hexidecimal address of request.
  int args = 0;           // Determines # of arguments read from a line in input file

  //Do While() loop parses the inputs from a file (Cycle, Operation, and Address)
  do{
    if(!controller.IsFull()) // if queues total not full
    {
      if(!pendingRQ)
      {
        args = fscanf(ifp,"%d %d 0x%llX", &requestTime, &op, &addrs);
        if (args < 0) { //EOF
          exit(-1);
        }

        //if statement below checks the validity of operation digit.
        if( op>2 || op<0) {
          printf("Error: Invalid Operation at Time %d\n", requestTime);
          fclose(ifp);
          exit(-1);
        }

        temp = mapit(addrs);  //temp struct will acquire mapping vals with the function mapit()
        if(dFlag) {           //if debugging flag (-d) is present, then print parsed inputs.
          printf("Time: %d\nOperation: %d (%s)\nAddress: 0x%09llX\n", requestTime, op, reqTypes[op], addrs);
          printf("row: %d | Hi_col: %d | BG: %d | Bank: %d | Low_col: %d\n\n", temp.row, temp.hcol, temp.bg, temp.bank, temp.lcol);
        }

        pendingRQ = true;

      }
      if(pendingRQ)
      {
        if((controller.IsEmpty())&&(requestTime>currentTime)) {// all queues are empty
          currentTime = requestTime; //skip ahead in time
        }
        if(currentTime >= requestTime)
        {
          controller.Add(requestTime, op, temp);
          pendingRQ = false;
          currentTime = controller.ProcessRequests(currentTime, ofp);
        }
      }
    }

    if(currentTime % 2 == 0) //DRAMTick
    {
      controller.updateQ(); //update q_time of each bank group's queue
    }

    currentTime++;
  } while(!feof(ifp) || pendingRQ); // end of do while loop

  fclose(ifp); //close the input file
  fclose(ofp); //close the output file
  fclose(stdin);
  fclose(stdout);
  fclose(stderr);
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
