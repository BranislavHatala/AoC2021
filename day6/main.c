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
#include <limits.h>
#include <stdint.h>


#define MAX 1000
#define FISHSTATES 9
#define DAYS 256
#define SPAWNTIME 8
#define RESETTIME 6

int ReadInput(uint64_t *fstates,int count);
int ReadDelimLine(uint64_t *fstates,int count,char *delim);

FILE *g_fp;
char g_buff[MAX];

int main()
{
    uint64_t fstates[FISHSTATES] = {0}; //states of fish, each fiel is count of fish where i is state, "Markov" based approach
    uint64_t fCount = 0;

    g_fp = fopen("input.txt", "r");

    if(ReadInput(fstates,MAX))
    {
        printf("ERROR: reading first line failed");//in case I add error code in func return
    }

    //simulate
    for(int i = 1 ; i <= DAYS ; i++ )
    {
        uint64_t temp = fstates[0];// fish ready to spawn fish

        for(int i = 1 ; i < FISHSTATES ; i++)//shift states lower
        {
            fstates[i-1] = fstates[i];
            fstates[i] = 0;
        }
        fstates[SPAWNTIME] += temp;// fish are spawned
        fstates[RESETTIME] += temp;// fish are reset;
        temp = 0;
    }

    //count fish
    for(int i = 0 ; i < FISHSTATES ; i++)
    {
        fCount += fstates[i];
        printf("value: %lld \n", fstates[i]);
    }

    uint64_t i = 0;
    i--;
    printf("value: %llu \n", i);
    printf("value: %lld \n", fCount);
    return 0;
}

int ReadInput(uint64_t *fstates,int count)
{
    char delim[2] = ",";
    ReadDelimLine(fstates, count, delim);
    fgets(g_buff, MAX, (FILE*)g_fp);//skip the empty line
    return 0;
}

int ReadDelimLine(uint64_t *fstates,int count,char *delim)
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
            fstates[atoi(tok)]++;
        }


        // Get another one
        tok = strtok(0, delim);
    }
    return retval;
}
