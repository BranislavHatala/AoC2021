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

#define MAX 4000
#define MAXCRABS 1200
#define MINX 0
#define MAXX 16

int ReadInput(int *numbers,int count);
int ReadDelimLine(int *numbers,int count,char *delim);
int CalcFuelCost(int crab, int destination);

FILE *g_fp;
char g_buff[MAX];

int main()
{
    int crabs[MAXCRABS];// crabs positions
    int cCount = 0;
    int fuelCost;
    int bestFuelCost = INT_MAX;
    int furthest = 0;

    g_fp = fopen("input.txt", "r");

    if(ReadInput(crabs,MAXCRABS))
    {
        printf("ERROR: reading first line failed");//in case I add error code in func return
    }

    for(int i = 0; i < MAXCRABS ; i++)//Find the furthest crab and count them
    {
        if(crabs[i]>furthest)
        {
            furthest = crabs[i];
        }
        if(crabs[i] == -1)
        {
            cCount = i;
            break;
        }
    }

    //iterate destinations, i is dstination
    for(int i = 1 ; i <= furthest ; i++ )
    {
        fuelCost = 0;
        //iterate crabs to sum fuel cost
        for(int j = 0; j < cCount ; j++)
        {
            fuelCost += CalcFuelCost(crabs[j], i);
        }
        if(bestFuelCost>fuelCost)//update best cost
        {
            bestFuelCost = fuelCost;
        }
    }


    printf("value: %d \n", bestFuelCost);
    return 0;
}

int CalcFuelCost(int crab, int destination)
{
    int steps = abs(crab - destination);
    int retval = 0;
    for(int i = 1 ; i <= steps ; i++ )//apply increasing fuel cost for each step
    {
        retval += i;
    }
    return retval;
}


int ReadInput(int *numbers,int count)
{
    char delim[2] = ",";
    ReadDelimLine(numbers, count, delim);
    fgets(g_buff, MAX, (FILE*)g_fp);//skip the empty line
    return 0;
}

int ReadDelimLine(int *numbers,int count,char *delim)
{
    char *gptr =  fgets(g_buff, MAX, (FILE*)g_fp);//get first line
    //extract array of called nums
    char* tok;
    tok = strtok(g_buff, delim);//get first token
    int retval = 0;
    if(gptr)
    {
        retval = 1;
    }
    // Checks for delimiter
   for(int i = 0 ; i<count ; i++)
   {
        if(tok != 0)//check if there is something
        {
            numbers[i] = atoi(tok);
        }
        else
        {
            numbers[i] = -1;//rest of array should indicate there is no valid number
        }

        // Get another one
        tok = strtok(0, delim);
    }
    return retval;
}
