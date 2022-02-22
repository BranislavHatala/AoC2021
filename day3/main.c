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

#define MAX 15
#define BITS 12 //bit width of each entry
int main()
{
    FILE *fp;
    int onesCount[BITS] = {0}; //counter for ones on each bit of entry
    char buff[MAX];
    int count = 0; 
    int threshold = 0;//threshold to determine if one is more common fo each bit, will be equal to count/2
    int gamma = 0;
    int epsilon = 0;
    
    fp = fopen("input.txt", "r");

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
    
    threshold = count/2;
    for(int i = 0;i<BITS;i++)//determine gamma and epsilon
    {
        if(onesCount[BITS-i-1] < threshold)//we go from lsb to msb
        {
            gamma +=  pow(2,i); //add value of bit
        }
        else
        {
            epsilon +=  pow(2,i); //add value of bit
        }
    }
    printf("value: %d \n", gamma * epsilon);
    return 0;
}
