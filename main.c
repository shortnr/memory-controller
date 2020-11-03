#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

int main()
{
    FILE *fp;
    int cycle=-1;
    int op=-1;
    char addrs[1024];
    char buff[1024];
//    signed int addr= 0x10FF97000;
//
//    srand(time(NULL));

    fp = fopen("usr_inp.txt","r");

    if(fp==NULL){
        printf("Error: cannot open file\n");
        exit(-1);
    }

//    for(int i=0; i<40; i++){
//        fprintf(fp,"%d %d 0x%d%d%X\n",i+1,rand()%3,rand()%2,rand()%2,addr+i);
//    }

    for(int i=0; i<40; i++){
        fscanf(fp,"%s",buff);
        cycle = atoi(buff);
        printf("Time: %d\n",cycle);

        fscanf(fp,"%s",buff);
        op = atoi(buff);

        if(op==0){
            printf("op: Data READ\n");
        }
        else if(op==1){
            printf("op: Data WRITE\n");
        }
        else if(op==2){
            printf("op: Instruction FETCH\n");
        }

        fscanf(fp,"%s",buff);

        for(int j=0; j<strlen(buff); j++){
            addrs[j] = buff[j];
        }

        printf("Address: %s\n\n",addrs);
    }

    fclose(fp);
    return 0;
}
