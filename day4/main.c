/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 200
#define DIGITMAX 4
#define NUMCOUNT 150
#define TABLEDIM 25
#define TABLESIZE 25

struct Table 
{
    int table[TABLESIZE];//data of the table itself
    int winRound;//count of called numbers for this table to win
};

int ReadToTable(struct Table *tbl);

int main()
{
    FILE *fp;
    char buff[MAX];
    char delim[2] = ",";
    int numbers[NUMCOUNT];
    
    

    struct Table BestTable;
    struct Table table;
    
    fp = fopen("input.txt", "r");
    
    //***************Get first line into array of numbers****************
    fgets(buff, MAX, (FILE*)fp);//get first line 
    //extract array of called nums
    char* tok;
    tok = strtok(buff, delim);//get first token
 
    // Checks for delimiter
   for(int i = 0 ; i<NUMCOUNT ; i++) 
   {
        if(tok != 0)//check if there is something
        {
            numbers[i] = atoi(tok);
        }
        else
        {
            numbers[i] = -1;
        }
        
        // Get another one
        tok = strtok(0, delim);
    }
    
    //***************Get table****************
    while(fgets(buff, MAX, (FILE*)fp)) //read and count ones on each bit
    {
        int count;
        count++;
        
    }
/*
    while(fgets(buff, MAX, (FILE*)fp)) //read and count ones on each bit
    {
        count++;
        for(int i = 0;i<BITS;i++)
        {
            if(buff[i] == '0')
            {
                onesCount[i]++;
            }
        }
    }
  */  
    
    //printf("value: %d \n", gamma * epsilon);
    return 0;
}


