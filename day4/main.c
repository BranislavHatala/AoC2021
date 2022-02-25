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

#define MAX 200
#define DIGITMAX 4
#define NUMCOUNT 150
#define TABLEDIM 5
#define TABLESIZE 25

struct Table
{
    int table[TABLESIZE];//data of the table itself
    int count;//count of called numbers for this table to win
    int score;
};
//*****************global vars***************
FILE *g_fp;
char g_buff[MAX];

//******************functions prototypes********
int ReadNumbersCalled(int *numbers,int count);

int ReadDelimLine(int *numbers,int count,char *delim);

int ReadToTable(struct Table *tbl);

void printTable(struct Table *tbl);

void initTable(struct Table *tbl);

int testTableForWin(struct Table *tbl,int *numbers);

int main()
{
    int numbers[NUMCOUNT];

    struct Table table;
    initTable(&table);
    struct Table bestTable;
    initTable(&bestTable);

    g_fp = fopen("input.txt", "r");

    if(ReadNumbersCalled(numbers,NUMCOUNT))
    {
        printf("ERROR: reading first line failed");//in case I add error code in func return
    }

    while(ReadToTable(&table))
    {
        if((testTableForWin(&table,numbers) < bestTable.count))
        {
            bestTable = table;
        }
    }

    printf("value: %d \n", table.score);
    return 0;
}

//******************Find out if table wins and in which round, returns score if win, -1 if no win*************
int testTableForWin(struct Table *tbl,int *numbers)
{
    for(int i = 0 ; ; i++)//go through numbers, end is indicated by -1
    {
        //printTable(tbl);
        if(numbers[i] == -1)//check if it run out of numbers
        {
            break;
        }
        int at = -1; // index of number found
        for(int j = 0 ; j < TABLESIZE ; j++) // search for called out number in table
        {
            if(tbl->table[j] == numbers[i])
            {
                at = j;
                tbl->table[at] = -1;
                break;
            }
        }
        if(at == -1)//number not present, move to next
        {
            continue;
        }

        //check if whole row/col done
        int rowstart = (at/TABLEDIM)*TABLEDIM;
        int col = at%TABLEDIM;
        int win = 1; //board wins flag
        for(int j = 0 ; j < TABLEDIM ; j++)//check row
        {
            if(tbl->table[rowstart+j] != -1)//there is still a number left
            {
                win = 0;
                break;
            }
        }
        if(win == 0)//No success at row now is time to check collumn
        {
            for(int j = 0 ; j < TABLEDIM ; j++)//check collumn
            {
                if(tbl->table[col + (j*(TABLEDIM-1))] != -1)//there is still a number left
                {
                    win = 0;
                    break;
                }
            }
        }
        if(win == 1)//row or col is complete
        {
            int sum = 0;
            for(int j = 0 ; j < TABLESIZE ; j++)//count score
            {
                if(tbl->table[j] != -1)//there is still a number left
                {
                    sum += tbl->table[j];
                }
            }
            tbl->score = numbers[i] * sum;
            tbl->count = i;
            break;
        }
    }
    printf("count: %d ********************************************\n", tbl->count);
    return tbl->count;
}

void printTable(struct Table *tbl)
{
    for(int i = 0 ; i < TABLESIZE ; i++)
    {
        if((i%TABLEDIM) == 0)
        {
            printf("\n");
        }
        printf("%d ", tbl->table[i]);
    }
    printf("\n");
}

//******************Read talbe from input file, return zero if last table was read, otherwise 1***************
int ReadToTable(struct Table *tbl)
{
    int row[TABLEDIM];
    char delim[2] = " ";
    int retval = 0;
    for(int i = 0 ; i < TABLESIZE ; i++)
    {
        if((i%TABLEDIM) == 0)//check if begginning of a row
        {
            retval = ReadDelimLine(row, TABLEDIM, delim);
        }
        tbl->table[i] = row[i%TABLEDIM];
    }
    fgets(g_buff, MAX, (FILE*)g_fp);//skip the empty line
    return retval;
}

//*****************Init table to some neutral values****************
void initTable(struct Table *tbl)
{
    tbl->score = -1;
    tbl->count = INT_MAX;//this is not so nice shortcut
    for(int i = 0 ; i < TABLESIZE ; i++)
    {
        tbl->table[i] = 0;
    }
}

//***************Get first line into array of numbers and skips empty line after****************
int ReadNumbersCalled(int *numbers,int count)
{
    char delim[2] = ",";
    ReadDelimLine(numbers, count, delim);
    fgets(g_buff, MAX, (FILE*)g_fp);//skip the empty line
    return 0;
}

//******************reads row of delimited numbers and loads them into an int array, returns 1 if ok returns 0 if last line was read************
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
