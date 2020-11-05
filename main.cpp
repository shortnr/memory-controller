#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

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

    FILE *ifp;       //input file pointer
    FILE *ofp;       //output file pointer
    int cycle=-1, op=-1;    //cycle will hold the time of an instruction and op will hold the type of instruction
    char cmd[64];           //Used in Switch/Case to determine the commands name (READ, WRITE, FETCH)
    unsigned long addrs;    //addrs will hold the hexadecimal address value

    ifp = fopen(ifile_name,"r");

    if(ifp==NULL){
        cout << "Error: Couldn't open input file\n" << endl;
        exit(-1);
    }

    //While() loop parses the inputs from a file (Cycle, Operation, and Address)
    while(fscanf(ifp,"%d %d %X",&cycle,&op,&addrs)!=EOF){
        //if statement below checks the validity of operation digit.
        if((op>2) || (op<0)){
            printf("Error: Invalid Operation at Time %d\n",cycle);
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

        if(dflag==1){ //if debugging flag (-d) is present, then print parsed inputs.
            printf("Time: %d\nOperation: %d (%s)\nAddress: 0x%08X\n\n",cycle,op,cmd,addrs);
        }

    }//end of while loop

    fclose(ifp); //close the input file
    return 0;
}
