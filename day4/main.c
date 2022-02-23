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
#define TABLEDIM 5
#define TABLESIZE 25

struct Table
{
    int table[TABLESIZE];//data of the table itself
    int score;//count of called numbers for this table to win
};
//*****************global vars***************
FILE *g_fp;
char g_buff[MAX];

//******************functions prototypes********
int ReadNumbersCalled(int *numbers,int count);

int ReadDelimLine(int *numbers,int count,char *delim);

int ReadToTable(struct Table *tbl);

void initTable(struct Table *tbl);

int testTableForWin(struct Table *tbl,int *numbers);

int main()
{
    int numbers[NUMCOUNT];

    struct Table bestTable;
    initTable(&bestTable);
    struct Table table;
    initTable(&table);

    g_fp = fopen("input.txt", "r");

    if(ReadNumbersCalled(numbers,NUMCOUNT))
    {
        printf("ERROR: reading first line failed");//in case I add error code in func return
    }

    ReadToTable(&table);


    //printf("value: %d \n", gamma * epsilon);
    return 0;
}

//******************Find out if table wins and in which round, returns score if win, -1 if no win*************
int testTableForWin((struct Table *tbl,int *numbers)
{
    for(int i = 0 ; ; i++)//go through numbers, end is indicated by -1
    {
        int at = -1; // index of number found
        for(int j = 0 ; j < TABLESIZE ; j++) // search for called out number in table
        {
            if(tbl->table[j] == numbers[i])
            {
                at = j;
                break;
            }
        }
        if(at == -1)//number not present, move to next
        {
            continue;
        }

        //check if whole row/col done
        int rowstart = (at%TABLEDIM)-at;
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

    }
}


//******************Read talbe from input file***************
int ReadToTable(struct Table *tbl)
{
    int row[TABLEDIM];
    char delim[2] = " ";
    for(int i = 0 ; i < TABLESIZE ; i++)
    {
        if((i%TABLEDIM) == 0)//check if begginning of a row
        {
            ReadDelimLine(row, TABLEDIM, delim);
        }
        tbl->table[i] = row[i%TABLEDIM];
    }
    fgets(g_buff, MAX, (FILE*)g_fp);//skip the empty line
    return 0;
}

//*****************Init table to some neutral values****************
void initTable(struct Table *tbl)
{
    tbl->score = -1;
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

//******************reads row of delimited numbers and loads them into an int array************
int ReadDelimLine(int *numbers,int count,char *delim)
{
    fgets(g_buff, MAX, (FILE*)g_fp);//get first line
    //extract array of called nums
    char* tok;
    tok = strtok(g_buff, delim);//get first token

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
}
