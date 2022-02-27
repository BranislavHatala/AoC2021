/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 8

int main()
{
    FILE *fp;
    char buff[MAX];
    int num;
    fp = fopen("input.txt", "r");
    int count = 0; //count of increases
    int prev = INT_MAX; //previous

    //get first delayed values, z delayed by time 1 and 2
    fgets(buff, MAX, (FILE*)fp);
    int z2 = atoi(buff);
    fgets(buff, MAX, (FILE*)fp);
    int z1 = atoi(buff);

    while(fgets(buff, MAX, (FILE*)fp)) //read and count value increases
    {
        int z0 = atoi(buff);
        int sum = (z0 + z1 + z2); // count sum
        num = atoi(buff);
        //printf("val: %d \n", number);
        if(sum > prev)
        {
            count++;
        }

        prev = sum;
        z2 = z1;
        z1 = z0;

    }
    printf("Count of increases: %d \n", count);
    return 0;
}
