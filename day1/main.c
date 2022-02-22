/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 8

int main()
{
    FILE *fp;
    char buff[MAX];
    int num;
    fp = fopen("input.txt", "r");
    int count = 0; //count of increases
    int prev = 0; //previous
    
    if(fgets(buff, MAX, (FILE*)fp)) //get first value
    {
        num = atoi(buff);
        prev = num;
    }
    else
    {
        printf("ERROR: reading from file failed.");
    }
    
    while(fgets(buff, MAX, (FILE*)fp)) //read and count value increases
    {
        num = atoi(buff);
        //printf("val: %d \n", number);
        if(num > prev)
        {
            count++;
        }
        
        prev = num;
    }
    printf("Count of increases: %d \n", count);
    return 0;
}
