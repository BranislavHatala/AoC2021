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

#define MAX 1000
#define BITS 12 //bit width of each entry
#define MAXFISH 900000
#define DAYS 80
#define SPAWNTIME 8
#define RESETTIME 6

int ReadInput(char *numbers,int count);
int ReadDelimLine(char *numbers,int count,char *delim);

FILE *g_fp;
char g_buff[MAX];

int main()
{
    char fish[MAXFISH];// fish timers array
    int fCount = 0;

    g_fp = fopen("input.txt", "r");

    if(ReadInput(fish,MAXFISH))
    {
        printf("ERROR: reading first line failed");//in case I add error code in func return
    }

    for(int i = 0; i < MAXFISH ; i++)//Count starting fish
    {
        if(fish[i] == -1)
        {
            fCount = i;
            break;
        }
    }

    //Print initial state
    printf("Initial state: ", fCount);
    for(int i = 0; i < (fCount-1) ; i++)
    {
        printf("%d,", fish[i]);
    }
    printf("%d\n", fish[(fCount-1)]);

    //simulate
    for(int i = 1 ; i <= DAYS ; i++ )
    {
        int j = fCount - 1;
        for(; j >= 0 ; j--)//go through fish
        {
            if(fish[j] == 0)
            {
                if(fCount < MAXFISH)
                {
                    fish[fCount] = SPAWNTIME;
                    fish[j] = RESETTIME;
                    fCount++;
                }
                else
                {
                    printf("ERROR: Too many fish in the sea.\n");
                }
            }
            else
            {
                fish[j]--;
            }
        }

        //print
        /*
        printf("day %d state:   ", i);
        for(int j = 0; j < (fCount-1) ; j++)
        {
            printf("%d,", fish[j]);
        }
        printf("%d\n", fish[(fCount-1)]);
        */

    }


    printf("value: %d \n", fCount);
    return 0;
}

int ReadInput(char *numbers,int count)
{
    char delim[2] = ",";
    ReadDelimLine(numbers, count, delim);
    fgets(g_buff, MAX, (FILE*)g_fp);//skip the empty line
    return 0;
}

int ReadDelimLine(char *numbers,int count,char *delim)
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
